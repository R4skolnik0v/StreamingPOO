#include "Episodio.h"
#include <numeric>
#include <iomanip>

Episodio::Episodio(const std::string& titulo, int temporada)
    : titulo(titulo), temporada(temporada) {}

void Episodio::agregarCalificacion(int cal) {
    if (cal < 1 || cal > 5) throw CalificacionInvalidaException(cal);
    calificaciones.push_back(cal);
}

double Episodio::getPromedio() const {
    if (calificaciones.empty()) return 0.0;
    int suma = std::accumulate(calificaciones.begin(), calificaciones.end(), 0);
    return static_cast<double>(suma) / calificaciones.size();
}

std::string Episodio::getTitulo()    const { return titulo; }
int         Episodio::getTemporada() const { return temporada; }

std::ostream& operator<<(std::ostream& os, const Episodio& e) {
    os << std::fixed << std::setprecision(1);
    os << "  T" << e.temporada
       << " | \"" << e.titulo << "\""
       << " | Promedio: " << e.getPromedio() << "/5";
    return os;
}
