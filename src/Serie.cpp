#include "Serie.h"
#include <iostream>

Serie::Serie(int id, const std::string& nombre, int duracion, Genero genero)
    : Video(id, nombre, duracion, genero) {}

void Serie::agregarEpisodio(const Episodio& ep) {
    episodios.push_back(ep);
}

void Serie::mostrarInfo() const {
    std::cout << "[SERIE]    " << *this              // usa operator<<
              << " | Episodios: " << episodios.size() << "\n";
}

void Serie::mostrarEpisodios(double calMin) const { //filtro por calificación mínima
    bool hayResultados = false;
    for (const Episodio& ep : episodios) {
        if (ep.getPromedio() >= calMin) {
            std::cout << ep << "\n";
            hayResultados = true;
        }
    }
    if (hayResultados == false)
        std::cout << "  (No hay episodios con promedio >= " << calMin << ")\n";
}

const std::vector<Episodio>& Serie::getEpisodios() const { 
    return episodios; 
}
