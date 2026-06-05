#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

#include "Video.h"
#include "Pelicula.h"
#include "Serie.h"
#include "Episodio.h"

// ─── Helpers de impresión ────────────────────────────────────────────────────

void separador(const std::string& titulo) {
    std::cout << "\n========== " << titulo << " ==========\n";
}

// ─── Reportes ────────────────────────────────────────────────────────────────

// Reporte 1: todos los videos (polimorfismo)
void mostrarTodosLosVideos(const std::vector<std::shared_ptr<Video>>& videos) {
    separador("TODOS LOS VIDEOS");
    for (const auto& v : videos)
        v->mostrarInfo();   // polimorfismo en acción
}

// Reporte 2: solo películas
void mostrarPeliculas(const std::vector<std::shared_ptr<Video>>& videos) {
    separador("PELICULAS");
    for (const auto& v : videos)
        if (auto p = std::dynamic_pointer_cast<Pelicula>(v))
            p->mostrarInfo();
}

// Reporte 3: solo series
void mostrarSeries(const std::vector<std::shared_ptr<Video>>& videos) {
    separador("SERIES");
    for (const auto& v : videos)
        if (auto s = std::dynamic_pointer_cast<Serie>(v))
            s->mostrarInfo();
}

// Reporte 4: episodios de una serie
void mostrarEpisodiosDeSerie(const std::vector<std::shared_ptr<Video>>& videos,
                              const std::string& nombreSerie) {
    separador("EPISODIOS DE: " + nombreSerie);
    bool encontrada = false;
    for (const auto& v : videos) {
        if (auto s = std::dynamic_pointer_cast<Serie>(v)) {
            if (s->getNombre() == nombreSerie) {
                s->mostrarEpisodios();
                encontrada = true;
                break;
            }
        }
    }
    if (!encontrada)
        throw std::runtime_error("Serie no encontrada: " + nombreSerie);
}

// Reporte 5: filtrar películas por género
void filtrarPeliculasPorGenero(const std::vector<std::shared_ptr<Video>>& videos, Genero g) {
    separador("PELICULAS DE GENERO: " + generoToString(g));
    for (const auto& v : videos)
        if (auto p = std::dynamic_pointer_cast<Pelicula>(v))
            if (p->getGenero() == g)
                p->mostrarInfo();
}

// Reporte 6: filtrar series por género
void filtrarSeriesPorGenero(const std::vector<std::shared_ptr<Video>>& videos, Genero g) {
    separador("SERIES DE GENERO: " + generoToString(g));
    for (const auto& v : videos)
        if (auto s = std::dynamic_pointer_cast<Serie>(v))
            if (s->getGenero() == g)
                s->mostrarInfo();
}

// Demo del operator> y operator<<
void demoOperadores(const std::vector<std::shared_ptr<Video>>& videos) {
    separador("DEMO OPERADORES SOBRECARGADOS");

    // operator<<
    std::cout << "operator<< en accion:\n";
    for (const auto& v : videos)
        std::cout << *v << "\n";

    // operator>  — comparar primeros dos videos
    if (videos.size() >= 2) {
        std::cout << "\noperator> : ";
        if (*videos[0] > *videos[1])
            std::cout << videos[0]->getNombre() << " tiene mejor promedio que " << videos[1]->getNombre() << "\n";
        else
            std::cout << videos[1]->getNombre() << " tiene mejor promedio que (o igual a) " << videos[0]->getNombre() << "\n";
    }
}

// ─── main ────────────────────────────────────────────────────────────────────

int main() {
    std::cout << std::fixed << std::setprecision(1);

    // ── Crear catálogo ──────────────────────────────────────────────────────
    std::vector<std::shared_ptr<Video>> catalogo;

    // Películas
    auto p1 = std::make_shared<Pelicula>(1, "Inception", 148, Genero::Accion, "Nolan");
    auto p2 = std::make_shared<Pelicula>(2, "El Padrino", 175, Genero::Drama, "Coppola");
    auto p3 = std::make_shared<Pelicula>(3, "Knives Out", 131, Genero::Misterio, "Johnson");

    // Series
    auto s1 = std::make_shared<Serie>(4, "Breaking Bad", 47, Genero::Drama);
    auto s2 = std::make_shared<Serie>(5, "Dark", 60, Genero::Misterio);

    // Episodios de Breaking Bad
    Episodio e1("Pilot", 1);
    Episodio e2("Cat's in the Bag", 1);
    Episodio e3("Ozymandias", 5);

    // ── Calificaciones con manejo de excepciones ────────────────────────────
    try {
        p1->agregarCalificacion(5);
        p1->agregarCalificacion(4);
        p1->agregarCalificacion(5);

        p2->agregarCalificacion(5);
        p2->agregarCalificacion(5);

        p3->agregarCalificacion(4);
        p3->agregarCalificacion(3);

        s1->agregarCalificacion(5);
        s1->agregarCalificacion(5);
        s1->agregarCalificacion(4);

        s2->agregarCalificacion(4);
        s2->agregarCalificacion(5);

        e1.agregarCalificacion(4);
        e2.agregarCalificacion(3);
        e3.agregarCalificacion(5);

        // Prueba de excepción por calificación inválida
        std::cout << "\n[TEST] Intentando agregar calificacion invalida (6)...\n";
        p1->agregarCalificacion(6);   // ← esto lanza excepción

    } catch (const std::out_of_range& e) {
        std::cerr << "[EXCEPCION capturada] " << e.what() << "\n";
    }

    s1->agregarEpisodio(e1);
    s1->agregarEpisodio(e2);
    s1->agregarEpisodio(e3);

    catalogo.push_back(p1);
    catalogo.push_back(p2);
    catalogo.push_back(p3);
    catalogo.push_back(s1);
    catalogo.push_back(s2);

    // ── Reportes ────────────────────────────────────────────────────────────
    mostrarTodosLosVideos(catalogo);
    mostrarPeliculas(catalogo);
    mostrarSeries(catalogo);

    try {
        mostrarEpisodiosDeSerie(catalogo, "Breaking Bad");
        mostrarEpisodiosDeSerie(catalogo, "Stranger Things");  // no existe → excepción
    } catch (const std::runtime_error& e) {
        std::cerr << "[EXCEPCION capturada] " << e.what() << "\n";
    }

    filtrarPeliculasPorGenero(catalogo, Genero::Drama);
    filtrarSeriesPorGenero(catalogo, Genero::Misterio);
    demoOperadores(catalogo);

    std::cout << "\n¡Fin del programa!\n";
    return 0;
}
