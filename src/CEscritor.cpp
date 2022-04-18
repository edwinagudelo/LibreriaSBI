#include "CEscritor.h"

using namespace SBI;

CEscritor::CEscritor()
{
    //ctor
    id = 0;
    reg = NULL;
    nombre = NULL;
    limite = 0;
    contador = 0;
}

CEscritor::~CEscritor()
{
    //dtor
    cerrar();
}

void CEscritor::escribir(){
    //stringstream ss;

    // Valido el registro
    if(reg == NULL)
        return;
    if( contador == 0 )
        abrir();
    //if( !salida.is_open() ){
        //abrir();
    //}
    if (depuracion == 1)
        cout<<(reg->Getsensor())->Getid()<<";"<<(reg->Getsensor())->Getescala()<<";"<<(reg->Getsensor())->Getnivel()<<";"<<reg->Getvalor()<<";"<<reg->Getrepresentacion()<<";"<<reg->GetDate()<<";"<<contador<<endl;
    //salida<<ss.c_str();
    //cout<<ss.c_str();
    if(salida.good())
        salida<<(reg->Getsensor())->Getid()<<";"<<(reg->Getsensor())->Getescala()<<";"<<(reg->Getsensor())->Getnivel()<<";"<<reg->Getvalor()<<";"<<reg->Getrepresentacion()<<";"<<reg->GetDate()<<";"<<contador<<endl;
    else
        cout<<"No se puede escribir"<<endl;
    //salida.flush();
    contador++;
    if(contador == limite){
        cerrar();
        abrir();
    }
    return;
}


int CEscritor::abrir(){
    int retorno = 0;
    char *rutacompleta;

    if(nombre == NULL){
        nombre = new char[25];
    }
    sprintf(nombre,"imp_%s.dat",CUtiles::traerFechaActual());
    rutacompleta = new char[strlen(rutatmp.c_str()) + 25];
    sprintf(rutacompleta,"%s/%s",rutatmp.c_str(),nombre);
    //sprintf(rutacompleta,"%s\\%s",rutatmp.c_str(),nombre);
    if(salida.is_open())
        salida.close();
    cout<<"Escribiendo temporalmente en:"<<rutacompleta<<endl;
    salida.open(rutacompleta, ios::out);
    if (!salida.good()){
        cout<<"Paila el archivo!!!"<<endl;
    }
    contador = 0;
    //delete rutacompleta;
    return retorno;
}

void CEscritor::cerrar(){
    char *rutainicial;
    char *rutafinal;
    string sep = "/";
    #ifdef _WIN32
        sep = "\\";
    #endif

    // Cierro el archivo
    if(salida.is_open()){
        salida.close();

        // Paso el archivo a la ruta final
        rutainicial = new char[strlen(rutatmp.c_str()) + 25];
        rutafinal = new char[strlen(rutasal.c_str()) + 25];
        sprintf(rutainicial,"%s%s%s",rutatmp.c_str(), sep.c_str(), nombre);
        sprintf(rutafinal,"%s%s%s",rutasal.c_str(),sep.c_str(), nombre);

        // Procedo a mover
        cout<<"Moviendo"<<endl<<"Desde:"<<rutainicial<<endl<<"Hacia:"<<rutafinal<<endl;
        rename(rutainicial, rutafinal);
    }

    return;

}
