#ifndef CCONFIGURA_H
#define CCONFIGURA_H

// Includes
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#define VER_CFG "1000"

using namespace std;

class CConfigura
{
    public:
        /** Default constructor */
        CConfigura();
        /** Default destructor */
        virtual ~CConfigura();

        /**
            Enumeracion que me indica el tipo de parametro
        */
        typedef enum {
            NO_TIPO,
            ENTERO,
            CARACTER,
            FLOTANTE,
            FECHA
        }TIPO_CONF;

        //TIPO_CONF TC_PARAM;

        /** Funciones a implementar */
        /** Funciones a implementar */
        virtual string getParam(string llave);
        /** Funciones a implementar */
        virtual bool setParam(string llave, string valor);
        /** Funciones a implementar */
        virtual bool setParam(string llave, string valor, int tipo);
        /** Funciones a implementar */
        virtual int getModif();
        /** Funciones a implementar */
        virtual void setModif(int modif);
        /** Funciones a implementar */
        virtual int cargar() = 0;
        /** Funciones a implementar */
        virtual void mostrar();
    protected:
    private:
        map<string, map<string, int> > configuraciones;
        int modificable;
};

#endif // CCONFIGURA_H
