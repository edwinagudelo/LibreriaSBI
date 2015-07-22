#include "CRegistro.h"

using namespace SBI;

CRegistro::CRegistro()
{
    //ctor
    valor = 0;
    representacion = 0;
    sensor = NULL;
    proceso = NULL;
    time(&fecreg);
}

CRegistro::~CRegistro()
{
    //dtor
    if(proceso != NULL)
        delete []proceso;
    /*if(sensor != NULL)
        delete sensor;*/
}

int CRegistro::LoadData(int val){
    if (sensor == NULL)
        return -1;
    time(&fecreg);
    valor = val;
    representacion = ((float)(valor + sensor->Getnivel())*(sensor->Getescala()));
    return 1;
}

char* CRegistro::GetDate(){
    char* retorno = new char[80];
    struct tm *ltm = localtime(&fecreg);
    //strftime(retorno,80,"%F %T",ltm);
    strftime(retorno,80,"%Y-%m-%d %H:%M:%S",ltm);
    return retorno;
}
