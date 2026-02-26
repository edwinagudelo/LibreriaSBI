#ifndef CONFIGURA_H
#define CONFIGURA_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @file Configura.h
 * @brief Configuration parameter management system
 * 
 * This module provides a dynamic parameter storage system using a linked list
 * structure. It allows storing key-value pairs of any data type and retrieving
 * them as needed. The system manages memory allocation automatically.
 */

/**
 * @struct Param
 * @brief Structure representing a configuration parameter node
 * 
 * This structure forms a linked list where each node contains:
 * - A parameter name (key)
 * - A parameter value (generic void pointer)
 * - A pointer to the next parameter in the list
 */
struct Param
{
    char* paramName;    /**< Parameter name/key as null-terminated string */
    void* paramValue;   /**< Parameter value as generic pointer */
    struct Param* next; /**< Pointer to next parameter in linked list */
};

/**
 * @brief Add a new parameter to the configuration system
 * 
 * Creates a new parameter node and adds it to the end of the linked list.
 * The function allocates memory for both the parameter name and value,
 * making a deep copy of the provided data.
 * 
 * @param name Parameter name/key as null-terminated string
 * @param value Pointer to the parameter value data
 * @param size Size in bytes of the parameter value data
 * 
 * @return OKCODE on success, NOMEMORY if memory allocation fails
 * 
 * @note The function makes copies of both name and value, so the original
 *       data can be safely freed after calling this function
 * @warning There's a bug in the implementation: paramName allocation should
 *          be strlen(name) + 1 to account for null terminator
 */
int agregarParam(char* name, void* value, size_t size);

/**
 * @brief Retrieve a parameter value as a character string
 * 
 * Searches the parameter list for a parameter with the specified key
 * and returns a copy of its value as a null-terminated string.
 * 
 * @param key Parameter name/key to search for
 * 
 * @return Pointer to newly allocated string containing the parameter value,
 *         or NULL if parameter not found or memory allocation fails
 * 
 * @note The returned string is dynamically allocated and must be freed
 *       by the caller to prevent memory leaks
 * @note The function assumes the stored parameter value is a valid string
 * @warning There's a bug in the implementation: result allocation should
 *          be strlen(tempParam->paramValue) + 1 for null terminator
 */
char* traerParamComoChar(const char* key);

/**
 * @brief Create a new parameter structure
 * 
 * Allocates memory for a new Param structure and initializes all
 * fields to NULL/safe values.
 * 
 * @return Pointer to newly allocated Param structure, or NULL if
 *         memory allocation fails
 * 
 * @note The returned structure must be properly initialized and
 *       eventually freed to prevent memory leaks
 */
struct Param* crearParam();

/**
 * @brief Free all memory allocated for the parameter system
 * 
 * Traverses the entire parameter linked list, freeing memory for
 * parameter names, values, and structures. Resets the root pointer
 * to NULL after cleanup.
 * 
 * @return Number of parameters that were freed
 * 
 * @note After calling this function, all previously retrieved parameter
 *       pointers become invalid and should not be used
 * @note This function should be called before program termination to
 *       prevent memory leaks
 */
int liberarMemoriaParametros();

#endif