#include "CConexion.h"

using namespace SBI;

CConexion::CConexion()
{
    //ctor
    // Inicializo las variables
    pgconn = NULL;
    hostaddr = NULL;
    port = 0;
    dbname = NULL;
    username = NULL;
    password = NULL;
    applicationname= NULL;
}

CConexion::~CConexion()
{
    //dtor
    if(pgconn != NULL){
        PQfinish(pgconn);
    }
}


int CConexion::OpenConn(){
    int retorno = 0;
    size_t largo = 0;
    char* cadenacon = NULL;

    // Validaciones
    if ( hostaddr == NULL )
        retorno = -1;
    if ( dbname == NULL )
        retorno = -2;
    if ( username == NULL )
        retorno = -3;
    if ( password == NULL )
        retorno = -4;
    if ( applicationname == NULL )
        retorno = -5;
    if ( port == 0 || port > 65535 )
        retorno = -6;

    if(retorno == 0){
        // longitud de la cadena, los 63 son los caracteres necesarios para armar la conexion
        largo = strlen(hostaddr) + strlen(dbname) + strlen(username) + strlen(password) + strlen(applicationname) + 74;
        // Armo la cadena
        cadenacon = (char*)malloc(largo*sizeof(char));
        if (cadenacon != NULL){
            sprintf(cadenacon,"hostaddr=%s port=%u dbname=%s user=%s password=%s application_name=%s",hostaddr, port, dbname, username, password, applicationname);
            //sprintf(cadenacon,"hostaddr=%s port=%u dbname=%s user=%s password=%s ",hostaddr, port, dbname, username, password);
            //sprintf(cadenacon,"hostaddr=%s port=%u dbname=%s user=%s password=%s fallback_application_name=%s",hostaddr, port, dbname, username, password,applicationname);
            pgconn = PQconnectdb(cadenacon);
            if(PQstatus(pgconn) != CONNECTION_OK){
                fprintf(stderr,"Error en la conexion:%s\n",PQerrorMessage(pgconn));
                retorno = -8;
            }
        }
        else{
            retorno = -7;
        }
    }
    return retorno;
}

char* CConexion::Getversion(){
    char* retorno = NULL;
    size_t largo = 0;
    PGresult* result;

    //Consulto la version
    result = PQexec(pgconn,"SELECT version()");
    if(PQresultStatus(result) == PGRES_TUPLES_OK){
        largo = strlen(PQgetvalue(result,0,0));
        retorno = (char*)malloc(largo*sizeof(char));
        if(retorno != NULL){
            strcpy(retorno,PQgetvalue(result,0,0));
        }
    }
    PQclear(result);
    /*switch(PQresultStatus(result)){
	    case PGRES_TUPLES_OK:
	        printf("Resultado:\n");
	        for(i = 0 ; i < PQntuples(result) ; i++){
                for(j = 0 ; j < PQnfields(result) ; j++){
                    if(PQgetisnull(result,i,j)){
                        printf("NULL\t");
                        continue;
                    }
                    printf(" %s\t",PQgetvalue(result,i,j));
                }
                printf("\n");
	        }
	        PQclear(result);
            break;
	    case PGRES_COMMAND_OK:
	        printf("Comando ejecutado correctamente\n");
	        PQclear(result);
	        break;
	    case PGRES_EMPTY_QUERY:
	        printf("Consulta vacia\n");
	        PQclear(result);
	        break;
	    case PGRES_BAD_RESPONSE:
	        printf("Error en respuesta:%s\n",PQresultErrorMessage(result));
	        PQclear(result);
	        break;
	    case PGRES_FATAL_ERROR:
	        printf("Error Fatal:%s\n",PQresultErrorMessage(result));
	        PQclear(result);
	        break;
	    default:
	        printf("Falla no definida:%d - %s\n",PQresultStatus(result), PQresStatus(PQresultStatus(result)));
	        break;
	}*/
	return retorno;
}

vector<CSensor*> CConexion::Getsensores(){
    vector<CSensor*> retorno;
    PGresult* result;

    //Consulto la version
    result = PQexec(pgconn,"Select sen_id, sen_nombre, sen_escala, sen_nivel, sen_frecuencia from sensores");
    if(PQresultStatus(result) == PGRES_TUPLES_OK){
        int i,j;
        for(i = 0 ; i < PQntuples(result) ; i++){
            CSensor* sen = new CSensor();
            for(j = 0; j < PQnfields(result) ; j++){
                if(PQgetisnull(result,i,j))
                    continue;
                switch(j){
                case 0:
                    sen->Setid(atoi(PQgetvalue(result,i,j)));
                    break;
                case 1:
                    sen->Setnombre(PQgetvalue(result,i,j));
                    break;
                case 2:
                    sen->Setescala(atof(PQgetvalue(result,i,j)));
                    break;
                case 3:
                    sen->Setnivel(atoi(PQgetvalue(result,i,j)));
                    break;
                case 4:
                    sen->Setfrecuencia(atoi(PQgetvalue(result,i,j)));
                    break;
                default:
                    break;
                }
            }
            retorno.push_back(sen);
        }
    }
    PQclear(result);
    return retorno;
}

int CConexion::Getiversion(){
    if (PQstatus(pgconn) == CONNECTION_OK)
        return PQserverVersion(pgconn);
    else
        return -1;
}
