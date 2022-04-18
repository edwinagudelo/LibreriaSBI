#ifndef CSENSOR_H
#define CSENSOR_H

#include <string.h>
#include <iostream>

using namespace std;

namespace SBI{
    class CSensor
    {
        public:
            /** Default constructor */
            CSensor();
            /** Default destructor */
            virtual ~CSensor();
            /** Access id
             * \return The current value of id
             */
            int Getid() { return id; }
            /** Set id
             * \param val New value to set
             */
            void Setid(int val) { id = val; }
            /** Access *nombre
             * \return The current value of *nombre
             */
            char* Getnombre() { return nombre; }
            /** Set *nombre
             * \param val New value to set
             */
            void Setnombre(const char* val) {
                if(nombre != NULL)
                    delete[] nombre;
                nombre = new char[strlen(val)];
                strcpy(nombre, val);
            }
            /** Access escala
             * \return The current value of escala
             */
            float Getescala() { return escala; }
            /** Set escala
             * \param val New value to set
             */
            void Setescala(float val) { escala = val; }
            /** Access nivel
             * \return The current value of nivel
             */
            int Getnivel() { return nivel; }
            /** Set nivel
             * \param val New value to set
             */
            void Setnivel(int val) { nivel = val; }
            /** Access frecuencia
             * \return The current value of frecuencia
             */
            int Getfrecuencia() { return frecuencia; }
            /** Set frecuencia
             * \param val New value to set
             */
            void Setfrecuencia(int val) { frecuencia = val; }
        protected:
        private:
            int id; //!< Member variable "id"
            char *nombre; //!< Member variable "*nombre"
            float escala; //!< Member variable "escala"
            int nivel; //!< Member variable "nivel"
            int frecuencia; //!< Member variable "frecuencia"
    };
}

#endif // CSENSOR_H
