#include "Episodio.h"

Episodio::Episodio(std::string titulo, int temporada){
    this -> titulo = titulo;
    this -> temporada = temporada;  
}
void Episodio::agregarCalificacion(int cal) {
    if (cal < 1 || cal > 5) throw CalificacionInvalidaException(cal);
    calificaciones.push_back(cal);
}

double Episodio::getPromedio() const {
    if (calificaciones.empty())
        return 0.0;
    int suma = 0;
    for (int i = 0; i < calificaciones.size(); i++) {
        suma += calificaciones[i];
    }
    return (double)suma / calificaciones.size();
}
std::string Episodio::getTitulo() const { 
    return titulo; 
}
int Episodio::getTemporada() const { 
    return temporada; 
}

std::ostream& operator<<(std::ostream& os, const Episodio& e) {

    os << "T" << e.temporada;
    os << " | ";
    os << e.titulo;
    os << " | Promedio: ";
    os << e.getPromedio();
    os << "/5";

    return os;
}
