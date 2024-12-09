#ifndef ENTORNO_H
#define ENTORNO_H

/**
 * 
 */
int crearDirectorio(const char* ruta);

/**
 * 
 */
int renonmbrarDirectorio(const char* oldPath, const char* newPath);

/**
 * 
 */
int validarDirectorioExiste(const char* path);

/**
 * 
 */
int borrarDirectorio(const char* path);

#endif