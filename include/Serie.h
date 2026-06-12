#pragma once
#include "Video.h"
#include "Episodio.h"
#include <vector>
//Clase serie de relacion de composición con episodio, hereda de video

class Serie : public Video {
private:
    std::vector<Episodio> episodios;  // composición

public:
    Serie(int id, const std::string& nombre, int duracion, Genero genero);

    void agregarEpisodio(const Episodio& ep);

    // Sobreescritura del método virtual puro
    void mostrarInfo() const override;

    // Mostrar episodios con calificación mínima
    void mostrarEpisodios(double calMin = 0.0) const;

    const std::vector<Episodio>& getEpisodios() const;
};
