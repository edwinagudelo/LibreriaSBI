#ifndef CREGISTROLEC_H
#define CREGISTROLEC_H

#include <string>

using namespace std;

namespace SBI{
    class CRegistroLec
    {
        public:
            /** Default constructor */
            CRegistroLec();
            /** Default destructor */
            virtual ~CRegistroLec();
            /** Access sensor
             * \return The current value of sensor
             */
            int Getsensor() { return sensor; }
            /** Set sensor
             * \param val New value to set
             */
            void Setsensor(int val) { sensor = val; }
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
            /** Access valor
             * \return The current value of valor
             */
            int Getvalor() { return valor; }
            /** Set valor
             * \param val New value to set
             */
            void Setvalor(int val) { valor = val; }
            /** Access representacion
             * \return The current value of representacion
             */
            float Getrepresentacion() { return representacion; }
            /** Set representacion
             * \param val New value to set
             */
            void Setrepresentacion(float val) { representacion = val; }
            /** Access fecha
             * \return The current value of fecha
             */
            string Getfecha() { return fecha; }
            /** Set fecha
             * \param val New value to set
             */
            void Setfecha(string val) { fecha = val; }
            /** Access nmuestra
             * \return The current value of nmuestra
             */
            unsigned int Getnmuestra() { return nmuestra; }
            /** Set nmuestra
             * \param val New value to set
             */
            void Setnmuestra(unsigned int val) { nmuestra = val; }
        protected:
        private:
            int sensor; //!< Member variable "sensor"
            float escala; //!< Member variable "escala"
            int nivel; //!< Member variable "nivel"
            int valor; //!< Member variable "valor"
            float representacion; //!< Member variable "representacion"
            string fecha; //!< Member variable "fecha"
            unsigned int nmuestra; //!< Member variable "nmuestra"
    };

}

#endif // CREGISTROLEC_H
