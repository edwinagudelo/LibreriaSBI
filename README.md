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

El cambio tiene que ver con los la ubicacion del _CMakeLists.txt_ y hay que tener en cuenta que si existe el directorio _build_ o el directorio _out_ o el archivo _CMakeUserPresets.json_ debe eliminarse y luego proceder los comandos antes citados

