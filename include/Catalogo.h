#pragma once
#include <vector>
#include <memory> // Para el shared ptr
#include <string>
#include "Video.h"
#include "Pelicula.h"
#include "Serie.h"
#include "Excepciones.h"

class Catalogo {
private:
    std::vector<std::shared_ptr<Video>> videos;  // lista de todos los videos (películas y series)

public:
    // Carga desde archivo 
    void cargarDesdeArchivo(const std::string& rutaPeliculas, const std::string& rutaSeries, const std::string& rutaEpisodios);

    // Reportes sobrecarga de métodos 
    void mostrarVideos() const; // todos
    void mostrarVideos(const std::string& genero) const; // por género
    void mostrarVideos(double calMin)             const; // por calificación mínima

    void mostrarPeliculas(double calMin)          const; // opción 4
    void mostrarEpisodiosDeSerie(const std::string& nombreSerie, double calMin)  const; // opción 3

    //  Multimedia 
    void reproducirVideo(const std::string& nombre) const;   // opción 6 reproducir video 
    void mostrarImagen(const std::string& nombre)   const;   // opción 7 mostrar imagen 

    //  Calificar 
    void calificarVideo(const std::string& nombre, int cal);

    // Checar si catálogo está vacío
    bool estaVacio() const;
};
