
#include "Configura.h"
#include "Constantes.h"

#include <string.h>


struct Param* createParam(){
    struct Param* result = NULL;
    result = malloc(sizeof(struct Param));
    if(result){
        result->paramName = NULL;
        result->next = NULL;
        result->paramValue = NULL;
    }
    return result;
}

int addParam(struct Param** root, char* name, void* value, size_t size){
    int result = OKCODE;
    struct Param* newOne = createParam();
    struct Param* tempParam = NULL;

    if (!newOne) {
        result = NOMEMORY;
        return result;
    }
    newOne->paramName = malloc(sizeof(char) * strlen(name));
    newOne->paramValue = malloc(size);
    memcpy(newOne->paramValue, value, size);

    if (*root == NULL) {
        *root = newOne;
    }
    else {
        tempParam = (*root);
        while (tempParam->next != NULL) {
            tempParam = tempParam->next;
        }
        tempParam->next = newOne;
    }

    return result;
}

char* getParamAsChar(struct Param* root, const char* key){
    struct Param* tempParam = root;
    char *result = NULL;
    while ( tempParam != NULL ) {
        if (strcmp(tempParam->paramName, key) == 0) {
            result = malloc(sizeof(char)* strlen(tempParam->paramValue));
            strcpy(result, tempParam->paramValue);
            break;
        }
        tempParam = tempParam->next;
    }
    return result;
}