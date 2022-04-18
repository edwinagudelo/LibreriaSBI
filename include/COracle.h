#ifndef CORACLE_H
#define CORACLE_H

#include <string>
#include <iostream>
#include <string.h>
#include "oci.h"

using namespace std;

class COracle
{
    public:
        /** Default constructor */
        COracle();
        /** Default destructor */
        virtual ~COracle();

        /** Funcion para conectarse a Oracle*/
        int Conectarse();
        void Finalizar();
    protected:
    private:
        // Datos para la conexion
        string usuario;
        string contrasena;
        string cadena;
        // Conexion a BSCSREP
        OCIEnv*       env;
        OCIError* err;
        OCIServer* srv;
        OCISvcCtx* svc;
        OCISession*   ses;

        void checkerr(OCIError* err, sword status);
};

#endif // CORACLE_H
