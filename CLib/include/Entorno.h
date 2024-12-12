#ifndef ENTORNO_H
#define ENTORNO_H

#include <stdio.h>
#include <sys/stat.h>
/**
 * 
 */
int crearDirectorio(const char* ruta);

/**
 * 
 */
int renonmbrarDirectorio(const char* nombreAnt, const char* nombreNue);

/**
 * 
 */
int validarDirectorioExiste(const char* ruta);

/**
 * 
 */
int borrarDirectorio(const char* ruta);

#endif