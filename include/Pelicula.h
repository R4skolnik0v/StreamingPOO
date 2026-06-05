#pragma once
#include "Video.h"

class Pelicula : public Video {
private:
    std::string director;

public:
    Pelicula(int id, const std::string& nombre, int duracion,
             Genero genero, const std::string& director);

    // Sobreescritura del método virtual puro
    void mostrarInfo() const override;

    std::string getDirector() const;
};
