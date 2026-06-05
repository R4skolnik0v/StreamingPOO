#include "Pelicula.h"
#include <iostream>
#include <iomanip>

Pelicula::Pelicula(int id, const std::string& nombre, int duracion,
                   Genero genero, const std::string& director)
    : Video(id, nombre, duracion, genero), director(director) {}

void Pelicula::mostrarInfo() const {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "[PELICULA] " << *this             // usa operator<<
              << " | Director: " << director << "\n";
}

std::string Pelicula::getDirector() const { return director; }
