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
    string sep = "/";
    #ifdef _WIN32
        sep = "\\";
    #endif

    // Valido si el directorio existe
    if( (stat(ruta.c_str(), &sb) == 0) && (S_ISDIR(sb.st_mode)) ){
        if( (dp = opendir(ruta.c_str())) != NULL ){
            while( (dirp = readdir(dp)) != NULL ){
                ruta_arch = ruta + sep + string(dirp->d_name);
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

void CUtiles::split(string cadena, char sep, vector<string> &retorno){
    string tsep(1,sep);
    size_t substart = 0;
    size_t cant_sep;
    retorno.clear();
    while( (cant_sep = cadena.find(tsep, substart)) != string::npos ){
        retorno.push_back(cadena.substr(substart, cant_sep - substart));
        substart = cant_sep + 1;
    }
    retorno.push_back(cadena.substr(substart, cadena.size()));
    return;
}

string CUtiles::getFileName(const string& s) {

   char sep = '/';
   #ifdef _WIN32
    sep = '\\';
   #endif
   size_t i = s.rfind(sep, s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }
   return("");

}
