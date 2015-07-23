#ifndef CCONEXION_H
#define CCONEXION_H

/********************************************************

CConexion.h

Clase de conexion a postgresql

S.B.I.
Ing. Edwin A. Agudelo G.
2015.

********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <postgresql/libpq-fe.h>
#include "CSensor.h"
#include "CRegistro.h"


namespace SBI{
    class CConexion
    {
        public:
            /** Default constructor */
            CConexion();
            /** Default destructor */
            virtual ~CConexion();
            /** Access pgconn
             * \return The current value of pgconn
             */
            PGconn* Getpgconn() { return pgconn; }
            /** Set pgconn
             * \param val New value to set
             */
            void Setpgconn(PGconn* val) { pgconn = val; }
            /** Access hostaddr
             * \return The current value of hostaddr
             */
            char* Gethostaddr() { return hostaddr; }
            /** Set hostaddr
             * \param val New value to set
             */
            void Sethostaddr(const char* val) {
                //hostaddr = val;
                if(hostaddr != NULL)
                    free(hostaddr);
                hostaddr = (char*)malloc(strlen(val)*sizeof(char));
                strcpy(hostaddr,val);
            }
            /** Access port
             * \return The current value of port
             */
            unsigned int Getport() { return port; }
            /** Set port
             * \param val New value to set
             */
            void Setport(unsigned int val) { port = val; }
            /** Access dbname
             * \return The current value of dbname
             */
            char* Getdbname() { return dbname; }
            /** Set dbname
             * \param val New value to set
             */
            void Setdbname(const char* val) {
                //dbname = val;
                if(dbname != NULL)
                    free(dbname);
                dbname = (char*)malloc(strlen(val)*sizeof(char));
                strcpy(dbname,val);
            }
            /** Access username
             * \return The current value of username
             */
            char* Getusername() { return username; }
            /** Set username
             * \param val New value to set
             */
            void Setusername(const char* val) {
                //username = val;
                if(username != NULL)
                    free(username);
                username = (char*)malloc(strlen(val)*sizeof(char));
                strcpy(username,val);
            }
            /** Access password
             * \return The current value of password
             */
            char* Getpassword() { return password; }
            /** Set password
             * \param val New value to set
             */
            void Setpassword(const char* val) {
                //password = val;
                if(password != NULL)
                    free(password);
                password = (char*)malloc(strlen(val)*sizeof(char));
                strcpy(password,val);
            }
            /** Access applicationname
             * \return The current value of applicationname
             */
            char* Getapplicationname() { return applicationname; }
            /** Set applicationname
             * \param val New value to set
             */
            void Setapplicationname(const char* val) {
                if(applicationname != NULL)
                    free(applicationname);
                applicationname = (char*)malloc(strlen(val)*sizeof(char));
                strcpy(applicationname,val);
            }

            /**
            *  Funcion devolver los datos cargados
            */
            CRegistro* Getregis() { return regis; }
            /**
            *  Funcion asignar valores cargados
            */
            void Setregis(CRegistro* val){
                regis = val;
            }

            /** OpenConn
            *  Funcion para abrir la conexion a Postgresql
            */
            int OpenConn();

            /** Getversion
            *  Funcion para conocer la version de postgresql
            */
            char* Getversion();

            /**Getsensores
            *  Funcion para traer la configuracion de sensores almacenados en la BD
            */
            vector<CSensor*> Getsensores();

            /** Getiversion
            *  Funcion para conocer la version de postgresql de tipo integer
            */
            int Getiversion();

        protected:
        private:
            PGconn* pgconn; //!< Member variable "pgconn"
            char* hostaddr; //!< Member variable "hostaddr"
            unsigned int port; //!< Member variable "port"
            char* dbname; //!< Member variable "dbname"
            char* username; //!< Member variable "username"
            char* password; //!< Member variable "password"
            char* applicationname; //!< Member variable "applicationname"
            // Objeto para las inserciones
            CRegistro *regis;
    };

}

#endif // CCONEXION_H
