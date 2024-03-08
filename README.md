# Libreria SBI

Esto es un intento por tener ciertas funcionalidades concentradas en un solo repositorio

## Dependencias

Este proyecto tiene las siguientes dependencias:

 - LibPQ
 - OCILIB

 ## Como Compilar

Para hacer la compilacion, usando CMake y conan, es necesario ejecutar los siguientes comandos:

```console
$> conan install . --build=missing
$> cd build/generators
$> cmake ../.. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
$> cmake --build .
```

El cambio tiene que ver con los la ubicacion del CMakeLists.txt
