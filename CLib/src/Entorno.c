
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