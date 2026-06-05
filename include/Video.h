#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Excepciones.h"

// Enum de géneros válidos
enum class Genero { Drama, Accion, Misterio };

std::string generoToString(Genero g);
Genero stringToGenero(const std::string& s); // lanza GeneroInvalidoException si no es válido

// ─────────────────────────────────────────────
// Clase abstracta base
// ─────────────────────────────────────────────
class Video {
protected:
    // protected: accesible en clases hijas, no fuera de la jerarquía
    int         id;
    std::string nombre;
    int         duracion;   // minutos
    Genero      genero;
    std::string rutaVideo;   // ruta al archivo de video (puntos extra +40)
    std::string rutaImagen;  // ruta a la imagen de portada (puntos extra +20)

private:
    // private: solo accesible dentro de Video
    std::vector<int> calificaciones;

public:
    Video(int id, const std::string& nombre, int duracion, Genero genero);
    virtual ~Video() = default;

    // ── Método virtual puro → Video es abstracta ──
    virtual void mostrarInfo() const = 0;

    // ── Getters (public) ──
    int         getId()       const;
    std::string getNombre()   const;
    int         getDuracion() const;
    Genero      getGenero()   const;
    double      getPromedio() const;
    std::string getRutaVideo()  const;
    std::string getRutaImagen() const;

    void setRutaVideo(const std::string& ruta);
    void setRutaImagen(const std::string& ruta);

    // Agregar calificación — lanza CalificacionInvalidaException
    void agregarCalificacion(int cal);

    // ── Sobrecarga de operadores ──
    bool operator>(const Video& otro) const;              // compara por promedio
    friend std::ostream& operator<<(std::ostream& os, const Video& v);
};
