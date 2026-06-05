#include "Catalogo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

// ── Helpers internos ──────────────────────────────────────────────────────────

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// ── Carga desde archivos ──────────────────────────────────────────────────────
//
// Formato peliculas.txt:
//   id,nombre,duracion,genero,director
//   1,Inception,148,Accion,Nolan
//
// Formato series.txt:
//   id,nombre,duracion_ep,genero
//   4,Breaking Bad,47,Drama
//
// Formato episodios.txt:
//   nombre_serie,titulo_ep,temporada,cal1,cal2,...
//   Breaking Bad,Pilot,1,4,5,4
// ─────────────────────────────────────────────────────────────────────────────

void Catalogo::cargarDesdeArchivo(const std::string& rutaPeliculas,
                                    const std::string& rutaSeries,
                                    const std::string& rutaEpisodios) {
    videos.clear();

    // ── Películas ─────────────────────────────────────────────────────────────
    {
        std::ifstream f(rutaPeliculas);
        if (!f.is_open()) throw ArchivoNoEncontradoException(rutaPeliculas);

        std::string linea;
        std::getline(f, linea); // saltar encabezado
        while (std::getline(f, linea)) {
            if (trim(linea).empty() || linea[0] == '#') continue;
            std::istringstream ss(linea);
            std::string id_s, nombre, dur_s, genero_s, director, rutaVid, rutaImg;
            std::getline(ss, id_s,    ',');
            std::getline(ss, nombre,  ',');
            std::getline(ss, dur_s,   ',');
            std::getline(ss, genero_s,',');
            std::getline(ss, director,',');
            std::getline(ss, rutaVid, ',');
            std::getline(ss, rutaImg, ',');
            try {
                auto p = std::make_shared<Pelicula>(
                    std::stoi(trim(id_s)),
                    trim(nombre),
                    std::stoi(trim(dur_s)),
                    stringToGenero(trim(genero_s)),
                    trim(director)
                );
                p->setRutaVideo(trim(rutaVid));
                p->setRutaImagen(trim(rutaImg));
                videos.push_back(p);
            } catch (const std::exception& e) {
                std::cerr << "[AVISO] Pelicula ignorada: " << e.what() << "\n";
            }
        }
    }

    // ── Series ────────────────────────────────────────────────────────────────
    {
        std::ifstream f(rutaSeries);
        if (!f.is_open()) throw ArchivoNoEncontradoException(rutaSeries);

        std::string linea;
        std::getline(f, linea); // encabezado
        while (std::getline(f, linea)) {
            if (trim(linea).empty() || linea[0] == '#') continue;
            std::istringstream ss(linea);
            std::string id_s, nombre, dur_s, genero_s, rutaVid, rutaImg;
            std::getline(ss, id_s,    ',');
            std::getline(ss, nombre,  ',');
            std::getline(ss, dur_s,   ',');
            std::getline(ss, genero_s,',');
            std::getline(ss, rutaVid, ',');
            std::getline(ss, rutaImg, ',');
            try {
                auto s = std::make_shared<Serie>(
                    std::stoi(trim(id_s)),
                    trim(nombre),
                    std::stoi(trim(dur_s)),
                    stringToGenero(trim(genero_s))
                );
                s->setRutaVideo(trim(rutaVid));
                s->setRutaImagen(trim(rutaImg));
                videos.push_back(s);
            } catch (const std::exception& e) {
                std::cerr << "[AVISO] Serie ignorada: " << e.what() << "\n";
            }
        }
    }

    // ── Episodios ─────────────────────────────────────────────────────────────
    {
        std::ifstream f(rutaEpisodios);
        if (!f.is_open()) throw ArchivoNoEncontradoException(rutaEpisodios);

        std::string linea;
        std::getline(f, linea); // encabezado
        while (std::getline(f, linea)) {
            if (trim(linea).empty() || linea[0] == '#') continue;
            std::istringstream ss(linea);
            std::string nombre_serie, titulo, temp_s, token;
            std::getline(ss, nombre_serie, ',');
            std::getline(ss, titulo,       ',');
            std::getline(ss, temp_s,       ',');
            nombre_serie = trim(nombre_serie);
            titulo       = trim(titulo);

            // Buscar la serie correspondiente
            std::shared_ptr<Serie> serie = nullptr;
            for (auto& v : videos) {
                if (auto s = std::dynamic_pointer_cast<Serie>(v)) {
                    if (s->getNombre() == nombre_serie) { serie = s; break; }
                }
            }
            if (!serie) {
                std::cerr << "[AVISO] Serie no encontrada para episodio: " << nombre_serie << "\n";
                continue;
            }

            Episodio ep(titulo, std::stoi(trim(temp_s)));
            while (std::getline(ss, token, ',')) {
                token = trim(token);
                if (!token.empty()) {
                    try { ep.agregarCalificacion(std::stoi(token)); }
                    catch (...) {}
                }
            }
            serie->agregarEpisodio(ep);
        }
    }

    std::cout << "\n✓ Catalogo cargado: " << videos.size() << " video(s).\n";
}

// ── Reportes ──────────────────────────────────────────────────────────────────

// Sobrecarga 1: todos los videos
void Catalogo::mostrarVideos() const {
    std::cout << std::fixed << std::setprecision(1);
    if (videos.empty()) { std::cout << "  (Catalogo vacio)\n"; return; }
    for (const auto& v : videos) v->mostrarInfo();  // polimorfismo
}

// Sobrecarga 2: filtrar por género
void Catalogo::mostrarVideos(const std::string& generoStr) const {
    std::cout << std::fixed << std::setprecision(1);
    Genero g = stringToGenero(generoStr); // lanza GeneroInvalidoException si no existe
    bool hayAlguno = false;
    for (const auto& v : videos) {
        if (v->getGenero() == g) { v->mostrarInfo(); hayAlguno = true; }
    }
    if (!hayAlguno) std::cout << "  (No hay videos del genero " << generoStr << ")\n";
}

// Sobrecarga 3: filtrar por calificación mínima
void Catalogo::mostrarVideos(double calMin) const {
    std::cout << std::fixed << std::setprecision(1);
    bool hayAlguno = false;
    for (const auto& v : videos) {
        if (v->getPromedio() >= calMin) { v->mostrarInfo(); hayAlguno = true; }
    }
    if (!hayAlguno) std::cout << "  (No hay videos con promedio >= " << calMin << ")\n";
}

// Opción 4: solo películas con calificación mínima
void Catalogo::mostrarPeliculas(double calMin) const {
    std::cout << std::fixed << std::setprecision(1);
    bool hayAlguno = false;
    for (const auto& v : videos) {
        if (auto p = std::dynamic_pointer_cast<Pelicula>(v)) {
            if (p->getPromedio() >= calMin) { p->mostrarInfo(); hayAlguno = true; }
        }
    }
    if (!hayAlguno) std::cout << "  (No hay peliculas con promedio >= " << calMin << ")\n";
}

// Opción 3: episodios de una serie con calificación mínima
void Catalogo::mostrarEpisodiosDeSerie(const std::string& nombreSerie, double calMin) const {
    for (const auto& v : videos) {
        if (auto s = std::dynamic_pointer_cast<Serie>(v)) {
            if (s->getNombre() == nombreSerie) {
                std::cout << "Episodios de \"" << nombreSerie
                          << "\" con promedio >= " << calMin << ":\n";
                s->mostrarEpisodios(calMin);
                return;
            }
        }
    }
    throw SerieNoEncontradaException(nombreSerie);
}

// Opción 5: calificar un video
void Catalogo::calificarVideo(const std::string& nombre, int cal) {
    for (auto& v : videos) {
        if (v->getNombre() == nombre) {
            v->agregarCalificacion(cal); // lanza CalificacionInvalidaException si inválida
            std::cout << "✓ Calificacion agregada. Nuevo promedio de \""
                      << nombre << "\": " << v->getPromedio() << "/5\n";
            return;
        }
    }
    throw VideoNoEncontradoException(nombre);
}

bool Catalogo::estaVacio() const { return videos.empty(); }

// ── Multimedia ────────────────────────────────────────────────────────────────

static void abrirArchivo(const std::string& ruta) {
#if defined(_WIN32) || defined(_WIN64)
    std::system(("start \"\" \"" + ruta + "\"").c_str());

#elif defined(__APPLE__)
    std::system(("open \"" + ruta + "\"").c_str());

#elif defined(__linux__)
    std::system(("xdg-open \"" + ruta + "\"").c_str());

#else
    std::cerr << "Sistema no soportado\n";
#endif
}
// Opción 6: reproducir video (+40 pts)
void Catalogo::reproducirVideo(const std::string& nombre) const {
    for (const auto& v : videos) {
        if (v->getNombre() == nombre) {
            v->mostrarInfo();
            std::string ruta = v->getRutaVideo();
            if (ruta.empty()) {
                std::cout << "  [!] Este video no tiene archivo multimedia asignado.\n";
                return;
            }
            std::cout << "  Abriendo: " << ruta << "\n";
            abrirArchivo(ruta);
            return;
        }
    }
    throw VideoNoEncontradoException(nombre);
}

// Opción 7: mostrar imagen (+20 pts)
void Catalogo::mostrarImagen(const std::string& nombre) const {
    for (const auto& v : videos) {
        if (v->getNombre() == nombre) {
            std::string ruta = v->getRutaImagen();
            if (ruta.empty()) {
                std::cout << "  [!] Este video no tiene imagen asignada.\n";
                return;
            }
            std::cout << "  Abriendo imagen: " << ruta << "\n";
            abrirArchivo(ruta);
            return;
        }
    }
    throw VideoNoEncontradoException(nombre);
}
