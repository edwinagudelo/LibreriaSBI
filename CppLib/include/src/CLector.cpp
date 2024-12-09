#include "CLector.h"

using namespace SBI;

CLector::CLector()
{
    //ctor
    totallineas = 0;
    lineaactual = 0;
    lineaserror = 0;
    rutaarch = "";
    rutaerr = "";
    rutaprc = "";
    conn = NULL;
}

CLector::CLector(std::string r_arch){
    rutaarch = r_arch;
    totallineas = 0;
    lineaactual = 0;
    lineaserror = 0;
    rutaerr = "";
    rutaprc = "";
    conn = NULL;
}

CLector::~CLector()
{
    //dtor
}

int CLector::procesar(){
    std::ifstream entrada;
    std::ofstream salidaerr;
    std::string lin;
    std::string nomArch;
    std::vector<std::string> campos;
    int report_err = 0;

    // Inicio a validar
    if(rutaarch.size() < 2){
        return -1;
    }
    if(rutaprc.size() < 2){
        return -2;
    }
    if(rutaerr.size() > 2){
        report_err = 1;
    }
    if(conn == NULL){
        return -5;
    }

    nomArch = CUtiles::traerNombreArchivo(rutaarch);

    entrada.open(rutaarch.c_str());
    if(!entrada.good()){
        return -3;
    }

    if(report_err != 0){
        std::string archerr = rutaerr + "/" + nomArch;
        salidaerr.open( archerr.c_str() );
        if(!salidaerr.good()){
            return -4;
        }
    }

    // recorro el archivo
    while(!entrada.eof()){
        lineaactual++;
        std::getline(entrada,lin);
        if(lin.size() < 2)
            continue;
        CUtiles::separarCadena(lin,';',campos);
        if(campos.size() != 7){
            if(report_err != 0)
                salidaerr<<lin;
            lineaserror++;
            continue;
        }
        CRegistroLec* regis = new CRegistroLec();
        regis->Setsensor(atoi(campos[0].c_str()));
        regis->Setescala(atof(campos[1].c_str()));
        regis->Setnivel(atoi(campos[2].c_str()));
        regis->Setvalor(atoi(campos[3].c_str()));
        regis->Setrepresentacion(atof(campos[4].c_str()));
        regis->Setfecha(campos[5]);
        regis->Setnmuestra(atoi(campos[6].c_str()));
        regs.push_back(regis);
        totallineas++;
    }
    entrada.close();
    if(report_err != 0)
        salidaerr.close();
    std::string sep = std::string(CUtiles::carSeparador());

    // Ahora procedo a registrar en BD
    if(conn->InsertRegs(regs) > 0){
        // ahora muevo el archivo a la ruta de procesados
        string nomPrc = rutaprc + sep + nomArch;
        rename(rutaarch.c_str(),nomPrc.c_str());
    }

    resumen();

    return totallineas;
}

void CLector::resumen(){
    std::string sep = std::string(CUtiles::carSeparador());    
    std::cout << "Se proceso el archivo:\t" << rutaarch <<std::endl;
    std::string nomPrc = rutaprc + sep + CUtiles::traerNombreArchivo(rutaarch);
    std::cout << "Se mueve hacia:\t\t" << nomPrc << std::endl;
    std::cout << "Lineas procesadas:\t\t" << totallineas << std::endl;
    std::cout << "Lineas con error:\t\t" << lineaserror << std::endl;
}


// Fin de la implementacion
