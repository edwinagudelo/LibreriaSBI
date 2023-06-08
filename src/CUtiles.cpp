#include "CUtiles.h"

using namespace SBI;

const char* CUtiles::traerFechaActual(char* formato){
    char* retorno = new char[20];
    time_t t;
    struct tm* ltm;
    time(&t);
    ltm = localtime(&t);
    strftime(retorno,20,formato,ltm);
    return retorno;
}

const char* CUtiles::traerFechaActual(){
    return CUtiles::traerFechaActual("%Y%m%d%H%M%S");
}

int CUtiles::traerListaArchivos(const std::string ruta, const std::string mascara, std::vector<std::string> &archivos){
    struct stat sb;
    int cont = 0;
    std::string sep = CUtiles::carSeparador();

    #ifdef _DEBUG
    std::cout<<"Validando:"<<ruta<<std::endl;
    #endif

    // Valido si el directorio existe
    int itmp = CUtiles::dirExiste(ruta.c_str());
    if(itmp < 0){
        #ifdef _DEBUG
        std::cout<<"Error:"<<strerror(errno)<<">>"<<ruta.c_str()<<std::endl;
        #endif
        return 0;
    }
    // Ahora bifurco segun el entorno en el que este compilando
    #ifdef _WIN32
        #ifdef _MSC_VER
        struct _finddata_t c_file;
        intptr_t hFile;
        char* current_directory ;
        if( !((current_directory = _getcwd(NULL, 0)) == NULL) ){
            _chdir(ruta.c_str());
            if( (hFile = _findfirst(mascara.c_str(), &c_file)) != -1){
                do{
                    archivos.push_back(std::string(c_file.name));
                    cont++;
                }while(_findnext(hFile, &c_file) == 0);
            }
            _chdir(current_directory);
        }
        #else
        std::string ruta_arch;
        char *def_mascara = new char[strlen(mascara.c_str()) + 10];
        sprintf(def_mascara,"(%s)(.*)",mascara.c_str());
        std::regex val_mascara("(.+?)(\\.BGH)");
        DIR *dp;
        struct dirent *dirp;
        if((stat(ruta.c_str(), &sb) == 0)){
            if( (S_ISDIR(sb.st_mode)) ){
                if( (dp = opendir(ruta.c_str())) != NULL ){
                    while( (dirp = readdir(dp)) != NULL ){
                        ruta_arch = ruta + sep + std::string(dirp->d_name);
                        stat(ruta_arch.c_str(), &sb);
                        if(S_ISREG(sb.st_mode)){
                            if(regex_match(std::string(dirp->d_name),val_mascara)){
                                archivos.push_back(ruta_arch);
                                cont++;
                            }
                        }
                    }
                }
            }
        }    
        #endif
    #else
    try{
        glob_t gres;
        char *cstr_ruta = new char[sizeof(char) * (ruta.size() + sep.size() + mascara.size()) + 1];
        sprintf(cstr_ruta,"%s%s%s",ruta.c_str(),sep.c_str(), mascara.c_str());
        int gtmp = glob(cstr_ruta, 0, NULL, &gres);
        if( gtmp == 0){
            for(size_t i = 0; i< gres.gl_pathc; i++){
                archivos.push_back(std::string(*(gres.gl_pathv)));
                cont++;
            }
        }
        else{
            cout<<"Error escaneando directorio(GLOB):"<<strerror(errno)<<">>"<<ruta.c_str()<<endl;
        }
        if(cstr_ruta != NULL)
            delete cstr_ruta;
    }catch(exception &ex){
        cout<<"Error al buscar archivos:"<<ex.what()<<endl;
    }
    #endif
    return cont;
}

int CUtiles::traerListaArchivos(std::string ruta, std::string mascara, std::vector<std::string> &archivos, int ord){
    int tcnt = traerListaArchivos(ruta, mascara, archivos);
    if (ord != 0){
        sort(archivos.begin(),archivos.end());
    }
    return tcnt;
}

int CUtiles::traerListaArchivos(std::string ruta, std::vector<std::string> &archivos){
    std::string mascara = "*";
    int tcnt = traerListaArchivos(ruta, mascara, archivos);
    return tcnt;
}

int CUtiles::split(const std::string& cadena, const char& sep, std::vector<std::string> &retorno){
    std::string tsep(1,sep);
    size_t substart = 0;
    size_t cant_sep;
    retorno.clear();
    while( (cant_sep = cadena.find(tsep, substart)) != std::string::npos ){
        retorno.push_back(cadena.substr(substart, cant_sep - substart));
        substart = cant_sep + 1;
    }
    retorno.push_back(cadena.substr(substart, cadena.size()));
    return retorno.size();
}

std::string CUtiles::getFileName(const std::string& s) {
   char sep = CUtiles::carSeparador()[0];
   size_t i = s.rfind(sep, s.length());
   if (i != std::string::npos) {
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

int CUtiles::cambiaCaracter(char* str, char car_o, char car_d ){
    unsigned int i=0;
    int cambiados = 0;
    while( str[i] ){
        if(str[i] == car_o){
            str[i] = car_d;
            cambiados++;
        }
        i++;
    }
    return cambiados;
}

const char* CUtiles::carSeparador(){
    char *sep = new char[2];
    strcpy(sep,"/");
    #ifdef _WIN32
        strcpy(sep,"\\");
    #endif
    return sep;
}


const char* CUtiles::calcularReferencia(const char* num){
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
    #ifndef _WIN32
    estado = mkdir(ruta,S_IRWXU | S_IRWXG | S_IRWXO);
    #else
    estado = mkdir(ruta);
    #endif
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

const std::string CUtiles::getOSUsername(){
    std::string retorno(getenv("USER"));
    return retorno;
}

int CUtiles::valAcceso(const char *path){
    int retorno = 0;
    #ifndef _WIN32
    if( access(path, R_OK) == -1 ){
        retorno = 1;
    }
    #else
    if( access(path, 04) == -1 ){
        retorno = 1;
    }
    #endif
    return retorno;
}
