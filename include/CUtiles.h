#ifndef CUTILES_H
#define CUTILES_H

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

namespace SBI{
    class CUtiles
    {
        public:
            /** Default constructor */
            CUtiles();
            /** Default destructor */
            virtual ~CUtiles();
            /** Funcion para calcular fecha */
            static char* traerFechaActual();
            /** Funcion para escanear archivos en un directorio a partir de una mascara */
            static int traerListaArchivos(string ruta, string mascara, vector<string> &archivos);

        protected:
        private:
    };
}

#endif // CUTILES_H
