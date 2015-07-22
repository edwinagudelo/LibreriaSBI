#ifndef CUTILES_H
#define CUTILES_H

#include <ctime>
#include <string>

using namespace std;

namespace SBI{
    class CUtiles
    {
        public:
            /** Default constructor */
            CUtiles();
            /** Default destructor */
            virtual ~CUtiles();
            /** Funcion para calcular fecha */
            static char* traerFechaActual();
        protected:
        private:
    };
}

#endif // CUTILES_H
