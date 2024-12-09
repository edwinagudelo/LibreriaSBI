#ifndef CONFIGURA_H
#define CONFIGURA_H

#include <stdio.h>
#include <stdlib.h>

struct Param
{
    char* paramName;
    void* paramValue;
    struct Param* next;
};


/***
 * 
*/
int addParam(struct Param** root, char* name, void* value, size_t size);


/***
 * 
*/
char* getParamAsChar(struct Param* root, const char* key);

/***
 * 
*/
struct Param* createParam();


#endif