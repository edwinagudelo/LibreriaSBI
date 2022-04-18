#ifndef CUTILES_H
#define CUTILES_H

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#if __cplusplus > 201100L
#include <regex>
#endif
#include <vector>
#include <algorithm>
#include <ctype.h>
#ifndef _WIN32
#include <glob.h>
#endif


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
            /** Funcion para calcular fecha actual con formato*/
            static char* traerFechaActual(char* formato);
            /** Funcion para escanear archivos en un directorio a partir de una mascara */
            static int traerListaArchivos(string ruta, string mascara, vector<string> &archivos);
            /** Funcion para escanear archivos en un directorio a partir de una mascara y ordenados */
            static int traerListaArchivos(string ruta, string mascara, vector<string> &archivos, int ord);
            /** Funcion para hacer split de una cadena */
            static void split(string cadena, char sep, vector<string> &retorno);
            /** Funcion para retornar el nombre de un archivo */
            static string getFileName(const string& s);
            /** Funcion para eliminar espacios*/
            static void retiraEspacios(char* str);
            /** Funcion para retornar el caracter separador de SO*/
            static char* carSeparador();
            /** Funcion para calcular el digito de chequeo de una referencia*/
            static char* refPago(char* num);
            /** Funcion para retirar un caracter*/
            static void retiraCaracter(char* str, char car);
            /** Funcion para cambiar un caracter*/
            static void cambiaCaracter(char* str, char car_o, char car_d);
            /** Funcion para crear un directorio */
            static int crearDirectorio(char* ruta);
            /** Funcion para saber si un directorio existe */
            static int dirExiste(const char *path);
            /** Funcion para retornar el nombre del usuario de sistema operativo */
            static string getOSUsername();
            /** Funcion para validar el acceso a un archivo */
            static int valAcceso(const char *path);

        protected:
        private:
    };
}

#endif // CUTILES_H
