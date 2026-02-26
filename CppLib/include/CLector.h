#ifndef CLECTOR_H
#define CLECTOR_H

#include <iostream>
#include <fstream>
#include "CConexion.h"
#include "CRegistroLec.h"
#include "CUtiles.h"

namespace SBI{

    class CLector
    {
        public:
            /** Default constructor */
            CLector();
            /** Constructor sobrecargado */
            CLector(std::string r_arch);
            /** Default destructor */
            virtual ~CLector();
            /** Access totallineas
             * \return The current value of totallineas
             */
            unsigned int Gettotallineas() { return totallineas; }
            /** Set totallineas
             * \param val New value to set
             */
            void Settotallineas(unsigned int val) { totallineas = val; }
            /** Access lineaactual
             * \return The current value of lineaactual
             */
            unsigned int Getlineaactual() { return lineaactual; }
            /** Set lineaactual
             * \param val New value to set
             */
            void Setlineaactual(unsigned int val) { lineaactual = val; }
            /** Access lineaserror
             * \return The current value of lineaserror
             */
            unsigned int Getlineaserror() { return lineaserror; }
            /** Set lineaserror
             * \param val New value to set
             */
            void Setlineaserror(unsigned int val) { lineaserror = val; }
            /** Access rutaarch
             * \return The current value of rutaarch
             */
            std::string Getrutaarch() { return rutaarch; }
            /** Set rutaarch
             * \param val New value to set
             */
            void Setrutaarch(std::string val) { rutaarch = val; }
            /** Access rutaerr
             * \return The current value of rutaerr
             */
            std::string Getrutaerr() { return rutaerr; }
            /** Set rutaerr
             * \param val New value to set
             */
            void Setrutaerr(std::string val) { rutaerr = val; }
            /** Access rutaprc
             * \return The current value of rutaprc
             */
            std::string Getrutaprc() { return rutaprc; }
            /** Set rutaprc
             * \param val New value to set
             */
            void Setrutaprc(std::string val) { rutaprc = val; }
            /** Access conn
             * \return The current value of conn
             */
            CConexion* Getconn() { return conn; }
            /** Set conn
             * \param val New value to set
             */
            void Setconn(CConexion* val) { conn = val; }
            /** Set procesar
             * \param val New value to set
             */
            int procesar();
        protected:
            void resumen();
        private:
            unsigned int totallineas; //!< Member variable "totallineas"
            unsigned int lineaactual; //!< Member variable "lineaactual"
            unsigned int lineaserror; //!< Member variable "lineaserror"
            std::string rutaarch; //!< Member variable "rutaarch"
            std::string rutaerr; //!< Member variable "rutaerr"
            std::string rutaprc; //!< Member variable "rutaprc"
            CConexion* conn; //!< Member variable "conn"
            std::vector<CRegistroLec*> regs;
    };

}

#endif // CLECTOR_H
