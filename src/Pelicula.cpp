#include "Pelicula.h"
#include <iostream>

Pelicula::Pelicula(int id, const std::string& nombre, int duracion, Genero genero, const std::string& director): Video(id, nombre, duracion, genero), director(director) {
    this -> id = id;
    this -> nombre = nombre;
    this -> duracion = duracion;
    this -> genero = genero;
    this -> director = director;    
}

void Pelicula::mostrarInfo() const {
    std::cout << "[PELICULA] " << *this             // usa operator<<
              << " | Director: " << director << "\n";
}

std::string Pelicula::getDirector() const { 
    return director; 
}
