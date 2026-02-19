#ifndef ENTORNO_H
#define ENTORNO_H

#include <stdio.h>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <io.h> 
#endif

/***
 * Struct para almacenar la informacion temporal de un archivo
 */
struct ArchivoTemporal
{
    char* nombreArchivo; /**< Nombre del archivo temporal */
    struct ArchivoTemporal* siguiente; /**< Puntero al siguiente archivo temporal */
};


/**
 * Section de funciones para la manipulacion de directorios
 */

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

/**
 * Section de funciones para la manipulacion de variables de entorno
 */

/**
 * 
 */
char *leerVariableEntorno(const char *nombreVariableEntorno);

/**
 * 
 */
int archivoExiste(const char *nombreArchivo);

/**
 * 
 */
int crearArchivoVacio(const char *nombreArchivo);

/**
 * 
 */
int borrarArchivo(const char *nombreArchivo);

/**
 * @brief Get list of files in a directory
 * @param ruta Directory path
 * @param archivos Pointer to array of file names
 * @return Number of files found, or -1 on error
 */
int traerListaArchivos(const char *ruta, char ***archivos);

/**
 * @brief Get list of files in a directory with mask filter
 * @param ruta Directory path
 * @param mascara File mask/pattern filter
 * @param archivos Pointer to array of file names
 * @return Number of files found, or -1 on error
 */
int traerListaArchivosConMascara(const char *ruta, const char *mascara, char ***archivos);

#endif