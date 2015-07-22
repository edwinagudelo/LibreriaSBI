#include "CSensor.h"

using namespace SBI;

CSensor::CSensor()
{
    //ctor
    id = 0;
    nombre = NULL;
    escala = 1;
    nivel = 0;
    frecuencia = 1;
}

CSensor::~CSensor()
{
    //dtor
    //if(nombre != NULL)
        //delete nombre;
}
