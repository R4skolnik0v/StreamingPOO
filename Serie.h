#pragma once
#include "Video.h"
#include "Episodio.h"
#include <vector>

class Serie : public Video {
private:
    std::vector<Episodio> episodios;

public:
    Serie(int id, const std::string& nombre, int duracion, Genero genero);

    void agregarEpisodio(const Episodio& ep);
    void mostrarEpisodios() const;
    const std::vector<Episodio>& getEpisodios() const;

    void mostrarInfo() const override;
};
