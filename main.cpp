#include <iostream>
#include <string>
#include "Catalogo.h"
#include "Excepciones.h"

// Helpers de interfaz 

void limpiarBuffer() {
    std::cin.ignore(1000, '\n');
}

void separador() {
    std::cout << "----------------------------------------\n";
}

void mostrarMenu() {
    separador();
    std::cout << "     STREAMING POO — MENU PRINCIPAL\n";
    separador();
    std::cout << "  1. Cargar archivo de datos\n";
    std::cout << "  2. Mostrar videos por genero o calificacion\n";
    std::cout << "  3. Mostrar episodios de una serie\n";
    std::cout << "  4. Mostrar peliculas con calificacion minima\n";
    std::cout << "  5. Calificar un video\n";
    std::cout << "  6. Reproducir video                  \n";
    std::cout << "  7. Mostrar imagen del video           \n";
    std::cout << "  0. Salir\n";
    separador();
    std::cout << "  Opcion: ";
}
//funciones interfaz para pedir datos al usuario, como calificación mínima o nombre de video, con validación de entrada para asegurar que los datos sean correctos antes de ser utilizados en las operaciones del catálogo.
double pedirCalificacionMinima() {
    double cal;

    do {
        std::cout << "Calificacion minima (1-5): ";
        std::cin >> cal;
    } while (cal < 1 || cal > 5);

    limpiarBuffer();

    return cal;
}

std::string pedirNombreVideo() {
    std::cout << "  Nombre del video: ";
    std::string nombre;
    std::getline(std::cin, nombre);
    return nombre;
}
bool verificarCatalogo(const Catalogo& catalogo)
{
    if (catalogo.estaVacio()) {
        std::cout << "  [!] Primero carga el catalogo (opcion 1).\n";
        return false;
    }

    return true;
}

// main, diferentes casos equivalen a diferentes opciones del menú, cada una con su propia lógica y manejo de excepciones. 
// El programa se ejecuta en un bucle hasta que el usuario elige salir (opción 0).
// En cada caso, se verifica si el catálogo está vacío antes de realizar operaciones que requieren datos cargados, y se manejan las excepciones específicas para proporcionar retroalimentación al usuario en caso de errores.  

int main() {
    Catalogo catalogo;
    int opcion = -1;

    std::cout << "\n  Bienvenido a StreamingPOO\n";

    do {
        mostrarMenu();
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cin.clear();
            limpiarBuffer();
            std::cout << "Opcion invalida\n";
            continue;
        }
        limpiarBuffer();

        switch (opcion) {

        // 1 -> Cargar archivos
        case 1: {
            try {
                catalogo.cargarDesdeArchivo("data/peliculas.txt",
                                             "data/series.txt",
                                             "data/episodios.txt");
            } catch (const ArchivoNoEncontradoException& e) {
                std::cerr << "  [ERROR] " << e.what() << "\n";
            }
            break;
        }

        // 2 -> Videos por género o calificación
        case 2: {
            if (!verificarCatalogo(catalogo)) { break; }
            std::cout << "  Filtrar por:\n    a) Genero\n    b) Calificacion minima\n    c) Todos\n  Seleccion: ";
            
            char sub; 
            std::cin >> sub; 
            limpiarBuffer();
            
            if (sub == 'a' || sub == 'A') {
                std::cout << "  Genero (Drama / Accion / Misterio): ";
                std::string g; 
                std::getline(std::cin, g);
                try { separador(); catalogo.mostrarVideos(g); }
                catch (const GeneroInvalidoException& e){ 
                    std::cerr << "  [ERROR] " << e.what() << "\n"; }
            } 
            else if (sub == 'b' || sub == 'B') {
                double cal = pedirCalificacionMinima();
                separador(); catalogo.mostrarVideos(cal);
            } 
            else {
                separador(); catalogo.mostrarVideos();
            }
            break;
        }

        // 3 -> Episodios de una serie 
        case 3: {
            if (!verificarCatalogo(catalogo)) { break; }
            std::cout << "  Nombre de la serie: ";
            std::string nombre; std::getline(std::cin, nombre);
            double cal = pedirCalificacionMinima();
            separador();
            try { catalogo.mostrarEpisodiosDeSerie(nombre, cal); }
            catch (const SerieNoEncontradaException& e) { 
                std::cerr << "  [ERROR] " << e.what() << "\n"; 
            }
            break;
        }

        // 4 -> Películas con calificación mínima 
        case 4: {
            if (!verificarCatalogo(catalogo)) { break; }
            double cal = pedirCalificacionMinima();
            separador(); catalogo.mostrarPeliculas(cal);
            break;
        }

        // 5 -> Calificar un video
        case 5: {
            if (!verificarCatalogo(catalogo)) { break; }
            std::string nombre = pedirNombreVideo();
            int cal;
            std::cout << "  Calificacion (1-5): ";
            std::cin >> cal;
            if (std::cin.fail()) {
                std::cin.clear();
                limpiarBuffer();
                std::cout << "  [!] Entrada invalida.\n";
            break;
            }

        limpiarBuffer();

        try {
            catalogo.calificarVideo(nombre, cal);
        }
        catch (const CalificacionInvalidaException& e) {
            std::cerr << "  [ERROR] " << e.what() << "\n";
        }
        catch (const VideoNoEncontradoException& e) {
            std::cerr << "  [ERROR] " << e.what() << "\n";
        }

        break;
        }
        //6 -> Reproducir video 
        case 6: {
            if (!verificarCatalogo(catalogo)) { break; }
            std::string nombre = pedirNombreVideo();
            try { catalogo.reproducirVideo(nombre); }
            catch (const VideoNoEncontradoException& e){ 
                std::cerr << "  [ERROR] " << e.what() << "\n"; 
            }
            break;
        }

        //7 -> Mostrar imagen 
        case 7: {
            if (!verificarCatalogo(catalogo)) { break; }
            std::string nombre = pedirNombreVideo();
            try { catalogo.mostrarImagen(nombre); }
            catch (const VideoNoEncontradoException& e) { 
                std::cerr << "  [ERROR] " << e.what() << "\n"; 
            }
            break;
        }

        case 0:
            std::cout << "\n  ¡Hasta luego!\n\n";
            break;

        default:
            std::cout << "  [!] Opcion invalida. Elige entre 0 y 7.\n";
        }

    } while (opcion != 0);

    return 0;
}
