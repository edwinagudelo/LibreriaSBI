# Libreria SBI

Esto es un intento por tener ciertas funcionalidades concentradas en un solo repositorio

## Dependencias

Este proyecto tiene las siguientes dependencias:

 - LibPQ
 - OCILIB

 ## Como Compilar

Para hacer la compilacion, usando CMake y conan, es necesario ejecutar los siguientes comandos:

```console
$> conan install . --output-folder=build --build=missing -pr=mscvdebug
$> cd build
$> cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
```

Con esto se validara el codigo usando el perfil "msvcdebug", pero eso depende de los perfiles que se estén manejando.
