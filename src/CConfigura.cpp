#include "CConfigura.h"

CConfigura::CConfigura()
{
    //ctor
    modificable = false;
}

CConfigura::~CConfigura()
{
    //dtor
    // just free memory
    this->configuraciones.clear();
}

std::string CConfigura::getParam(const std::string& llave){
    std::string retorno = "";
    if(configuraciones.count(llave) != 0){ // la llave existe
        return configuraciones[llave];
    }
    return retorno;
}

bool CConfigura::setParam(const std::string& llave, const std::string& valor){
    if(configuraciones.count(llave) != 0){
        if(modificable == 0){
            return false;
        }
        std::cerr << "Se sobreescribira" << llave <<std::endl;
    }
    configuraciones.insert(std::pair<std::string, std::string>(llave, valor)) ;
    return true;
}

bool CConfigura::getModif(){
    return modificable;
}

void CConfigura::setModif(bool modif){
    modificable = modif;
    return;
}

void CConfigura::mostrar(){
    for(std::map<std::string , std::string >::const_iterator ite = configuraciones.begin() ; ite != configuraciones.end() ; ite++){
        std::cout << "Parametro:" << ite->first << "\tValor:" << ite->second << std::endl;
    }
}


