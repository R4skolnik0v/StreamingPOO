#include "Catalogo.h"

#include <fstream> //leer archivos 
#include <sstream>
#include <iostream>


// CARGAR DATOS ------------------------------
void Catalogo::cargarDesdeArchivo(const std::string& rutaPeliculas, const std::string& rutaSeries, const std::string& rutaEpisodios) {
    videos.clear();
    // PELICULAS ---------------
    std::ifstream f1(rutaPeliculas);
    if (!f1.is_open()) throw ArchivoNoEncontradoException(rutaPeliculas);

    std::string linea;
    std::getline(f1, linea); // header

    while (std::getline(f1, linea)) {
        if (linea == "") continue;

        std::stringstream ss(linea); //divide la línea en partes usando la coma como delimitador

        std::string id, nombre, dur, genero, director, rutaVid, rutaImg;

        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dur, ',');
        std::getline(ss, genero, ',');
        std::getline(ss, director, ',');
        std::getline(ss, rutaVid, ',');
        std::getline(ss, rutaImg, ',');

        auto p = std::make_shared<Pelicula>( //creacion del obj, leer txt llega como string 
            std::stoi(id), //convierte el id de string a int
            nombre,
            std::stoi(dur),
            stringToGenero(genero),
            director
        );

        p->setRutaImagen(rutaImg);
        p->setRutaVideo(rutaVid);

        videos.push_back(p); // Agrega la película al vector general
    }
    
    // SERIES ---------------
   
    std::ifstream f2(rutaSeries);
    if (!f2.is_open()) throw ArchivoNoEncontradoException(rutaSeries);

    std::getline(f2, linea);

    while (std::getline(f2, linea)) {
        if (linea == "") continue; //Recorrer 

        std::stringstream ss(linea);

        std::string id, nombre, dur, genero, rutaVid, rutaImg;

        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, dur, ',');
        std::getline(ss, genero, ',');
        std::getline(ss, rutaVid, ',');
        std::getline(ss, rutaImg, ',');

        auto s = std::make_shared<Serie>( // Creacion del obj, leer txt llega como string
            std::stoi(id),
            nombre,
            std::stoi(dur),
            stringToGenero(genero)
        );

        s->setRutaVideo(rutaVid);
        s->setRutaImagen(rutaImg);

        videos.push_back(s); //Guardar en catalogo
    }

    
    // EPISODIOS ------------
    
    std::ifstream f3(rutaEpisodios);
    if (!f3.is_open()) throw ArchivoNoEncontradoException(rutaEpisodios);

    std::getline(f3, linea);

    while (std::getline(f3, linea)) {
        if (linea == "") continue;

        std::stringstream ss(linea);

        std::string serie, titulo, temp;

        std::getline(ss, serie, ',');
        std::getline(ss, titulo, ',');
        std::getline(ss, temp, ',');

        std::shared_ptr<Serie> encontrada = nullptr; // Buscar la serie a la que pertenece el episodio

        for (auto& v : videos) {
            auto seriePtr = std::dynamic_pointer_cast<Serie>(v); // Convertir video a Serie 
            if (seriePtr == nullptr) continue;
            if (seriePtr->getNombre() == serie) {
            encontrada = seriePtr;
        break;
    }
}

        if (!encontrada) continue;

        Episodio ep(titulo, std::stoi(temp));

        std::string cal;

        while (std::getline(ss, cal, ',')) {
            if (cal != "") {
                ep.agregarCalificacion(std::stoi(cal));
            }
        }

        encontrada->agregarEpisodio(ep);
    }

    std::cout << "Catalogo cargado: " << videos.size() << "\n";

    // Restaurar calificaciones guardadas en sesiones anteriores
    cargarCalificaciones();
}


// MOSTRAR VIDEOS ------------------------------

void Catalogo::mostrarVideos() const { // Recorre catalogo y muestra info 
    for (auto& v : videos) { // V es peli o serie 
        v->mostrarInfo();
    }
}

void Catalogo::mostrarVideos(const std::string& genero) const {
    Genero g = stringToGenero(genero);

    for (auto& v : videos) {
        if (v->getGenero() == g) { // Filtrar por genero
            v->mostrarInfo();
        }
    }
}

void Catalogo::mostrarVideos(double calMin) const {
    for (auto& v : videos) {
        if (v->getPromedio() >= calMin) {
            v->mostrarInfo();
        }
    }
}

// PELICULAS

void Catalogo::mostrarPeliculas(double calMin) const {
    for (auto& v : videos) {
        auto p = std::dynamic_pointer_cast<Pelicula>(v); // Intenta convertir video a Pelicula 

        if (p && p->getPromedio() >= calMin) {
            p->mostrarInfo();
        }
    }
}

// SERIES

void Catalogo::mostrarEpisodiosDeSerie(const std::string& nombreSerie, double calMin) const {

    for (auto& v : videos) {
        auto s = std::dynamic_pointer_cast<Serie>(v);

        if (s && s->getNombre() == nombreSerie) {
            s->mostrarEpisodios(calMin);
            return;
        }
    }

    throw SerieNoEncontradaException(nombreSerie);
}


// CALIFICAR
void Catalogo::calificarVideo(const std::string& nombre, int cal) {

    for (auto& v : videos) { // Recorre videos 
        if (v->getNombre() == nombre) {
            v->agregarCalificacion(cal);
            guardarCalificaciones(); // persistir de inmediato para no perderla al cerrar
            return;
        }
    }

    throw VideoNoEncontradoException(nombre);
}

// PERSISTENCIA DE CALIFICACIONES

// Guarda las calificaciones de todos los videos en un archivo.
// Formato: id,cal1,cal2,...
void Catalogo::guardarCalificaciones(const std::string& ruta) const {
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        throw ArchivoNoEncontradoException(ruta);
    }

    for (const auto& v : videos) {
        const std::vector<int>& cals = v->getCalificaciones();
        if (cals.empty()) continue; // no guardar videos sin calificaciones

        archivo << v->getId();
        for (int c : cals) {
            archivo << "," << c;
        }
        archivo << "\n";
    }
}

// Carga las calificaciones guardadas en una sesion anterior.
// Si el archivo no existe todavia (primera vez), no hace nada.
void Catalogo::cargarCalificaciones(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea == "") continue;

        std::stringstream ss(linea);
        std::string token;
        if (!std::getline(ss, token, ',')) continue;

        int id = std::stoi(token);

        for (auto& v : videos) {
            if (v->getId() == id) {
                while (std::getline(ss, token, ',')) {
                    if (token == "") continue;
                    try {
                        v->agregarCalificacion(std::stoi(token));
                    } catch (...) {
                        // calificacion corrupta en el archivo: se ignora
                    }
                }
                break;
            }
        }
    }
}

// UTIL

bool Catalogo::estaVacio() const {
    return videos.empty();
}


// MULTIMEDIA

static void abrir(const std::string& ruta) { //Abre segun el sistema operativo

#if defined(_WIN32)
    system(("start " + ruta).c_str());
#elif defined(__APPLE__)
    system(("open " + ruta).c_str());
#elif defined(__linux__)
    system(("xdg-open " + ruta).c_str());
#endif

}

void Catalogo::reproducirVideo(const std::string& nombre) const {

    for (auto& v : videos) {
        if (v->getNombre() == nombre) {
            abrir(v->getRutaVideo());
            return;
        }
    }

    throw VideoNoEncontradoException(nombre);
}

void Catalogo::mostrarImagen(const std::string& nombre) const {

    for (auto& v : videos) {
        if (v->getNombre() == nombre) {
            abrir(v->getRutaImagen());
            return;
        }
    }

    throw VideoNoEncontradoException(nombre);
}

void Catalogo::mostrarCatalogoSimple() const {
    std::cout << "\n--- CATALOGO DISPONIBLE ---\n";

    for (auto& v : videos) {
        std::cout << "- " << v->getNombre();

        if (dynamic_cast<Pelicula*>(v.get())) {
            std::cout << " (Pelicula)";
        } 
        else if (dynamic_cast<Serie*>(v.get())) {
            std::cout << " (Serie)";
        }

        std::cout << "\n";
    }
}