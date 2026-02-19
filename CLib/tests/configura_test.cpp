#include <catch2/catch_test_macros.hpp>
#include <cstring>

extern "C" {
    #include "Configura.h"
    #include "Constantes.h"
}

// Helper to ensure clean state before each test
class ConfiguraTestFixture {
public:
    ConfiguraTestFixture() {
        liberarMemoriaParametros();
    }
    ~ConfiguraTestFixture() {
        liberarMemoriaParametros();
    }
};

TEST_CASE("Configura - Parameter creation", "[configura]") {
    SECTION("crearParam creates a valid parameter structure") {
        struct Param* param = crearParam();
        
        REQUIRE(param != nullptr);
        REQUIRE(param->paramName == nullptr);
        REQUIRE(param->paramValue == nullptr);
        REQUIRE(param->next == nullptr);
        
        free(param);
    }
}

TEST_CASE("Configura - Adding string parameters", "[configura]") {
    ConfiguraTestFixture fixture;
    
    SECTION("agregarParam adds a string parameter successfully") {
        const char* testName = "test_key";
        const char* testValue = "test_value";
        
        int result = agregarParam(
            const_cast<char*>(testName), 
            const_cast<void*>(static_cast<const void*>(testValue)), 
            strlen(testValue) + 1
        );
        
        REQUIRE(result == OKCODE);
        
        char* retrieved = traerParamComoChar(testName);
        REQUIRE(retrieved != nullptr);
        REQUIRE(strcmp(retrieved, testValue) == 0);
        
        free(retrieved);
    }
    
    SECTION("agregarParam adds multiple string parameters") {
        const char* key1 = "key1";
        const char* value1 = "value1";
        const char* key2 = "key2";
        const char* value2 = "value2";
        const char* key3 = "key3";
        const char* value3 = "value3";
        
        REQUIRE(agregarParam(const_cast<char*>(key1), const_cast<void*>(static_cast<const void*>(value1)), strlen(value1) + 1) == OKCODE);
        REQUIRE(agregarParam(const_cast<char*>(key2), const_cast<void*>(static_cast<const void*>(value2)), strlen(value2) + 1) == OKCODE);
        REQUIRE(agregarParam(const_cast<char*>(key3), const_cast<void*>(static_cast<const void*>(value3)), strlen(value3) + 1) == OKCODE);
        
        char* retrieved1 = traerParamComoChar(key1);
        char* retrieved2 = traerParamComoChar(key2);
        char* retrieved3 = traerParamComoChar(key3);
        
        REQUIRE(retrieved1 != nullptr);
        REQUIRE(retrieved2 != nullptr);
        REQUIRE(retrieved3 != nullptr);
        
        REQUIRE(strcmp(retrieved1, value1) == 0);
        REQUIRE(strcmp(retrieved2, value2) == 0);
        REQUIRE(strcmp(retrieved3, value3) == 0);
        
        free(retrieved1);
        free(retrieved2);
        free(retrieved3);
    }
}

TEST_CASE("Configura - Retrieving parameters", "[configura]") {
    ConfiguraTestFixture fixture;
    
    SECTION("traerParamComoChar returns nullptr for non-existent key") {
        char* result = traerParamComoChar("non_existent_key");
        REQUIRE(result == nullptr);
    }
    
    SECTION("traerParamComoChar retrieves correct value") {
        const char* key = "test_key";
        const char* value = "test_value";
        
        agregarParam(const_cast<char*>(key), const_cast<void*>(static_cast<const void*>(value)), strlen(value) + 1);
        
        char* retrieved = traerParamComoChar(key);
        REQUIRE(retrieved != nullptr);
        REQUIRE(strcmp(retrieved, value) == 0);
        
        free(retrieved);
    }
    
    SECTION("traerParamComoChar handles empty string values") {
        const char* key = "empty_key";
        const char* value = "";
        
        agregarParam(const_cast<char*>(key), const_cast<void*>(static_cast<const void*>(value)), strlen(value) + 1);
        
        char* retrieved = traerParamComoChar(key);
        REQUIRE(retrieved != nullptr);
        REQUIRE(strcmp(retrieved, value) == 0);
        
        free(retrieved);
    }
}

TEST_CASE("Configura - Memory cleanup", "[configura]") {
    ConfiguraTestFixture fixture;
    
    SECTION("liberarMemoriaParametros frees all parameters") {
        agregarParam(const_cast<char*>("key1"), const_cast<void*>(static_cast<const void*>("value1")), 7);
        agregarParam(const_cast<char*>("key2"), const_cast<void*>(static_cast<const void*>("value2")), 7);
        agregarParam(const_cast<char*>("key3"), const_cast<void*>(static_cast<const void*>("value3")), 7);
        
        int freed = liberarMemoriaParametros();
        REQUIRE(freed == 3);
        
        // After cleanup, retrieving should return nullptr
        char* result = traerParamComoChar("key1");
        REQUIRE(result == nullptr);
    }
    
    SECTION("liberarMemoriaParametros returns 0 when no parameters exist") {
        int freed = liberarMemoriaParametros();
        REQUIRE(freed == 0);
    }
    
    SECTION("liberarMemoriaParametros can be called multiple times safely") {
        agregarParam(const_cast<char*>("key1"), const_cast<void*>(static_cast<const void*>("value1")), 7);
        
        int freed1 = liberarMemoriaParametros();
        REQUIRE(freed1 == 1);
        
        int freed2 = liberarMemoriaParametros();
        REQUIRE(freed2 == 0);
    }
}

TEST_CASE("Configura - Edge cases", "[configura]") {
    ConfiguraTestFixture fixture;
    
    SECTION("Handle long parameter names and values") {
        const char* longKey = "this_is_a_very_long_parameter_name_for_testing_purposes";
        const char* longValue = "this_is_a_very_long_parameter_value_that_should_be_stored_correctly";
        
        int result = agregarParam(
            const_cast<char*>(longKey), 
            const_cast<void*>(static_cast<const void*>(longValue)), 
            strlen(longValue) + 1
        );
        
        REQUIRE(result == OKCODE);
        
        char* retrieved = traerParamComoChar(longKey);
        REQUIRE(retrieved != nullptr);
        REQUIRE(strcmp(retrieved, longValue) == 0);
        
        free(retrieved);
    }
    
    SECTION("Handle special characters in values") {
        const char* key = "special_key";
        const char* value = "value with spaces, symbols: !@#$%^&*()";
        
        agregarParam(const_cast<char*>(key), const_cast<void*>(static_cast<const void*>(value)), strlen(value) + 1);
        
        char* retrieved = traerParamComoChar(key);
        REQUIRE(retrieved != nullptr);
        REQUIRE(strcmp(retrieved, value) == 0);
        
        free(retrieved);
    }
}
