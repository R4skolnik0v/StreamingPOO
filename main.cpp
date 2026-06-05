#include <iostream>
#include <limits>
#include <string>
#include "Catalogo.h"
#include "Excepciones.h"

// ── Helpers de interfaz ───────────────────────────────────────────────────────

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::cout << "  0. Salir\n";
    separador();
    std::cout << "  Opcion: ";
}

// Solicita un double validado al usuario
double pedirCalificacionMinima() {
    double cal;
    while (true) {
        std::cout << "  Calificacion minima (1-5): ";
        if (std::cin >> cal && cal >= 1.0 && cal <= 5.0) {
            limpiarBuffer();
            return cal;
        }
        std::cin.clear();
        limpiarBuffer();
        std::cout << "  [!] Valor invalido. Ingresa un numero entre 1 y 5.\n";
    }
}

// ── main ──────────────────────────────────────────────────────────────────────

int main() {
    Catalogo catalogo;
    int opcion = -1;

    std::cout << "\n  Bienvenido a StreamingPOO\n";

    // ── Menú cíclico ──────────────────────────────────────────────────────────
    do {
        mostrarMenu();

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            limpiarBuffer();
            std::cout << "  [!] Opcion invalida.\n";
            continue;
        }
        limpiarBuffer();

        switch (opcion) {

        // ── 1. Cargar archivo ──────────────────────────────────────────────
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

        // ── 2. Mostrar videos por género o calificación ────────────────────
        case 2: {
            if (catalogo.estaVacio()) { std::cout << "  [!] Primero carga el catalogo (opcion 1).\n"; break; }

            std::cout << "  Filtrar por:\n";
            std::cout << "    a) Genero\n";
            std::cout << "    b) Calificacion minima\n";
            std::cout << "    c) Todos\n";
            std::cout << "  Seleccion: ";
            char sub; std::cin >> sub; limpiarBuffer();

            if (sub == 'a' || sub == 'A') {
                std::cout << "  Genero (Drama / Accion / Misterio): ";
                std::string g; std::getline(std::cin, g);
                try {
                    separador();
                    catalogo.mostrarVideos(g);
                } catch (const GeneroInvalidoException& e) {
                    std::cerr << "  [ERROR] " << e.what() << "\n";
                }
            } else if (sub == 'b' || sub == 'B') {
                double cal = pedirCalificacionMinima();
                separador();
                catalogo.mostrarVideos(cal);
            } else {
                separador();
                catalogo.mostrarVideos();
            }
            break;
        }

        // ── 3. Episodios de una serie ──────────────────────────────────────
        case 3: {
            if (catalogo.estaVacio()) { std::cout << "  [!] Primero carga el catalogo (opcion 1).\n"; break; }

            std::cout << "  Nombre de la serie: ";
            std::string nombre; std::getline(std::cin, nombre);
            double cal = pedirCalificacionMinima();
            separador();
            try {
                catalogo.mostrarEpisodiosDeSerie(nombre, cal);
            } catch (const SerieNoEncontradaException& e) {
                std::cerr << "  [ERROR] " << e.what() << "\n";
            }
            break;
        }

        // ── 4. Películas con calificación mínima ───────────────────────────
        case 4: {
            if (catalogo.estaVacio()) { std::cout << "  [!] Primero carga el catalogo (opcion 1).\n"; break; }

            double cal = pedirCalificacionMinima();
            separador();
            catalogo.mostrarPeliculas(cal);
            break;
        }

        // ── 5. Calificar un video ──────────────────────────────────────────
        case 5: {
            if (catalogo.estaVacio()) { std::cout << "  [!] Primero carga el catalogo (opcion 1).\n"; break; }

            std::cout << "  Titulo del video: ";
            std::string nombre; std::getline(std::cin, nombre);

            int cal;
            std::cout << "  Calificacion (1-5): ";
            if (!(std::cin >> cal)) {
                std::cin.clear(); limpiarBuffer();
                std::cout << "  [!] Entrada invalida.\n"; break;
            }
            limpiarBuffer();

            try {
                catalogo.calificarVideo(nombre, cal);
            } catch (const CalificacionInvalidaException& e) {
                std::cerr << "  [ERROR] " << e.what() << "\n";
            } catch (const VideoNoEncontradoException& e) {
                std::cerr << "  [ERROR] " << e.what() << "\n";
            }
            break;
        }

        case 0:
            std::cout << "\n  ¡Hasta luego!\n\n";
            break;

        default:
            std::cout << "  [!] Opcion invalida. Elige entre 0 y 5.\n";
        }

    } while (opcion != 0);

    return 0;
}
