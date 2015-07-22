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
