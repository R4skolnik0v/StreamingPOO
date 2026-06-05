#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Episodio {
private:
    std::string titulo;
    int temporada;
    std::vector<int> calificaciones;

public:
    Episodio(const std::string& titulo, int temporada);

    void agregarCalificacion(int cal);
    double promedioCalificaciones() const;

    std::string getTitulo() const;
    int getTemporada() const;

    friend std::ostream& operator<<(std::ostream& os, const Episodio& e);
};
