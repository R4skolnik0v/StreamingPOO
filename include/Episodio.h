#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Excepciones.h"

class Episodio {
private:
    std::string      titulo;
    int              temporada;
    std::vector<int> calificaciones;

public:
    Episodio(const std::string& titulo, int temporada);

    void   agregarCalificacion(int cal); // lanza CalificacionInvalidaException
    double getPromedio() const;

    std::string getTitulo()    const;
    int         getTemporada() const;

    friend std::ostream& operator<<(std::ostream& os, const Episodio& e);
};
