#include "CPlano.h"
#include "CUtiles.h"

CPlano::CPlano()
{
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

void CPlano::setRuta(std::string val){
    ruta = val;
    return;
}

std::string CPlano::getRuta(){
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
        std::cerr << "No esta definida la ruta de carga" << std::endl;
        return -1;
    }
    try{
        std::ifstream is;
        std::string lin;
        std::string lla_val[2];
        std::vector<std::string> split_result;
        is.open(ruta.c_str());
        while(!is.eof()){ // Leo linea a linea
            lineas++;
            std::getline(is,lin);
            if(lin.size() < 2)
                continue;
            if(lin.c_str()[0] == comentador)
                continue;
            
            SBI::CUtiles::separarCadena(lin, separador, split_result);
            
            if(split_result.size() != 2){
                std::cerr << "Linea " << lineas << " es inconsistente con el numero de elementos" << std::endl;
                continue;
            }
           
            if(split_result[0] == "")
                continue;

            if(!setParam(lla_val[0], lla_val[1])){
                std::cerr << "No se puede agregar la linea:" << lin << std::endl;
                continue;
            }
            parametros++;
        }
        is.close();
    }catch(std::exception& ex){
        std::cerr << "Error al intentar abrir el archivo:" << ruta << std::endl;
        std::cerr << "Error:" << ex.what() << std::endl;
        return -3;
    }
    return parametros;
}
