
#include "Configura.h"
#include "Constantes.h"

#include <string.h>

// Global variable for the parameter linked list
static struct Param *paramRoot = NULL;

struct Param* crearParam(){
    struct Param* result = NULL;
    result = malloc(sizeof(struct Param));
    if(result){
        result->paramName = NULL;
        result->next = NULL;
        result->paramValue = NULL;
    }
    return result;
}

int agregarParam(char* name, void* value, size_t size){
    int result = OKCODE;

    struct Param* newOne = crearParam();
    struct Param* tempParam = NULL;

    if (!newOne) {
        result = NOMEMORY;
        return result;
    }
    newOne->paramName = malloc(sizeof(char) * (strlen(name) + 1));
    if (!newOne->paramName) {
        free(newOne);
        return NOMEMORY;
    }
    strcpy(newOne->paramName, name);
    
    newOne->paramValue = malloc(size);
    if (!newOne->paramValue) {
        free(newOne->paramName);
        free(newOne);
        return NOMEMORY;
    }
    memcpy(newOne->paramValue, value, size);

    if (paramRoot == NULL) {
        paramRoot = newOne;
    }
    else {
        tempParam = (paramRoot);
        while (tempParam->next != NULL) {
            tempParam = tempParam->next;
        }
        tempParam->next = newOne;
    }

    return result;
}

char* traerParamComoChar(const char* key){
    struct Param* tempParam = paramRoot;
    char *result = NULL;
    while ( tempParam != NULL ) {
        if (strcmp(tempParam->paramName, key) == 0) {
            // Assume paramValue is a null-terminated string
            // Calculate length safely by treating it as a string
            const char* strValue = (const char*)tempParam->paramValue;
            size_t len = strlen(strValue);
            result = (char*)malloc(sizeof(char) * (len + 1));
            if (result) {
                strcpy(result, strValue);
            }
            break;
        }
        tempParam = tempParam->next;
    }
    return result;
}

int liberarMemoriaParametros() {
    int result = 0;
    struct Param* current = paramRoot;
    struct Param* next;

    while (current != NULL) {
        next = current->next;
        free(current->paramName);
        free(current->paramValue);
        free(current);
        current = next;
        result++;
    }
    paramRoot = NULL; // Reset the root pointer
    return result; // Indicate success
}