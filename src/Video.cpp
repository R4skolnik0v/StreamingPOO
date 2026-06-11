#include "Video.h"
#include <numeric> //sumar los elementos del vector 


//  Utilidades de Genero 

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

// Video - Implementación de métodos

Video::Video(int id, const std::string& nombre, int duracion, Genero genero){
    this->id = id;
    this->nombre = nombre;
    this->duracion = duracion;
    this->genero = genero;
}

void Video::agregarCalificacion(int cal) {
    if (cal < 1 || cal > 5)
        throw CalificacionInvalidaException(cal);
    calificaciones.push_back(cal);
}

double Video::getPromedio() const {
    if (calificaciones.empty()) return 0.0;
    int suma = 0;
    for (int cal : calificaciones){
        suma += cal;
    }
return (double)suma / calificaciones.size();
}

int Video::getId() const { 
    return id; 
}
std::string Video::getNombre() const { 
    return nombre; 
}
int Video::getDuracion() const { 
    return duracion; 
}
Genero Video::getGenero()const { 
    return genero; 
}
std::string Video::getRutaVideo() const { 
    return rutaVideo; 
}
std::string Video::getRutaImagen()const { 
    return rutaImagen; 
}
void Video::setRutaVideo(const std::string& r)  { 
    rutaVideo  = r; 
}
void Video::setRutaImagen(const std::string& r) { 
    rutaImagen = r; 
}

bool Video::operator>(const Video& otro) const {
    return getPromedio() > otro.getPromedio();
}

std::ostream& operator<<(std::ostream& os, const Video& v) {
    os << v.nombre
       << " [" << generoToString(v.genero) << "]"
       << " | " << v.duracion << " min"
       << " | Promedio: " << v.getPromedio() << "/5";
    return os; // Mostrar el video con su nombre, genero, duracion y promedio de calificaciones con cout (sobrecarga de <<)
}
