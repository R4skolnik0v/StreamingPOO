#pragma once
#include <stdexcept>
#include <string>

// Excepción personalizada: calificación fuera de rango
class CalificacionInvalidaException : public std::out_of_range {
public:
    explicit CalificacionInvalidaException(int val)
        : std::out_of_range("Calificacion invalida (" + std::to_string(val) +
                             "). Debe estar entre 1 y 5.") {}
};

// Excepción personalizada: video no encontrado
class VideoNoEncontradoException : public std::runtime_error {
public:
    explicit VideoNoEncontradoException(const std::string& nombre)
        : std::runtime_error("Video no encontrado: \"" + nombre + "\"") {}
};

// Excepción personalizada: serie no encontrada
class SerieNoEncontradaException : public std::runtime_error {
public:
    explicit SerieNoEncontradaException(const std::string& nombre)
        : std::runtime_error("Serie no encontrada: \"" + nombre + "\"") {}
};

// Excepción personalizada: género inválido
class GeneroInvalidoException : public std::invalid_argument {
public:
    explicit GeneroInvalidoException(const std::string& g)
        : std::invalid_argument("Genero invalido: \"" + g + "\"") {}
};

// Excepción personalizada: archivo no encontrado
class ArchivoNoEncontradoException : public std::runtime_error {
public:
    explicit ArchivoNoEncontradoException(const std::string& path)
        : std::runtime_error("No se pudo abrir el archivo: \"" + path + "\"") {}
};
