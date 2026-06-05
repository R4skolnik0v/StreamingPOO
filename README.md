# 🎬 StreamingPOO — Sistema de Streaming en C++

Proyecto integrador para la materia de **Programación Orientada a Objetos**.  
Modela un servicio de streaming de video utilizando los principios fundamentales de POO en C++17.

---

## 📁 Estructura del Repositorio

```
StreamingPOO/
│
├── src/
│   ├── Video.cpp
│   ├── Pelicula.cpp
│   ├── Serie.cpp
│   └── Episodio.cpp
│
├── include/
│   ├── Video.h
│   ├── Pelicula.h
│   ├── Serie.h
│   └── Episodio.h
│
├── docs/
│   └── UML.md
│
├── README.md
└── main.cpp
```

---

## ⚙️ Compilación

```bash
g++ -std=c++17 -Wall -Iinclude main.cpp src/Video.cpp src/Pelicula.cpp src/Serie.cpp src/Episodio.cpp -o streaming
./streaming
```

Requiere: **g++ con soporte C++17** (GCC 7+, Clang 5+).

---

## 🧩 Conceptos de POO Utilizados

| Concepto             | Implementación                                                   |
|----------------------|------------------------------------------------------------------|
| **Herencia**         | `Pelicula` y `Serie` heredan de `Video`                         |
| **Polimorfismo**     | `vector<shared_ptr<Video>>` + llamada a `mostrarInfo()`         |
| **Clase abstracta**  | `Video` tiene el método virtual puro `mostrarInfo()`            |
| **Sobreescritura**   | `mostrarInfo()` redefinido en `Pelicula` y `Serie`              |
| **Sobrecarga**       | `operator>` y `operator<<` definidos en `Video`                 |
| **Excepciones**      | `std::out_of_range` y `std::runtime_error` con `try-catch`      |
| **Encapsulación**    | Atributos `private`/`protected`, acceso mediante getters        |
| **Composición**      | `Serie` contiene un `vector<Episodio>`                          |

---

## 📋 Reportes del Sistema

| # | Reporte                                  |
|---|------------------------------------------|
| 1 | Todos los videos con promedio            |
| 2 | Solo películas con promedio              |
| 3 | Solo series con promedio                 |
| 4 | Episodios de una serie específica        |
| 5 | Filtrar películas por género             |
| 6 | Filtrar series por género                |

---

## 🚨 Manejo de Excepciones

- **`std::out_of_range`** — Se lanza al agregar una calificación fuera del rango 1-5.
- **`std::runtime_error`** — Se lanza al buscar una serie que no existe en el catálogo.

---

## 🏗️ Diagrama UML

Ver [`docs/UML.md`](docs/UML.md) para el diagrama completo en formato Mermaid.

---

## 👤 Autor

Proyecto académico — Programación Orientada a Objetos, C++17.
