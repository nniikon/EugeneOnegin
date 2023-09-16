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

struct line
{
    char* str;
    size_t len;
};



/**
 * @brief Puts a char** text array into the file.
 *
 * @param txt   The struct text array.
 * @param file  The opened file for writing.
 * @param delim The symbol each text[i] is ending with.
 */
void printTextToFile(line* txt, FILE* file, const char delim);

/**
 * @brief Moves data from a file to the buffer.
 *
 * This function copies information from the provided file to the allocated char* array
 *
 * @param size[in,out]  A size of the file. Changes to the real amount of read symbols. 
 * @param FILE_NAME[in] A name of the file.
 * 
 * @return A pointer to the buffer.
 *
 * @note Don't forget to `free()` the given pointer.
 */
char* FileToBuffer(size_t* size, const char* FILE_NAME);

/**
 * @brief Gets a file size by it's name.
 *
 * @param fileName The file name.
 * 
 * @return If successful, returns the size of the file. On error, returns `-1`.
 */
ssize_t getFileSize(const char* fileName);


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
void deleteNonLetterCharacters(char* input, const char delim);

/**
 * @brief Returns an array of pointer, each pointing to the start of a new line.
 *
 * @param[in]  buffer    The buffer that needs to be parsed.
 * @param[in]  delimiter The symbol that indicates a new line.
 * @param[out] nLines    The number of lines in the buffer.
 *
 * @return An array on `line`, ending with `NULL`.
 *
 * @note Don't forget to `free()` the given pointer
*/
line* parseBufferToLines(char* buffer, size_t* nLines, const char delimiter);


/**
 * @brief Counts the length of the line.
 *
 * @param input The input line.
 * @param delim The delimiter where the count stops.
 *
 * @return The length of the line.
 */
size_t my_strlen(const char* input, const char delim);

#endif