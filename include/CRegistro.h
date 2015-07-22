#ifndef CREGISTRO_H
#define CREGISTRO_H

#include <iostream>
#include <string.h>
#include "CSensor.h"
#include <ctime>

using namespace std;

namespace SBI{
    class CRegistro
    {
        public:
            /** Default constructor */
            CRegistro();
            /** Default destructor */
            virtual ~CRegistro();
            /** Access valor
             * \return The current value of valor
             */
            int Getvalor() { return valor; }
            /** Set valor
             * \param val New value to set
             */
            void Setvalor(int val) { valor = val; }
            /** Access nivel
             * \return The current value of nivel
             */
            float Getrepresentacion() { return representacion; }
            /** Set representacion
             * \param val New value to set
             */
            void Setrepresentacion(float val) { representacion = val; }
            /** Access sensor
             * \return The current value of sensor
             */
            CSensor* Getsensor() { return sensor; }
            /** Set sensor
             * \param val New value to set
             */
            void Setsensor(CSensor* val) { sensor = val; }
            /** Access proceso
             * \return The current value of proceso
             */
            char* Getproceso() { return proceso; }
            /** Set proceso
             * \param val New value to set
             */
            void Setproceso(const char* val) {
                //proceso = val;
                if(proceso != NULL)
                    delete[] proceso;
                proceso = new char[strlen(val)];
                strcpy(proceso,val);
            }

            /**
                Funciones propias para el proceso
            */
            int LoadData(int val);
            char *GetDate();
        protected:
        private:
            int valor; //!< Member variable "valor"
            float representacion; //!< Member variable "representacion"
            char* proceso; //!< Member variable "proceso"
            CSensor* sensor;
            time_t fecreg;
    };
}

#endif // CREGISTRO_H
