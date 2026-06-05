# StreamingPOO

Sistema de streaming de video desarrollado en **C++17** como proyecto integrador de Programación Orientada a Objetos.

---

## Estructura del Proyecto

```
StreamingPOO/
├── include/
│   ├── Video.h          ← Clase abstracta base
│   ├── Pelicula.h       ← Hereda de Video
│   ├── Serie.h          ← Hereda de Video
│   ├── Episodio.h       ← Composición dentro de Serie
│   ├── Catalogo.h       ← Administra todos los videos
│   └── Excepciones.h    ← Excepciones personalizadas
├── src/
│   ├── Video.cpp
│   ├── Pelicula.cpp
│   ├── Serie.cpp
│   ├── Episodio.cpp
│   └── Catalogo.cpp
├── data/
│   ├── peliculas.txt    ← Catálogo de películas
│   ├── series.txt       ← Catálogo de series
│   └── episodios.txt    ← Episodios y calificaciones
├── docs/
│   └── UML.md           ← Diagramas Mermaid y PlantUML
├── main.cpp
├── Makefile
└── README.md
```

---

##  Compilación y Ejecución

```bash
# Compilar
make

# Compilar y ejecutar
make run

# Limpiar ejecutable
make clean
```

**Requisito:** g++ con soporte C++17 (GCC 7+ o Clang 5+).

---

## 🖥️ Menú del Sistema

```
1. Cargar archivo de datos
2. Mostrar los videos en general con una cierta calificación o de un cierto género
3. Mostrar los episodios de una determinada serie con una calificación determinada
4. Mostrar las películas con cierta calificación
5. Calificar un video
0. Salir
```

---

##  Conceptos de POO Implementados

| Concepto                  | Implementación                                                         |
|---------------------------|------------------------------------------------------------------------|
| **Herencia**              | `Pelicula` y `Serie` heredan de `Video`                               |
| **Polimorfismo**          | `vector<shared_ptr<Video>>` + llamada virtual a `mostrarInfo()`        |
| **Clase abstracta**       | `Video` con método virtual puro `mostrarInfo() = 0`                   |
| **Sobreescritura**        | `mostrarInfo()` redefinido en `Pelicula` y `Serie`                    |
| **Sobrecarga de métodos** | `Catalogo::mostrarVideos()` con 3 firmas distintas                    |
| **Sobrecarga de operadores** | `operator>` y `operator<<` en `Video`; `operator<<` en `Episodio` |
| **Encapsulación**         | Atributos `private`/`protected`, acceso controlado por getters        |
| **Composición**           | `Serie` contiene `vector<Episodio>`                                   |
| **Excepciones personalizadas** | 5 clases de excepción propias con `try-catch`                    |
| **Lectura de archivos**   | `Catalogo::cargarDesdeArchivo()` con `ifstream`                       |

---

## 🔍 Detalle por Concepto

### Herencia (12 pts)

```
Video  (clase base abstracta)
├── Pelicula  (añade: director)
└── Serie     (añade: vector<Episodio>)
```

Archivo: `include/Pelicula.h`, `include/Serie.h`

```cpp
class Pelicula : public Video { ... };
class Serie    : public Video { ... };
```

---

### Modificadores de Acceso (10 pts)

| Modificador   | Atributos                                    | Razón                                                |
|---------------|----------------------------------------------|------------------------------------------------------|
| `private`     | `calificaciones` (Video), `director`, `episodios` | Solo accesibles desde la propia clase          |
| `protected`   | `id`, `nombre`, `duracion`, `genero`         | Accesibles desde clases hijas sin exponer al exterior|
| `public`      | Getters, `mostrarInfo()`, operadores         | Interfaz de uso para el resto del programa           |

---

### Clase Abstracta (12 pts)

`Video` es abstracta porque declara `mostrarInfo()` como método virtual puro:

```cpp
// include/Video.h
virtual void mostrarInfo() const = 0;
```

No se puede instanciar `Video` directamente. Solo sus clases derivadas concretas (`Pelicula`, `Serie`) pueden usarse.

---

### Sobreescritura (12 pts)

`mostrarInfo()` está redefinido en ambas clases hijas:

```cpp
// Pelicula.cpp
void Pelicula::mostrarInfo() const {
    std::cout << "[PELICULA] " << *this << " | Director: " << director << "\n";
}

// Serie.cpp
void Serie::mostrarInfo() const {
    std::cout << "[SERIE]    " << *this << " | Episodios: " << episodios.size() << "\n";
}
```

---

### Sobrecarga de Métodos (12 pts)

`Catalogo` implementa tres versiones de `mostrarVideos()`:

```cpp
void mostrarVideos();                          // Todos los videos
void mostrarVideos(const std::string& genero); // Filtrar por género
void mostrarVideos(double calMin);             // Filtrar por calificación mínima
```

Archivo: `include/Catalogo.h`, `src/Catalogo.cpp`

---

### Polimorfismo (12 pts)

El catálogo almacena películas y series como punteros a `Video`:

```cpp
std::vector<std::shared_ptr<Video>> videos;
```

Al llamar `v->mostrarInfo()`, C++ decide en tiempo de ejecución si ejecutar la versión de `Pelicula` o de `Serie`.

---

### Sobrecarga de Operadores (12 pts)

```cpp
// operator> — compara videos por promedio de calificaciones
bool Video::operator>(const Video& otro) const {
    return this->getPromedio() > otro.getPromedio();
}

// operator<< — imprime información resumida de cualquier Video
std::ostream& operator<<(std::ostream& os, const Video& v);

// operator<< — imprime información de un Episodio
std::ostream& operator<<(std::ostream& os, const Episodio& e);
```

---

### Excepciones (Opcional — puntos extra)

Se implementaron **5 excepciones personalizadas** en `include/Excepciones.h`:

| Excepción                      | Hereda de           | Cuándo se lanza                              |
|-------------------------------|---------------------|----------------------------------------------|
| `CalificacionInvalidaException`| `std::out_of_range` | Calificación fuera del rango 1-5             |
| `VideoNoEncontradoException`   | `std::runtime_error`| Se busca un video que no existe              |
| `SerieNoEncontradaException`   | `std::runtime_error`| Se busca una serie que no existe             |
| `GeneroInvalidoException`      | `std::invalid_argument` | Género no reconocido                     |
| `ArchivoNoEncontradoException` | `std::runtime_error`| No se puede abrir un archivo de datos        |

Todas se manejan con `try-catch` en `main.cpp`.

---

## Diagrama UML

Ver [`docs/UML.md`](docs/UML.md) — incluye versión **Mermaid** y **PlantUML**.

---

##  Formato de Archivos de Datos

**peliculas.txt**
```
id,nombre,duracion,genero,director
1,Inception,148,Accion,Christopher Nolan
```

**series.txt**
```
id,nombre,duracion_ep,genero
6,Breaking Bad,47,Drama
```

**episodios.txt**
```
nombre_serie,titulo_ep,temporada,cal1,cal2,...
Breaking Bad,Pilot,1,4,5,4
```

---

##  Autor

Proyecto integrador — Programación Orientada a Objetos, C++17.
