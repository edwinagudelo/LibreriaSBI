#ifndef CCONFIGURA_H
#define CCONFIGURA_H

// Includes
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define VER_CFG "1000"

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

        /** Funciones a implementar */
        virtual std::string getParam(std::string llave);
        /** Funciones a implementar */
        virtual bool setParam(std::string llave, std::string valor);
        /** Funciones a implementar */
        virtual bool setParam(std::string llave, std::string valor, int tipo);
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
        std::map<std::string, std::map<std::string, int> > configuraciones;
        int modificable;
};

#endif // CCONFIGURA_H
