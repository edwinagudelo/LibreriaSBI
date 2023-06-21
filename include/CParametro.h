#ifndef CPARAMETRO_H
#define CPARAMETRO_H

#include <string>

class CParametro
{
    public:

        typedef enum {
                NO_TIPO,
                ENTERO,
                CARACTER,
                FLOTANTE,
                FECHA
            }TIPO_PARAM;

        CParametro(std::string& valor, TIPO_PARAM tipo);

        void setParam(std::string& valor, TIPO_PARAM tipo);

    private:

        std::string value;
        TIPO_PARAM param_type;

};

#endif //CPARAMETRO_H

