#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <ctype.h>

/**
 * @brief Moves data from a file to the buffer. 
 * 
 * This function copies information from the provided file to the allocated char* array
 * 
 * @param size      A size of the file.
 * @param FILE_NAME A name of the file.
 * @return A pointer to the buffer.
 * 
 * @note Don't forget to `free()` the given pointer.
 */
char* FileToBuffer(off_t size, const char* FILE_NAME);


/**
 * @brief Gets a file size by it's name.
 * 
 * @param fileName The file name.
 * @return The size of the file.
 */
off_t getFileSize(const char* fileName);


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
size_t nCharactersInString (const char input[], const char chr);

/**
 * @brief Prints a string to the file and stops at the given delimiter.
 * 
 * @param[in] input The input string.
 * @param[in] delim The delimiter.
 * @param[in] file  The file.
 */
void printLineToFile(const char* input, const char delim, FILE* file);

/**
 * @brief Deletes non-letter characters from the line.
 * 
 * @param[in,out] input The input string.
 * @param[in]     delim The delimiter a line ends at.
 */
void  deleteNonLetterCharacters (char* input, const char delim);

/**
 * @brief Returns an array of pointer, each pointing to the start of a new line.
 * 
 * @param[in]  buffer    A buffer that needs to be parsed.
 * @param[in]  delimiter A symbol that indicates a new line.
 * @param[out] nLines    A number of lines in the buffer.
 * 
 * @return A pointer to an array of pointers, each pointing to the start of a new line, ending with NULL.
 * 
 * @note Don't forget to `free()` the given pointer
*/
char** parseBufferToLines(char* buffer, size_t* nLines, const char delimiter);


/**
 * @brief Counts the length of the line.
 * 
 * @param input The input line.
 * @param delim The delimiter where the count stops.
 *
 * @return The length of the line. 
 */
size_t my_strlen(const char* input, const char delim);