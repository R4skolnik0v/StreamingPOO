# Diagrama UML — StreamingPOO

## Mermaid (pega en https://mermaid.live)

```mermaid
classDiagram
    class Video {
        <<abstract>>
        #int id
        #string nombre
        #int duracion
        #Genero genero
        -vector~int~ calificaciones
        +Video(id, nombre, duracion, genero)
        +agregarCalificacion(int) void
        +getPromedio() double
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
        +mostrarInfo() void
        +mostrarEpisodios(double calMin) void
        +getEpisodios() vector~Episodio~
    }

    class Episodio {
        -string titulo
        -int temporada
        -vector~int~ calificaciones
        +Episodio(titulo, temporada)
        +agregarCalificacion(int) void
        +getPromedio() double
        +getTitulo() string
        +getTemporada() int
        +operator<<(ostream, Episodio) ostream
    }

    class Catalogo {
        -vector~shared_ptr~Video~~ videos
        +cargarDesdeArchivo(string, string, string) void
        +mostrarVideos() void
        +mostrarVideos(string genero) void
        +mostrarVideos(double calMin) void
        +mostrarPeliculas(double calMin) void
        +mostrarEpisodiosDeSerie(string, double) void
        +calificarVideo(string, int) void
        +estaVacio() bool
    }

    class Genero {
        <<enumeration>>
        Drama
        Accion
        Misterio
    }

    class CalificacionInvalidaException {
        +CalificacionInvalidaException(int)
    }

    class VideoNoEncontradoException {
        +VideoNoEncontradoException(string)
    }

    class SerieNoEncontradaException {
        +SerieNoEncontradaException(string)
    }

    class GeneroInvalidoException {
        +GeneroInvalidoException(string)
    }

    Video <|-- Pelicula : herencia
    Video <|-- Serie : herencia
    Serie "1" *-- "0..*" Episodio : composición
    Catalogo "1" o-- "0..*" Video : agrega (polimorfismo)
    Video --> Genero : usa

    out_of_range <|-- CalificacionInvalidaException
    runtime_error <|-- VideoNoEncontradoException
    runtime_error <|-- SerieNoEncontradaException
    invalid_argument <|-- GeneroInvalidoException
```

---

## PlantUML (pega en https://plantuml.com/plantuml)

```plantuml
@startuml StreamingPOO

skinparam classAttributeIconSize 0

abstract class Video {
    # id : int
    # nombre : string
    # duracion : int
    # genero : Genero
    - calificaciones : vector<int>
    + agregarCalificacion(int) : void
    + getPromedio() : double
    + {abstract} mostrarInfo() : void
    + operator>(Video) : bool
}

class Pelicula {
    - director : string
    + mostrarInfo() : void
}

class Serie {
    - episodios : vector<Episodio>
    + agregarEpisodio(Episodio) : void
    + mostrarInfo() : void
    + mostrarEpisodios(double) : void
}

class Episodio {
    - titulo : string
    - temporada : int
    - calificaciones : vector<int>
    + agregarCalificacion(int) : void
    + getPromedio() : double
}

class Catalogo {
    - videos : vector<shared_ptr<Video>>
    + cargarDesdeArchivo(...) : void
    + mostrarVideos() : void
    + mostrarVideos(string) : void
    + mostrarVideos(double) : void
    + mostrarPeliculas(double) : void
    + mostrarEpisodiosDeSerie(string, double) : void
    + calificarVideo(string, int) : void
}

enum Genero {
    Drama
    Accion
    Misterio
}

Video <|-- Pelicula
Video <|-- Serie
Serie "1" *-- "0..*" Episodio : composicion
Catalogo o-- Video : gestiona

@enduml
```

---

## Relaciones

| Relación              | Tipo        | Descripción                                       |
|-----------------------|-------------|---------------------------------------------------|
| Video → Pelicula      | Herencia    | Pelicula extiende Video                           |
| Video → Serie         | Herencia    | Serie extiende Video                              |
| Serie ◆→ Episodio     | Composición | Serie posee y gestiona sus episodios              |
| Catalogo ◇→ Video     | Agregación  | Catalogo administra videos mediante polimorfismo  |
