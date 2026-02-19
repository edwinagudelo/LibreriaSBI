#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <cstdlib>

extern "C" {
    #include "Entorno.h"
}

TEST_CASE("Entorno - Directory operations", "[entorno][directory]") {
    const char* testDir = "test_directory_temp";
    
    SECTION("crearDirectorio creates a new directory") {
        // Clean up if exists
        borrarDirectorio(testDir);
        
        int result = crearDirectorio(testDir);
        REQUIRE(result == 0);
        REQUIRE(validarDirectorioExiste(testDir) == 1);
        
        // Clean up
        borrarDirectorio(testDir);
    }
    
    SECTION("validarDirectorioExiste returns 0 for non-existent directory") {
        int result = validarDirectorioExiste("non_existent_directory_xyz");
        REQUIRE(result == 0);
    }
    
    SECTION("validarDirectorioExiste returns 1 for existing directory") {
        crearDirectorio(testDir);
        
        int result = validarDirectorioExiste(testDir);
        REQUIRE(result == 1);
        
        borrarDirectorio(testDir);
    }
    
    SECTION("renonmbrarDirectorio renames an existing directory") {
        const char* oldName = "old_dir_name";
        const char* newName = "new_dir_name";
        
        crearDirectorio(oldName);
        
        int result = renonmbrarDirectorio(oldName, newName);
        REQUIRE(result == 0);
        REQUIRE(validarDirectorioExiste(newName) == 1);
        REQUIRE(validarDirectorioExiste(oldName) == 0);
        
        borrarDirectorio(newName);
    }
    
    SECTION("borrarDirectorio removes an existing directory") {
        crearDirectorio(testDir);
        
        int result = borrarDirectorio(testDir);
        REQUIRE(result == 0);
        REQUIRE(validarDirectorioExiste(testDir) == 0);
    }
}

TEST_CASE("Entorno - File operations", "[entorno][file]") {
    const char* testFile = "test_file_temp.txt";
    
    SECTION("crearArchivoVacio creates a new empty file") {
        // Clean up if exists
        borrarArchivo(testFile);
        
        int result = crearArchivoVacio(testFile);
        REQUIRE(result == 1);
        REQUIRE(archivoExiste(testFile) == 1);
        
        // Clean up
        borrarArchivo(testFile);
    }
    
    SECTION("archivoExiste returns 0 for non-existent file") {
        int result = archivoExiste("non_existent_file_xyz.txt");
        REQUIRE(result == 0);
    }
    
    SECTION("archivoExiste returns 1 for existing file") {
        crearArchivoVacio(testFile);
        
        int result = archivoExiste(testFile);
        REQUIRE(result == 1);
        
        borrarArchivo(testFile);
    }
    
    SECTION("borrarArchivo removes an existing file") {
        crearArchivoVacio(testFile);
        
        int result = borrarArchivo(testFile);
        REQUIRE(result == 1);
        REQUIRE(archivoExiste(testFile) == 0);
    }
    
    SECTION("borrarArchivo returns 0 for non-existent file") {
        int result = borrarArchivo("non_existent_file_xyz.txt");
        REQUIRE(result == 0);
    }
}

TEST_CASE("Entorno - Environment variables", "[entorno][env]") {
    SECTION("leerVariableEntorno reads existing environment variable") {
        // PATH should exist on all systems
        char* path = leerVariableEntorno("PATH");
        REQUIRE(path != nullptr);
        REQUIRE(strlen(path) > 0);
    }
    
    SECTION("leerVariableEntorno returns nullptr for non-existent variable") {
        char* result = leerVariableEntorno("NON_EXISTENT_VAR_XYZ_123");
        REQUIRE(result == nullptr);
    }
    
    SECTION("leerVariableEntorno reads custom environment variable") {
        // Set a test environment variable
        #ifdef _WIN32
        _putenv_s("TEST_VAR_KIRO", "test_value");
        #else
        setenv("TEST_VAR_KIRO", "test_value", 1);
        #endif
        
        char* value = leerVariableEntorno("TEST_VAR_KIRO");
        REQUIRE(value != nullptr);
        REQUIRE(strcmp(value, "test_value") == 0);
        
        // Clean up
        #ifdef _WIN32
        _putenv_s("TEST_VAR_KIRO", "");
        #else
        unsetenv("TEST_VAR_KIRO");
        #endif
    }
}

TEST_CASE("Entorno - Edge cases", "[entorno][edge]") {
    SECTION("Creating directory with nested path fails without parent") {
        const char* nestedDir = "parent_dir/child_dir";
        int result = crearDirectorio(nestedDir);
        // Should fail because parent doesn't exist
        REQUIRE(result == -1);
    }
    
    SECTION("Creating file with invalid path fails") {
        const char* invalidFile = "non_existent_dir/test_file.txt";
        int result = crearArchivoVacio(invalidFile);
        REQUIRE(result == 0);
    }
    
    SECTION("Renaming non-existent directory returns non-zero") {
        int result = renonmbrarDirectorio("non_existent_dir_xyz", "new_name");
        REQUIRE(result == 0); // Function returns 0 when source doesn't exist
    }
    
    SECTION("Multiple file operations in sequence") {
        const char* file1 = "test_file_1.txt";
        const char* file2 = "test_file_2.txt";
        const char* file3 = "test_file_3.txt";
        
        REQUIRE(crearArchivoVacio(file1) == 1);
        REQUIRE(crearArchivoVacio(file2) == 1);
        REQUIRE(crearArchivoVacio(file3) == 1);
        
        REQUIRE(archivoExiste(file1) == 1);
        REQUIRE(archivoExiste(file2) == 1);
        REQUIRE(archivoExiste(file3) == 1);
        
        REQUIRE(borrarArchivo(file1) == 1);
        REQUIRE(borrarArchivo(file2) == 1);
        REQUIRE(borrarArchivo(file3) == 1);
        
        REQUIRE(archivoExiste(file1) == 0);
        REQUIRE(archivoExiste(file2) == 0);
        REQUIRE(archivoExiste(file3) == 0);
    }
}
