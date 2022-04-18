#ifndef CESCRITOR_H
#define CESCRITOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "CRegistro.h"
#include "CUtiles.h"

using namespace std;

namespace SBI{
    class CEscritor
    {
        public:
            /** Default constructor */
            CEscritor();
            /** Default destructor */
            virtual ~CEscritor();
            /** Access id
             * \return The current value of id
             */
            int Getid() { return id; }
            /** Set id
             * \param val New value to set
             */
            void Setid(int val) { id = val; }
            /** Access nombre
             * \return The current value of nombre
             */
            char* Getnombre() { return nombre; }
            /** Set nombre
             * \param val New value to set
             */
            void Setnombre(char* val) { nombre = val; }
            /** Access limite
             * \return The current value of limite
             */
            double Getlimite() { return limite; }
            /** Set limite
             * \param val New value to set
             */
            void Setlimite(double val) { limite = val; }
            /** Access reg
             * \return The current value of reg
             */
            CRegistro* Getreg() { return reg; }
            /** Set reg
             * \param val New value to set
             */
            void Setreg(CRegistro* val) { reg = val; escribir(); }
            /** Access rutasal
             * \return The current value of rutasal
             */
            string Getrutasal() { return rutasal; }
            /** Set rutasal
             * \param val New value to set
             */
            void Setrutasal(string val) { rutasal = val; }
            /** Access rutatmp
             * \return The current value of rutatmp
             */
            string Getrutatmp() { return rutatmp; }
            /** Set rutasal
             * \param val New value to set
             */
            void Setrutatmp(string val) { rutatmp = val; }
            /** Access id
             * \return The current value of id
             */
            int Getdepuracion() { return depuracion; }
            /** Set id
             * \param val New value to set
             */
            void Setdepuracion(int val) { depuracion = val; }
            /** Access nombre
             * \return The current value of nombre
             */

        protected:
        private:
            int id; //!< Member variable "id"
            char* nombre; //!< Member variable "nombre"
            double limite; //!< Member variable "limite"
            CRegistro* reg; //!< Member variable "reg"
            double contador; //!< Member variable "contador"
            ofstream salida; //!< Member variable "salida"
            string rutasal; //!< Member variable "rutasal"
            string rutatmp; //!< Member variable "rutatmp"
            int depuracion; //!< valor de depuracion

            /**
            Funcion que se encarga de registrar los datos
            */
            void escribir();
            int abrir();
            void cerrar();
    };
}

#endif // CESCRITOR_H
