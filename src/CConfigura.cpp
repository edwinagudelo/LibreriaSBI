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

string CConfigura::getParam(string llave){
    string retorno = "";
    if(configuraciones.count(llave) != 0){ // la llave existe
        map <string,int> mptmp = configuraciones[llave];
        retorno = mptmp.begin()->first;
    }
    return retorno;
}

bool CConfigura::setParam(string llave, string valor){
    if(configuraciones.count(llave) != 0){
        if(modificable == 0){
            return false;
        }
        cerr<<"Se sobreescribira "<<llave<<endl;
    }
    map<string,int> tmp;
    tmp[valor] = (int)(this->NO_TIPO);
    configuraciones[llave] = tmp;
    return true;
}

bool CConfigura::setParam(string llave, string valor, int tipo){
    if(configuraciones.count(llave) != 0){
        if(modificable == 0){
            return false;
        }
        cerr<<"Se sobreescribira "<<llave<<endl;
    }
    map<string,int> tmp;
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
    for(map<string , map<string, int> >::const_iterator ite = configuraciones.begin() ; ite != configuraciones.end() ; ite++){
        for(map<string, int>::const_iterator iti = ite->second.begin() ; iti != ite->second.end() ; iti++){
            cout<<"Parametro:"<<ite->first<<"\tValor:"<<iti-> first<<"\tTipo:"<<iti->second<<endl;
        }
    }
}


