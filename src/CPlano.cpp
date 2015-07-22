#include "CPlano.h"

CPlano::CPlano()
{
    //ctor
    ruta = "";
    separador = '=';
    comentador = '#';
}

CPlano::~CPlano()
{
    //dtor
}

void CPlano::setSeparador(char val){
    separador = val;
    return;
}

char CPlano::getSeparador(){
    return separador;
}

void CPlano::setRuta(string val){
    ruta = val;
    return;
}

string CPlano::getRuta(){
    return ruta;
}

void CPlano::setComentador(char val){
    comentador = val;
    return;
}

char CPlano::getComentador(){
    return comentador;
}

int CPlano::cargar(){
    int parametros = 0;
    int lineas = 0;
    if(ruta == ""){
        cerr<<"No esta definida la ruta de carga"<<endl;
        return -1;
    }
    /*if( access(ruta.c_str(), R_OK) == -1 ){
        cerr<<"No se tiene acceso al archivo "<<ruta<<endl;
        return -2;
    }*/
    try{
        ifstream is;
        string lin;
        string lla_val[2];
        is.open(ruta.c_str());
        while(!is.eof()){ // Leo linea a linea
            lineas++;
            getline(is,lin);
            if(lin.size() < 2)
                continue;
            if(lin.c_str()[0] == comentador)
                continue;
            split(lin,separador,lla_val);
            if(lla_val[0] == "")
                continue;
            if(!setParam(lla_val[0], lla_val[1])){
                cerr<<"No se puede agregar la linea:"<<lin<<endl;
                continue;
            }
            parametros++;
        }
        is.close();
    }catch(exception ex){
        cerr<<"Error al intentar abrir el archivo:"<<ruta<<endl;
        cerr<<"Error:"<<ex.what()<<endl;
        return -3;
    }
    return parametros;
}

void CPlano::split(string cadena, char sep, string *retorno){
    //string retorno[2];
    string tsep(1,sep);
    retorno[0] = "";
    retorno[1] = "";
    int itmp = (int)cadena.find(tsep);
    if(itmp != (int)string::npos){
        string llave = cadena.substr(0,(int)cadena.find(tsep));
        string valor = cadena.substr((int)cadena.find(tsep) + 1, (int)cadena.size());
        retorno[0] = llave;
        retorno[1] = valor;
    }
    return;// retorno;
}
