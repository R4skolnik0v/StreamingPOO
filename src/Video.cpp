#include "Video.h"
#include <numeric>
#include <algorithm>

// ── Utilidades de Genero ──────────────────────────────────────────────────────

std::string generoToString(Genero g) {
    switch (g) {
        case Genero::Drama:    return "Drama";
        case Genero::Accion:   return "Accion";
        case Genero::Misterio: return "Misterio";
        default:               return "Desconocido";
    }
}

Genero stringToGenero(const std::string& s) {
    if (s == "Drama")    return Genero::Drama;
    if (s == "Accion")   return Genero::Accion;
    if (s == "Misterio") return Genero::Misterio;
    throw GeneroInvalidoException(s);
}

// ── Video ─────────────────────────────────────────────────────────────────────

Video::Video(int id, const std::string& nombre, int duracion, Genero genero)
    : id(id), nombre(nombre), duracion(duracion), genero(genero) {}

void Video::agregarCalificacion(int cal) {
    if (cal < 1 || cal > 5)
        throw CalificacionInvalidaException(cal);
    calificaciones.push_back(cal);
}

double Video::getPromedio() const {
    if (calificaciones.empty()) return 0.0;
    int suma = std::accumulate(calificaciones.begin(), calificaciones.end(), 0);
    return static_cast<double>(suma) / calificaciones.size();
}

int         Video::getId()       const { return id; }
std::string Video::getNombre()   const { return nombre; }
int         Video::getDuracion() const { return duracion; }
Genero      Video::getGenero()   const { return genero; }

bool Video::operator>(const Video& otro) const {
    return this->getPromedio() > otro.getPromedio();
}

std::ostream& operator<<(std::ostream& os, const Video& v) {
    os << v.nombre
       << " [" << generoToString(v.genero) << "]"
       << " | " << v.duracion << " min"
       << " | Promedio: " << v.getPromedio() << "/5";
    return os;
}
