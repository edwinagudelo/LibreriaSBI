#ifndef CPLANO_H
#define CPLANO_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sys/stat.h>
#ifdef __GNUC__
#include <unistd.h>
#endif


#include "CUtiles.h"
#include "CConfigura.h"

class CPlano : public CConfigura
{
    public:
        /** Default constructor */
        CPlano();
        /** Default destructor */
        virtual ~CPlano();
        virtual int cargar();
        void setSeparador(char val);
        char getSeparador();
        void setRuta(std::string val);
        std::string getRuta();
        void setComentador(char val);
        char getComentador();

    protected:
        std::string ruta;
        char separador;
        char comentador;
};

#endif // CPLANO_H
