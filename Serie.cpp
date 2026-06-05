#include "Serie.h"
#include <iostream>
#include <iomanip>

Serie::Serie(int id, const std::string& nombre, int duracion, Genero genero)
    : Video(id, nombre, duracion, genero) {}

void Serie::agregarEpisodio(const Episodio& ep) {
    episodios.push_back(ep);
}

void Serie::mostrarEpisodios() const {
    std::cout << "Episodios de \"" << nombre << "\":\n";
    if (episodios.empty()) {
        std::cout << "  (Sin episodios registrados)\n";
        return;
    }
    for (const auto& ep : episodios)
        std::cout << ep << "\n";
}

const std::vector<Episodio>& Serie::getEpisodios() const {
    return episodios;
}

void Serie::mostrarInfo() const {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "[SERIE]    ID: " << id
              << " | Nombre: " << nombre
              << " | Genero: " << generoToString(genero)
              << " | Duracion ep: " << duracion << " min"
              << " | Episodios: " << episodios.size()
              << " | Promedio: " << promedioCalificaciones() << "/5\n";
}
