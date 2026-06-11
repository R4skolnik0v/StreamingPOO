#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Excepciones.h"

// Enum de géneros válidos
enum class Genero { Drama, Accion, Misterio };

std::string generoToString(Genero g);
Genero stringToGenero(const std::string& s); // Lanza GeneroInvalidoException si no es válido

// Clase abstracta base

class Video {
protected: 
// protected: accesible en clases hijas, no fuera de la jerarquía
    int id;
    std::string nombre;
    int duracion;  
    Genero genero;
    std::string rutaVideo;   
    std::string rutaImagen;  

private:
    std::vector<int> calificaciones;

public:
    Video(int id, const std::string& nombre, int duracion, Genero genero); //constructor base
    virtual ~Video() = default; //destructor 

    virtual void mostrarInfo() const = 0; // Cada hijo implementa mostrarinfo

    // Getters 
    int         getId()       const;
    std::string getNombre()   const;
    int         getDuracion() const;
    Genero      getGenero()   const;
    double      getPromedio() const;
    std::string getRutaVideo()  const;
    std::string getRutaImagen() const;

    // Setters 
    void setRutaVideo(const std::string& ruta);
    void setRutaImagen(const std::string& ruta);

    // Agregar calificación
    void agregarCalificacion(int cal);

    // Sobrecarga de operadores 
    bool operator>(const Video& otro) const;              // compara por promedio
    friend std::ostream& operator<<(std::ostream& os, const Video& v); // Es una sobrecarga del operador << para que un objeto Video pueda imprimirse directamente con cout. Se declara como friend para que pueda acceder a los atributos internos del objeto 
};
