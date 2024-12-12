
#include "Entorno.h"

int crearDirectorio(const char* ruta) {
    int retorno = 0;
    int estado = 0;
    #ifndef _WIN32
    estado = mkdir(ruta,S_IRWXU | S_IRWXG | S_IRWXO);
    #else
    estado = mkdir(ruta);
    #endif
    
    if(estado != 0)
        retorno = -1;
    return retorno;
}

int renonmbrarDirectorio(const char* nombreAnt, const char* nombreNue) {
    int retorno = 0;
    if(validarDirectorioExiste(nombreAnt) == 0) {
        retorno = rename(nombreAnt, nombreNue);
    }
    return retorno;
}


int validarDirectorioExiste(const char* ruta) {
    struct stat info;

    if(stat( ruta, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

int borrarDirectorio(const char* ruta) {
    int retorno = 0;
    if(validarDirectorioExiste(ruta) == 0) {
        retorno = remove(ruta);
    }
    return retorno;
}