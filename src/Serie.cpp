#include "Serie.h"
#include <iostream>
#include <iomanip>

Serie::Serie(int id, const std::string& nombre, int duracion, Genero genero)
    : Video(id, nombre, duracion, genero) {}

void Serie::agregarEpisodio(const Episodio& ep) {
    episodios.push_back(ep);
}

void Serie::mostrarInfo() const {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "[SERIE]    " << *this              // usa operator<<
              << " | Episodios: " << episodios.size() << "\n";
}

void Serie::mostrarEpisodios(double calMin) const {
    std::cout << std::fixed << std::setprecision(1);
    bool hayResultados = false;
    for (const auto& ep : episodios) {
        if (ep.getPromedio() >= calMin) {
            std::cout << ep << "\n";
            hayResultados = true;
        }
    }
    if (!hayResultados)
        std::cout << "  (No hay episodios con promedio >= " << calMin << ")\n";
}

const std::vector<Episodio>& Serie::getEpisodios() const { return episodios; }
