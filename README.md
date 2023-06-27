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
