#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

enum class Genero { Drama, Accion, Misterio };

std::string generoToString(Genero g);

class Video {
protected:
    int id;
    std::string nombre;
    int duracion; // minutos
    Genero genero;
    std::vector<int> calificaciones;

public:
    Video(int id, const std::string& nombre, int duracion, Genero genero);
    virtual ~Video() = default;

    // Método virtual puro → clase abstracta
    virtual void mostrarInfo() const = 0;

    void agregarCalificacion(int cal);
    double promedioCalificaciones() const;

    int getId() const;
    std::string getNombre() const;
    int getDuracion() const;
    Genero getGenero() const;

    // Sobrecarga de operadores
    bool operator>(const Video& otro) const;
    friend std::ostream& operator<<(std::ostream& os, const Video& v);
};
