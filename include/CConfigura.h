#ifndef CCONFIGURA_H
#define CCONFIGURA_H

// Includes
#include <iostream>
#include <map>
#include <string>

namespace SBI{
    namespace  Utils{
        class CConfigura
        {
            public:
                /** Default constructor */
                CConfigura();
                /** Default destructor */
                virtual ~CConfigura();

                /** Return a parameter */
                std::string getParam(const std::string& llave);
                /** Set a parameter */
                bool setParam(const std::string& llave, const std::string& valor);
                /** Get the modification parameter */
                bool getModif();
                /** Set modification parameter */
                void setModif(bool modif);
                /** Show all parameters */
                void mostrar();

            private:
                std::map<std::string, std::string> configuraciones;
                bool modificable;
        };

    }

}

#endif // CCONFIGURA_H
