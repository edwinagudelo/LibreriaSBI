#include "COracle.h"

COracle::COracle()
{
    //ctor
}

COracle::~COracle()
{
    //dtor
}

int COracle::Conectarse(){
    int retorno = 0;
    sword r;
    env = 0;
    err = 0;
    srv = 0;
    svc = 0;
    ses = 0;
    r=OCIEnvCreate( &env, OCI_DEFAULT, 0, 0, 0, 0, 0, 0);

    if (r != OCI_SUCCESS)  {
        cout<<"OCIEnvCreate Fallo!\n"<<endl;
        Finalizar();
        return -1;
    }
    OCIHandleAlloc(env, (dvoid**)&err, OCI_HTYPE_ERROR,   0, 0);
    OCIHandleAlloc(env, (dvoid**)&srv, OCI_HTYPE_SERVER,  0, 0);
    OCIHandleAlloc(env, (dvoid**)&svc, OCI_HTYPE_SVCCTX,  0, 0);

    //r=OCIServerAttach(srv, err,  dbname, strlen((const char*)dbname), (ub4) OCI_DEFAULT);
    r=OCIServerAttach(srv, err, (const OraText*) cadena.c_str(), strlen((const char*)cadena.c_str()), (ub4) OCI_DEFAULT);

    if (r != OCI_SUCCESS) {
        checkerr(err, r);
        Finalizar();
        return -2;
    }

    OCIAttrSet(svc, OCI_HTYPE_SVCCTX, srv, 0, OCI_ATTR_SERVER,  err);
    OCIHandleAlloc(env, (dvoid**)&ses, OCI_HTYPE_SESSION, 0, 0);
    OCIAttrSet(ses, OCI_HTYPE_SESSION, usuario.c_str(), strlen((const char*)usuario.c_str()), OCI_ATTR_USERNAME, err);
    OCIAttrSet(ses, OCI_HTYPE_SESSION, contrasena.c_str(), strlen((const char*)contrasena.c_str()), OCI_ATTR_PASSWORD, err);

    r=OCISessionBegin (svc, err, ses, OCI_CRED_RDBMS, OCI_DEFAULT);
    checkerr(err, r);
    r=OCIAttrSet(svc, OCI_HTYPE_SVCCTX, ses, 0, OCI_ATTR_SESSION, err);

    cout<<"Conexion Oracle OK.\n"<<endl;
    return retorno;
}

void COracle::Finalizar(){
    if (err) OCIHandleFree(err, OCI_HTYPE_ERROR );
    if (srv) OCIHandleFree(srv, OCI_HTYPE_SERVER);
    if (svc) OCIHandleFree(svc, OCI_HTYPE_SVCCTX);
    if (env) OCIHandleFree(env, OCI_HTYPE_ENV   );
    OCITerminate(OCI_DEFAULT);
    return 0;
}

void COracle::checkerr(OCIError* err, sword status) {
    text errbuf[512];
    //ub4 buflen;
    ub4 errcode;

    switch (status) {
        case OCI_SUCCESS:
            break;
        case OCI_SUCCESS_WITH_INFO:
            cout<<"Error - OCI_SUCCESS_WITH_INFO\n"<<endl;
            break;
        case OCI_NEED_DATA:
            cout<<"Error - OCI_NEED_DATA\n"<<endl;
            break;
        case OCI_NO_DATA:
            cout<<"Error - OCI_NO_DATA\n"<<endl;
            break;
        case OCI_ERROR:
            OCIErrorGet ( err, (ub4) 1, (text *) NULL, (sb4*)&errcode,
                    errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);
            cout<<"Error - %s\n", errbuf<<endl;
            break;
        case OCI_INVALID_HANDLE:
            cout<<"Error - OCI_INVALID_HANDLE\n"<<endl;
            break;
        case OCI_STILL_EXECUTING:
            cout<<"Error - OCI_STILL_EXECUTE\n"<<endl;
            break;
        case OCI_CONTINUE:
            cout<<"Error - OCI_CONTINUE\n"<<endl;
            break;
        default:
            cout<<"Error Oracle Unknown";
            break;
    }
}
