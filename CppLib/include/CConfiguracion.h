#ifndef CCONFIGURACION_H
#define CCONFIGURACION_H

template<typename T>
class CConfiguracion{
    public:
        CConfiguracion();

        T get<T>(std::string llave);

};

#endif