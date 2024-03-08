/**
 * Libreria SBI
 * 
 * Este archivo tiene como finalidad validar las funcionalidades que se desarrollan en la libreria
 * 
 * Ing. Edwin Agudelo
 * 
*/

#include <iostream>
#include <memory>

#include "CConfigura.h"

void test_configura(){
    std::cout << "Iniciando pruebas de CConfigura" << std::endl;
    std::unique_ptr<CConfigura> config = std::make_unique<CConfigura>();
    auto setparam = config->setParam("prueba", "123");
    if (!setparam) {
        std::cout << "Error: El parametro no se pudo setear" << std::endl;
    }
    else {
        std::cout << "Parametro seteado correctamente" << std::endl;
    }
    config->setModif(false);
    setparam = config->setParam("prueba", "345");
    if (setparam) {
        std::cout << "Error: El parametro se dejo modificar" << std::endl;
    }
    else {
        std::cout << "El parametro no se dejo modifiacar" << std::endl;
    }
    auto param = config->getParam("prueba");
    if (param != "123") {
        std::cout << "Error: El parametro no es el esperado -- " << param << std::endl;
    }
    else {
        std::cout << "El parametro es el esperado [" << param << "]" << std::endl;
    }
}


int main(){
    std::cout << "Libreria SBI" << std::endl;
    std::cout << "Probando" << std::endl;

    test_configura();
    
    return 0;
}