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

int CConexion::InsertRegs(vector<CRegistroLec*> &lineas){
    PGresult* pgresultado;
    PGresult* stmt;
    char valorParam[7][30];
    const char* valorParamt[7];
    int largoParam[7];
    int formatoParam[7] = {0,0,0,0,0,0,0};
    int procesados = 0;
    int errores = 0;
    vector<CRegistroLec*>::iterator r_act = lineas.begin(); // registro actual
    // Valido
    if (PQstatus(pgconn) != CONNECTION_OK)
        return -1;
    // Alisto la consulta
    stmt = PQprepare(pgconn, "insert_data",
                             "INSERT INTO import_data(imp_reg, imp_value, imp_factor, imp_repr, imp_elem, imp_proc, imp_nivel) VALUES(to_timestamp($1,'YYYY-MM-DD HH24-MI:SS'), $2, $3, $4, $5, $6, $7)", 7, NULL);
    if(PQresultStatus(stmt) == PGRES_COMMAND_OK){
        // Continuo con la ejecucion
        while(r_act != lineas.end()){ // Recorro todo el vector
            // Alisto los parametros
            sprintf(valorParam[0],"%s",(*r_act)->Getfecha().c_str());
            //valorParam[0] = (*r_act)->Getfecha().c_str();
            sprintf(valorParam[1],"%d",(*r_act)->Getvalor());
            //valorParam[1] = to_string((*r_act)->Getvalor()).c_str();
            sprintf(valorParam[2],"%f",(*r_act)->Getescala());
            //valorParam[2] = to_string((*r_act)->Getescala().c_str();
            sprintf(valorParam[3],"%f",(*r_act)->Getrepresentacion());
            //valorParam[3] = to_string((*r_act)->Getrepresentacion().c_str();
            sprintf(valorParam[4],"%d",(*r_act)->Getnmuestra());
            //valorParam[4] = to_string((*r_act)->Getnmuestra().c_str();
            sprintf(valorParam[5],"Prueba_123");
            //valorParam[5] = "Prueba_123";
            sprintf(valorParam[6],"%d",(*r_act)->Getnivel());
            //valorParam[6] = to_string((*r_act)->Getnivel().c_str();
            valorParamt[0] = valorParam[0];
            valorParamt[1] = valorParam[1];
            valorParamt[2] = valorParam[2];
            valorParamt[3] = valorParam[3];
            valorParamt[4] = valorParam[4];
            valorParamt[5] = valorParam[5];
            valorParamt[6] = valorParam[6];
            largoParam[0] = strlen(valorParam[0]);
            largoParam[1] = strlen(valorParam[1]);
            largoParam[2] = strlen(valorParam[2]);
            largoParam[3] = strlen(valorParam[3]);
            largoParam[4] = strlen(valorParam[4]);
            largoParam[5] = strlen(valorParam[5]);
            largoParam[6] = strlen(valorParam[6]);

            // Ahora ejecuto
            pgresultado = PQexecPrepared(pgconn,"insert_data",7,valorParamt, largoParam, formatoParam, 0);

            if (PQresultStatus(pgresultado) != PGRES_COMMAND_OK){
                cout<<"Error en la insercion de datos["<<PQresultErrorMessage(pgresultado)<<"]"<<endl;
                cout<<"con el registro ["<<(*r_act)->Getnmuestra()<<"]"<<endl;
                errores++;
            }
            else{
                procesados++;
            }
            PQclear(pgresultado);
            r_act++; // voy con el siguiente elemento
        }
    }
    else{
        cout<<"No se puede crear ls instruccion de registro:"<<PQresultErrorMessage(stmt)<<endl;
    }
    PQclear(stmt);
    if(PQresultStatus(PQexec(pgconn, "DEALLOCATE insert_data")) != PGRES_COMMAND_OK){
        cout<<"No se pude desasignar la consulta de registro!!!"<<endl;
    }
    cout<<"Registros a cargar:"<<lineas.size()<<endl;
    cout<<"Lineas registradas:"<<procesados<<endl;
    cout<<"Lineas erradas:"<<errores<<endl;
    return procesados;
}


// Final de la implementacion
