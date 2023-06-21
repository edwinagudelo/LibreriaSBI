#include "include/CConfigura.h"

CConfigura::CConfigura()
{
    //ctor
    modificable = 0;
}

CConfigura::~CConfigura()
{
    //dtor
}

std::string CConfigura::getParam(std::string llave){
    std::string retorno = "";
    if(configuraciones.count(llave) != 0){ // la llave existe
        std::map <std::string,int> mptmp = configuraciones[llave];
        retorno = mptmp.begin()->first;
    }
    return retorno;
}

bool CConfigura::setParam(std::string llave, std::string valor){
    if(configuraciones.count(llave) != 0){
        if(modificable == 0){
            return false;
        }
        std::cerr << "Se sobreescribira" << llave <<std::endl;
    }
    std::map<std::string,int> tmp;
    tmp[valor] = (int)(this->NO_TIPO);
    configuraciones[llave] = tmp;
    return true;
}

bool CConfigura::setParam(std::string llave, std::string valor, int tipo){
    if(configuraciones.count(llave) != 0){
        if(modificable == 0){
            return false;
        }
        std::cerr << "Se sobreescribira" << llave <<std::endl;
    }
    std::map<std::string,int> tmp;
    tmp[valor] = tipo;
    configuraciones[llave] = tmp;
    return true;
}

int CConfigura::getModif(){
    return modificable;
}

void CConfigura::setModif(int modif){
    modificable = modif;
    return;
}

void CConfigura::mostrar(){
    for(std::map<std::string , std::map<std::string, int> >::const_iterator ite = configuraciones.begin() ; ite != configuraciones.end() ; ite++){
        for(std::map<std::string, int>::const_iterator iti = ite->second.begin() ; iti != ite->second.end() ; iti++){
            std::cout << "Parametro:" << ite->first << "\tValor:" << iti->first << "\tTipo:" << iti->second << std::endl;
        }
    }
}


