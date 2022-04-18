#include "include/CUtiles.h"

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

char* CUtiles::traerFechaActual(char* formato){
    char* retorno = new char[20];
    time_t t;
    struct tm* ltm;
    time(&t);
    ltm = localtime(&t);
    strftime(retorno,20,formato,ltm);
    return retorno;
}

int CUtiles::traerListaArchivos(const string ruta, const string mascara, vector<string> &archivos){
    // Variables
    struct stat sb;
    int cont = 0;
    //sprintf(def_mascara,"%s",mascara.c_str());
    string sep = "/";
    #ifdef _WIN32
        sep = "\\";
    #endif

    cout<<"Validando:"<<ruta<<endl;

    // Valido si el directorio existe
    int itmp = stat(ruta.c_str(), &sb);
    if(itmp < 0){
        cout<<"Error:"<<strerror(errno)<<">>"<<ruta.c_str()<<endl;
        return 0;
    }
    // Ahora bifurco segun el entorno en el que este
    #ifdef _WIN32
    string ruta_arch;
    char *def_mascara = new char[strlen(mascara.c_str()) + 10];
    sprintf(def_mascara,"(%s)(.*)",mascara.c_str());
    regex val_mascara("(.+?)(\\.BGH)");
    DIR *dp;
    struct dirent *dirp;
    if((stat(ruta.c_str(), &sb) == 0)){
        if( (S_ISDIR(sb.st_mode)) ){
            if( (dp = opendir(ruta.c_str())) != NULL ){
                while( (dirp = readdir(dp)) != NULL ){
                    ruta_arch = ruta + sep + string(dirp->d_name);
                    stat(ruta_arch.c_str(), &sb);
                    if(S_ISREG(sb.st_mode)){
                        if(regex_match(string(dirp->d_name),val_mascara)){
                        //if(regex_match("*",val_mascara)){
                            archivos.push_back(ruta_arch);
                            cont++;
                        }
                    }
                }
            }
        }
    }
    #else
    try{
        glob_t gres;
        char *cstr_ruta = new char[sizeof(char) * (ruta.size() + sep.size() + mascara.size()) + 1];
        //const string ruta_completa = (ruta + sep + mascara);
        sprintf(cstr_ruta,"%s%s%s",ruta.c_str(),sep.c_str(), mascara.c_str());
        //int gtmp = glob(ruta_completa.c_str(), 0, NULL, &gres);
        int gtmp = glob(cstr_ruta, 0, NULL, &gres);
        if( gtmp == 0){
            for(size_t i = 0; i< gres.gl_pathc; i++){
                //ruta_arch = ruta + sep + string(*(gres.gl_pathv));
                archivos.push_back(string(*(gres.gl_pathv)));
                cont++;
            }
        }
        else{
            cout<<"Error escaneando directorio(GLOB):"<<strerror(errno)<<">>"<<ruta.c_str()<<endl;
        }
        if(cstr_ruta != NULL)
            delete cstr_ruta;
        //ruta_completa.swap(ruta_completa);
    }catch(exception &ex){
        cout<<"Error al buscar archivos:"<<ex.what()<<endl;
    }
    #endif // _WIN32
    return cont;
}

int CUtiles::traerListaArchivos(string ruta, string mascara, vector<string> &archivos, int ord){
    //
    int tcnt = traerListaArchivos(ruta, mascara, archivos);
    if (ord != 0){
        sort(archivos.begin(),archivos.end());
    }
    return tcnt;
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

void CUtiles::retiraEspacios(char* str){
    unsigned int i=0;
    while( (!(isspace(str[i]))) && (isdigit(str[i])) ){
        i++;
    }
    str[i] = '\0';
}


void CUtiles::retiraCaracter(char* str, char car){
    unsigned int i=0;
    unsigned int j=i;
    while( str[i] ){
        if(str[i] != car && isprint(str[i])){
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

void CUtiles::cambiaCaracter(char* str, char car_o, char car_d ){
    unsigned int i=0;
    while( str[i] ){
        if(str[i] == car_o){
            str[i] = car_d;
        }
        i++;
    }
}

char* CUtiles::carSeparador(){
    char *sep = new char[2];
    strcpy(sep,"/");
    #ifdef _WIN32
        strcpy(sep,"\\");
    #endif
    return sep;
}


char* CUtiles::refPago(char* num){
    char* retorno;
    int largo = strlen(num);
    int suma = 0;
    int modulo = 0;
    int i;
    int base = 3;
    for(i = (largo - 1); i >= 0 ; i--){
        suma+=(((num[i] - 48)>10 ? 0 : (num[i] - 48))*base); // la base
        base+=2;
        if(base == 11)
            base = 3;
    }
    modulo = suma%11;
    if((modulo != 0) && (modulo != 1))
        modulo = 11 - modulo;
    retorno = new char[strlen(num) + 3];
    sprintf(retorno,"%s%d",num,modulo);
    return retorno;
}

int CUtiles::crearDirectorio(char* ruta){
    int retorno = 0;
    int estado = 0;
    estado = mkdir(ruta,S_IRWXU | S_IRWXG | S_IRWXO);
    if(estado != 0)
        retorno = -1;
    return retorno;
}


int CUtiles::dirExiste(const char *path){
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

string CUtiles::getOSUsername(){
    string retorno(getenv("USER"));
    return retorno;
}

int CUtiles::valAcceso(const char *path){
    int retorno = 0;
    if( access(path, R_OK) == -1 ){
        retorno = 1;
    }
    return retorno;
}
