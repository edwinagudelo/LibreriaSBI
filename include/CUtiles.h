#ifndef CUTILES_H
#define CUTILES_H

#include <algorithm>
#include <ctime>
#include <ctype.h>
#include <errno.h>
#include <iostream>
#include <regex>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#ifdef __GNUC__
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#else
#include <direct.h>
#include <io.h>
#endif

namespace SBI{
    /***
     * @brief Esta clase tiene funciones utiles que son usadas desde cualquier otra clase
    */
    class CUtiles
    {
        public:
            /** Default constructor */
            CUtiles() = delete;
            /** Default destructor */
            virtual ~CUtiles() = delete;
            /** Funcion para calcular fecha actual con formato*/
            static const char* traerFechaActual(char* formato);
            /** Funcion para calcular fecha */
            static const char* traerFechaActual();
            /** Funcion para escanear archivos en un directorio a partir de una mascara */
            static int traerListaArchivos(std::string ruta, std::string mascara, std::vector<std::string> &archivos);
            /** Funcion para escanear archivos en un directorio a partir de una mascara y ordenados */
            static int traerListaArchivos(std::string ruta, std::string mascara, std::vector<std::string> &archivos, int ord);
            /** Funcion para escanear archivos en un directorio a partir de una mascara y ordenados */
            static int traerListaArchivos(std::string ruta, std::vector<std::string> &archivos);
            /** Funcion para hacer split de una cadena */
            static int split(const std::string& cadena, const char& sep, std::vector<std::string>& retorno);
            /** Funcion para retornar el nombre de un archivo */
            static std::string getFileName(const std::string& s);
            /** Funcion para eliminar espacios*/
            static void retiraEspacios(char* str);
            /** Funcion para retornar el caracter separador de SO*/
            static const char* carSeparador();
            /** Funcion para calcular el digito de chequeo de una referencia*/
            static const char* calcularReferencia(const char* num);
            /** Funcion para retirar un caracter*/
            static void retiraCaracter(char* str, char car);
            /** Funcion para cambiar un caracter*/
            static int cambiaCaracter(char* str, char car_o, char car_d);
            /** Funcion para crear un directorio */
            static int crearDirectorio(char* ruta);
            /** Funcion para saber si un directorio existe */
            static int dirExiste(const char *path);
            /** Funcion para retornar el nombre del usuario de sistema operativo */
            static const std::string getOSUsername();
            /** Funcion para validar el acceso a lectura de un archivo */
            static int valAcceso(const char *path);
    };
}

#endif // CUTILES_H
