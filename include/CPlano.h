#ifndef CPLANO_H
#define CPLANO_H

#include <CConfigura.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

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
        void setRuta(string val);
        string getRuta();
        void setComentador(char val);
        char getComentador();

    protected:
        string ruta;
        char separador;
        char comentador;
    private:
        void split(string cadena, char sep, string *retorno);
};

#endif // CPLANO_H
