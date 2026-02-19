# Libreria SBI

![SBI Library CI](https://github.com/edwinagudelo/LibreriaSBI/actions/workflows/sbilib_pipeline.yml/badge.svg)

Esto es un intento por tener ciertas funcionalidades concentradas en un solo repositorio

## Dependencias

Este proyecto tiene las siguientes dependencias:

- LibPQ
- OCILIB
- Catch2 (para pruebas unitarias)

## Como Compilar

Para hacer la compilacion, usando CMake y conan, es necesario ejecutar los siguientes comandos:

```console
$> conan install . --output-folder=build --build=missing
$> cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release
$> cmake --build build --config Release
```

### Compilar solo la librería CLib

```console
$> cmake --build build --config Release --target sbi_clib
```

### Compilar las pruebas unitarias

```console
$> cmake --build build --config Release --target configura_test entorno_test
```

## Ejecutar Pruebas Unitarias

Después de compilar las pruebas, puedes ejecutarlas con:

```console
$> cd build/CLib/tests
$> ctest --output-on-failure -C Release
```

O ejecutar las pruebas directamente:

```console
# Windows
$> $env:PATH="$PWD\..\..\CLib\Release;$env:PATH"
$> .\Release\configura_test.exe
$> .\Release\entorno_test.exe

# Linux/macOS
$> export LD_LIBRARY_PATH=../../CLib:$LD_LIBRARY_PATH
$> ./configura_test
$> ./entorno_test
```

## Integración Continua

El proyecto utiliza GitHub Actions para ejecutar automáticamente las pruebas en múltiples plataformas:
- Windows (MSVC)
- Linux (GCC)
- macOS (Clang)

El pipeline se ejecuta automáticamente en cada push o pull request a las ramas `main` y `develop`.

Ver más detalles en [.github/workflows/README.md](.github/workflows/README.md)

## Estructura del Proyecto

```
LibreriaSBI/
├── CLib/                  # Librería C con utilidades
│   ├── include/          # Archivos de cabecera
│   ├── src/              # Implementaciones
│   └── tests/            # Pruebas unitarias con Catch2
├── CppLib/               # Librería C++
├── Hardware/             # Módulos de hardware
├── .github/
│   └── workflows/        # Pipelines de CI/CD
└── conanfile.txt         # Dependencias del proyecto
```

## Notas

- Si existe el directorio _build_ o el directorio _out_ o el archivo _CMakeUserPresets.json_ debe eliminarse antes de proceder con los comandos de compilación
- El proyecto requiere CMake 3.20 o superior
- Se recomienda usar Conan 2.x para la gestión de dependencias
