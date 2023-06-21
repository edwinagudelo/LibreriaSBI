#include "CParametro.h"

CParametro::CParametro(std::string& valor, TIPO_PARAM tipo){
    value = valor;
    param_type = tipo;
}

void CParametro::setParam(std::string& valor, TIPO_PARAM tipo){
    value = valor;
    param_type = tipo;
}