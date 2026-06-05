# Diagrama UML — StreamingPOO

Pega este código en [mermaid.live](https://mermaid.live) para visualizarlo.

```mermaid
classDiagram
    class Video {
        <<abstract>>
        #int id
        #string nombre
        #int duracion
        #Genero genero
        #vector~int~ calificaciones
        +Video(id, nombre, duracion, genero)
        +agregarCalificacion(int) void
        +promedioCalificaciones() double
        +getId() int
        +getNombre() string
        +getDuracion() int
        +getGenero() Genero
        +mostrarInfo()* void
        +operator>(Video) bool
        +operator<<(ostream, Video) ostream
    }

    class Pelicula {
        -string director
        +Pelicula(id, nombre, duracion, genero, director)
        +mostrarInfo() void
        +getDirector() string
    }

    class Serie {
        -vector~Episodio~ episodios
        +Serie(id, nombre, duracion, genero)
        +agregarEpisodio(Episodio) void
        +mostrarEpisodios() void
        +getEpisodios() vector~Episodio~
        +mostrarInfo() void
    }

    class Episodio {
        -string titulo
        -int temporada
        -vector~int~ calificaciones
        +Episodio(titulo, temporada)
        +agregarCalificacion(int) void
        +promedioCalificaciones() double
        +getTitulo() string
        +getTemporada() int
        +operator<<(ostream, Episodio) ostream
    }

    class Genero {
        <<enumeration>>
        Drama
        Accion
        Misterio
    }

    Video <|-- Pelicula : herencia
    Video <|-- Serie : herencia
    Serie "1" *-- "0..*" Episodio : composición
    Video --> Genero : usa
    Episodio --> Genero : usa
```

---

## Relaciones

| Relación               | Tipo         | Descripción                                      |
|------------------------|--------------|--------------------------------------------------|
| `Video → Pelicula`     | Herencia     | Pelicula extiende Video                          |
| `Video → Serie`        | Herencia     | Serie extiende Video                             |
| `Serie ◆→ Episodio`    | Composición  | Serie contiene y gestiona sus propios episodios  |
| `Video → Genero`       | Dependencia  | Video utiliza el enum Genero                     |
