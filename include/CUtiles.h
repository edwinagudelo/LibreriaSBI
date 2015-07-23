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
#include <vector>
#include <algorithm>

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
            /** Funcion para hacer split de una cadena */
            static void split(string cadena, char sep, vector<string> &retorno);
            /** Funcion para retornar el nombre de un archivo */
            static string getFileName(const string& s);
        protected:
        private:
    };
}

#endif // CUTILES_H
