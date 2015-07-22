#include "CUtiles.h"

using namespace SBI;

CUtiles::CUtiles()
{
    //ctor
}

CUtiles::~CUtiles()
{
    //dtor
}

char* CUtiles::traerFechaActual(){
    char* retorno = new char[20];
    time_t t;
    struct tm* ltm;
    time(&t);
    ltm = localtime(&t);
    strftime(retorno,20,"%Y%m%d%H%M%S",ltm);
    return retorno;
}

int CUtiles::traerListaArchivos(string ruta, string mascara, vector<string> &archivos){
    // Variables
    struct stat sb;
    int cont = 0;
    string ruta_arch;
    DIR *dp;
    struct dirent *dirp;
    char *def_mascara = new char[strlen(mascara.c_str()) + 10];
    sprintf(def_mascara,"(%s)(.*)",mascara.c_str());
    regex val_mascara(def_mascara);

    // Valido si el directorio existe
    if( (stat(ruta.c_str(), &sb) == 0) && (S_ISDIR(sb.st_mode)) ){
        if( (dp = opendir(ruta.c_str())) != NULL ){
            while( (dirp = readdir(dp)) != NULL ){
                ruta_arch = ruta + "/" + string(dirp->d_name);
                stat(ruta_arch.c_str(), &sb);
                if(S_ISREG(sb.st_mode)){
                    if(regex_match(string(dirp->d_name),val_mascara)){
                        archivos.push_back(ruta_arch);
                        cont++;
                    }
                }
            }
        }
    }
    return cont;
}
