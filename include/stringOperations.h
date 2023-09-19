#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>


enum Error
{
    NO_ERROR,
    FILE_OPEN_ERROR,
    MEM_ALLOCATION_ERROR,
    STAT_ERROR,
    INVALID_ARGS,
    UNEXPECTED_ERROR,
    FREAD_ERROR,
};


/// @brief A structure for storing a `char*` string along with it's length.
struct line
{
    char* str;  /**< The `char*` string.       */
    size_t len; /**< The length of the string. */
};



/**
 * @brief Prints a `line*` text into the file.
 *
 * @param txt   The struct text array.
 * @param file  The opened for writing file.
 * @param delim The symbol each `line[i].str` is ending with.
 */
void printTextToFile(line* txt, FILE* file, const char delim);

/**
 * @brief Moves data from a file to the buffer.
 *
 * This function copies information from the provided file to the allocated char* array
 *
 * @param size[in]       A size of the file. 
 * @param FILE_NAME[in]  A name of the file.
 * @param buffer[in,out] A pointer to a buffer of the data from the file.
 * 
 * @return The `Error` code.
 *
 * @note Don't forget to `free()` the given pointer.
 */
Error FileToBuffer(char** buffer, const size_t size, const char* FILE_NAME);

/**
 * @brief Gets a file size by it's name.
 *
 * @param[in]  fileName The file name.
 * @param[out] size     Pointer to the size of the file to be set.
 * 
 * @return The `Error` code.
 */
Error getFileSize(const char* fileName, size_t* size);

/**
 * @brief Removes all consecutive occurrences of the given character in the string.
 *
 * @param[in,out] input The input string.
 * @param[in]     chr   The character to be removed.
 */
void deleteRepetitiveCharacters(char input[], const char chr);

/**
 * @brief Replaces every given symbol with another symbol.
 *
 * @param[in,out] input The input string.
 * @param[in]     dst   The symbol that will be replaced.
 * @param[in]     src   The symbol that will replace the given symbol.
 */
void replaceCharacter(char input[], const char dst, const char src);

/**
 * @brief Counts the amout of given characters in the string.
 *
 * @param[in] input The input string.
 * @param[in] chr   The character.
 * @return The amount of given characters in the string.
 */
size_t nCharactersInString(const char input[], const char chr);

/**
 * @brief Prints a string to the file and stops at the given delimiter.
 *
 * @param[in] input The input string.
 * @param[in] delim The delimiter.
 * @param[in] file  The file.
 */
void printLineToFile(const char* input, const char delim, FILE* file);

/**
 * @brief Returns an array of pointer, each pointing to the start of a new line.
 *
 * @param[in]  buffer    The buffer that needs to be parsed.
 * @param[out] nLines    The number of lines in the buffer.
 * @param[in]  delimiter The symbol that indicates a new line.
 * @param[out] dstLine   A pointer to the array on `line`, ending with `NULL`.
 * 
 * @return The `Error` code.
 *
 * @note Don't forget to `free()` the given pointer.
*/
Error parseBufferToLines(line** dstLine, char* buffer, size_t* nLines, const char delimiter);

#endif