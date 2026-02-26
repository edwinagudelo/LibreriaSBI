
// Implementacion de funciones de entorno
#include "Entorno.h"
#include <stdlib.h>
#include <string.h>

// MinGW on Windows needs Windows API, not POSIX
#if defined(__MINGW32__) || defined(__MINGW64__)
#include <io.h>
#include <direct.h>
#define USE_WINDOWS_API
#endif

int crearDirectorio(const char* ruta) {
    int retorno = 0;
    int estado = 0;
    errno = 0;
    #if defined(_MSC_VER) || defined(USE_WINDOWS_API)
    estado = _mkdir(ruta);
    #else
    estado = mkdir(ruta,S_IRWXU | S_IRWXG | S_IRWXO);
    #endif
    
    if(estado != 0){
        printf("Error creando el director %s > %d\n", ruta, errno);
        retorno = -1;
    }
        
    return retorno;
}

int renonmbrarDirectorio(const char* nombreAnt, const char* nombreNue) {
    int retorno = 0;
    if(validarDirectorioExiste(nombreAnt) == 1) {
        retorno = rename(nombreAnt, nombreNue);
    }
    return retorno;
}


int validarDirectorioExiste(const char* ruta) {

    #if defined(_MSC_VER) || defined(USE_WINDOWS_API)
    struct _stat info;
    if(_stat(ruta, &info) != 0)
        return 0;
    else if(info.st_mode & _S_IFDIR)
        return 1;
    else
        return 0;
    #else
    struct stat info;
    if(stat( ruta, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
    #endif

}

int borrarDirectorio(const char* ruta) {
    int retorno = 0;
    if(validarDirectorioExiste(ruta) == 1) {
        printf("Removing %s\n", ruta);
        #if defined(_MSC_VER) || defined(USE_WINDOWS_API)
        retorno = _rmdir(ruta);
        #else
        retorno = rmdir(ruta);
        #endif
    }
    return retorno;
}

char *leerVariableEntorno(const char *nombreVariableEntorno) {
    printf("Reading %s env var\n", nombreVariableEntorno);
    char *valor = getenv(nombreVariableEntorno);
    if (valor == NULL) {
        return NULL;
    } else {
        printf("Value is %s\n", valor);
        //valor = strdup(valor);
        return valor;
    }
}

int archivoExiste(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo) {
        fclose(archivo);
        return 1; // El archivo existe
    } else {
        return 0; // El archivo no existe
    }
}

int crearArchivoVacio(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo) {
        fclose(archivo);
        return 1; // Archivo creado exitosamente
    } else {
        return 0; // Error al crear el archivo
    }
}

int borrarArchivo(const char *nombreArchivo) {
    if (remove(nombreArchivo) == 0) {
        return 1; // Archivo borrado exitosamente
    } else {
        return 0; // Error al borrar el archivo
    }
}

int traerListaArchivos(const char *ruta, char ***archivos) {
    int result = 0;
    struct ArchivoTemporal *temp = NULL;
    struct ArchivoTemporal *head = NULL;
    
    if(archivos == NULL || ruta == NULL) {
        return -1; // Error: parámetros inválidos
    }

    temp = malloc(sizeof(struct ArchivoTemporal));
    if (temp == NULL) { // Error al reservar memoria
        return -1;
    }
    head = temp; // Guardar la referencia al inicio de la lista
    temp->nombreArchivo = NULL;
    temp->siguiente = NULL;


    #if defined(_MSC_VER) || defined(USE_WINDOWS_API)
    struct _finddata_t c_file;
    intptr_t hFile;
    char* ruta_completa = malloc(strlen(ruta) + 10);
    if (ruta_completa == NULL){
        free(temp);
        return -1; // Error al reservar memoria
    }
    sprintf(ruta_completa, "%s\\*.*", ruta);
    hFile = _findfirst(ruta_completa, &c_file);
    if (hFile == -1) {
        free(temp);
        free(ruta_completa);
        return 0; // No se encontraron archivos
    }
    do {

        if ((c_file.attrib & _A_SUBDIR) == 0) {
            temp->nombreArchivo = malloc(strlen(c_file.name) + 1);
            if (temp->nombreArchivo == NULL) {
                _findclose(hFile);
                free(temp);
                free(ruta_completa);
                return -1; // Error al reservar memoria
            }
            strcpy(temp->nombreArchivo, c_file.name);
            temp->siguiente = malloc(sizeof(struct ArchivoTemporal));
            if (temp->siguiente == NULL) {
                _findclose(hFile);
                free(temp->nombreArchivo);
                free(temp);
                free(ruta_completa);
                return -1; // Error al reservar memoria
            }
            temp = temp->siguiente;
            temp->nombreArchivo = NULL; // Inicializar el siguiente nodo}
            temp->siguiente = NULL; // Inicializar el siguiente nodo

            result++;
        }
    } while (_findnext(hFile, &c_file) == 0);
    _findclose(hFile);
    free(ruta_completa);
    free(temp); // Liberar el último nodo temporal
    #else
    // Implementación para sistemas POSIX (Linux/macOS)
    #include <dirent.h>
    DIR *dir = opendir(ruta);
    if (dir == NULL) {
        free(temp);
        return -1; // Error al abrir el directorio
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        size_t len = strlen(entry->d_name);
        temp->nombreArchivo = malloc(sizeof(char) * (len + 1));
        if (temp->nombreArchivo == NULL) {
            closedir(dir);
            free(temp);
            return -1; // Error al reservar memoria
        }
        strcpy(temp->nombreArchivo, entry->d_name);
        temp->siguiente = malloc(sizeof(struct ArchivoTemporal));
        temp = temp->siguiente;
        temp->nombreArchivo = NULL; // Inicializar el siguiente nodo
        temp->siguiente = NULL; // Inicializar el siguiente nodo
        result++;
    }
    closedir(dir); 
    free(temp); // Liberar el último nodo temporal
    #endif

    if(result == 0) {
        free(temp);
        return 0; // No se encontraron archivos
    }
    *archivos = malloc(sizeof(char*) * result);

    if (*archivos != NULL) {
        // Liberar la memoria de la lista temporal
        struct ArchivoTemporal *current = head;
        int index = 0;
        while (current != NULL && current->nombreArchivo != NULL) {
            char *nombreArchivo = malloc(strlen(current->nombreArchivo) + 1);
            if (nombreArchivo != NULL) {
                strcpy(nombreArchivo, current->nombreArchivo);
                (*archivos)[index++] = nombreArchivo;
            }
            struct ArchivoTemporal *next = current->siguiente;
            free(current->nombreArchivo);
            free(current);
            current = next;
        }
    }

    return result; 
}

int traerListaArchivosConMascara(const char *ruta, const char *mascara, char ***archivos){
    int result = 0;
    char** listaArchivos = NULL;
    if (ruta == NULL || archivos == NULL) {
        return -1; // Error: parámetros inválidos
    }
    result = traerListaArchivos(ruta, &listaArchivos);
    if (result < 0) {
        return result; // Error al obtener la lista de archivos
    }

    *archivos = malloc(sizeof(char*) * result);
    if (*archivos == NULL) {
        free(listaArchivos);
        return -1; // Error al reservar memoria
    }

    int i;
    for (i = 0; i < result; i++) {
        (*archivos)[i] = listaArchivos[i];
    }
    free(listaArchivos);
    return result;
}

