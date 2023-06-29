# Repositorio de Testeo del TP3

La repo para pasar en limpio está [acá.](https://github.com/Dante-010/tp3-algo2)

Esta repo está hecha para tener separados los tests unitarios de cada componente y los tests generales de la catedra en la otra repo. Hay cosas atadas con alambre
porque no estoy 100% seguro de como usar los Google Tests.

En `src/` van los archivos fuente de las definiciones, estructuras, implementaciones, etc. (`.h`, `.cpp`, `.hpp`)

En `tests/` van los tests. Por ahora hay un solo archivo con múltiples suites porque no estaba seguro de cómo tener varios archivos.

En `CMakeLists.txt` armo el ejecutable `correrTests` con `tests.cpp`. Para crearlo desde cero hay que ejecutar lo siguiente:

```bash
# En la carpeta del proyecto

# Buildear el proyecto
cmake . 

# Generar el ejecutable de tests
make correrTests

# Correr los tests
./correrTests
```

Está funcionando bien en Ubuntu 22 LTS

Adicionalmente, si el sistema operativo usa bash, hay dos scripts: `cleandir` y `cleanbuild`.
El primero limpia todos los archivos creados por CMake y Make. El segundo primero ejecuta `cleandir` y después buildea el proyecto y ejecuta los tests usando los comandos anteriores.

Hay un script más, `projsetup`, que ejecutado a través de
```sh
. ./projsetup.sh
```

(Importante el espacio entre los puntitos)
Setea la terminal desde la que estén para que los comandos `cleandir` y `cleanbuild` se puedan escribir así nomás (y aparte simplifica la ruta a la carpeta, que sólo ocupa espacio).
Además, crea otro comando `memcheck` que ejecuta Valgrind sobre el ejecutable `correrTests`.

---
# Sobre GitHub Actions

¡Ésta repo cuenta con GitHub Actions! En resumen significa que todos los cambios que hagan (cada vez que pusheen) se van a testear automáticamente, **sin necesidad de ejecutarlos en su máquina.**

Si quieren revisarlo, en `/.github/workflows/c-cpp.yml` está especificado _qué_ debe ejecutarse cada vez que pushean un archivo. La cosa es así: Usamos CMake para crear el archivo Makefile, y usamos Make para compilar según el Makefile. Como el `main` (entry point) del proyecto usa los Google Tests, entonces el archivo compilado son directamente esos tests. Lo único que hace GitHub Actions es, según el `.yml` que escribí, ejecutar `cmake . && make correrTests && ./correrTests`, como lo haríamos normalmente.

Tengo pendiente agregar una configuración para Valgrind, pero por ahora me interesa que se ejecuten los tests nomás.


---

# TODO List - Cosas pendientes
*Objetivo:* Pasar todos los tests de la cátedra sin memory leaks.

- [x] Corroborar que los parámetros por copia no arruinen las complejidades.
  - [x] (Opcional) Anotar las complejidades
- [x] Pasar el pseudocódigo a C++
- [ ] Escribir tests para cada componente.
  - [x] maxHeap
  - [x] minHeap
  - [x] Puesto
  - [ ] Lollapatuza
- [x] Pasar los tests personales y que cada componente no leakee.
  - [x] maxHeap
  - [x] minHeap
  - [x] Puesto
  - [x] Lollapatuza
- [x] Pasar todos los tests de la cátedra sin que leakee.
- [x] Encapsular y limpiar el código.
  - [x] maxHeap
  - [x] minHeap
  - [x] Puesto
  - [x] Lollapatuza
