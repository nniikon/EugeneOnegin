#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
const char FILE_NAME[] = "EugeneOnegin.txt";

char*  FileToBuffer(off_t size);
void   printBuffer (const char* buffer,  size_t size);
off_t  getFileSize (const char* fileName);
void   deleteRepetitiveCharacters(char input[], const char chr);
void   replaceCharacter          (char input[], const char dst, const char src);
size_t nCharacterInString  (const char input[], const char chr);
void   printLine           (const char* input);


/**
 * @brief Returns an array of pointer, each pointing to the start of a new line.
 * 
 * @param[in] buffer A buffer that needs to be parsed.
 * 
 * @param[in] delimiter A symbol that indicates a new line.
 * 
 * @return A pointer to an array of pointers, each pointing to the start of a new line, ending with NULL.
 * 
 * @note Don't forget to `free()` the given pointer
*/
char** parseBufferToLines(char buffer[], const char delimiter);


int main()
{
    off_t size = getFileSize(FILE_NAME);
    char* buffer = FileToBuffer(size);
    
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');

    //printBuffer(buffer, size_t(size));

    char** test = parseBufferToLines(buffer, '\n');

    for (int i = 0; test[i]; i++)
    {
        printLine(test[i]);
    }
    
}

char* FileToBuffer(off_t size)
{
    char*  buf = (char*)calloc(size, sizeof(char));
    assert(buf);

    FILE  *file = fopen(FILE_NAME, "rb");
    assert(file);

    fread (buf, sizeof(char), size, file);

    return buf;
}


off_t getFileSize(const char* fileName)
{
    struct stat bf;
    stat(fileName, &bf);
    return bf.st_size;
}


void printBuffer(const char* buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if(buffer[i] == '\0' || buffer[i] == '\n' || buffer[i] == '\r')
            printf("%d ", buffer[i]);
        else
            printf("%c",  buffer[i]);
    }
    
}

// This function accepts a string and a character as input. 
// It scans through the string and removes consecutive occurrences of the specified character.
void deleteRepetitiveCharacters(char input[], const char chr)
{
    size_t currentEmptySpace = 0;

    // Iterate through the input string.
    for (size_t i = 0; input[i] != '\0'; ++i)
    {
        // If the current character is not the character to be deleted...
        if (input[i] != chr || input[i + 1] != chr)
        {
            // ... move the current character to the position of the current "empty" space and increment it.
            input[currentEmptySpace] = input[i];
            currentEmptySpace++;
        }
    }

    input[currentEmptySpace] = '\0';
}


void replaceCharacter(char input[], const char dst, const char src)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == dst)
        {
            input[i] = src;
        }  
    }
}


size_t nCharacterInString(const char input[], const char chr)
{
    size_t counter = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == chr)
        {
            counter++;
        }
    }
    return counter;
}

char** parseBufferToLines(char buffer[], const char delimiter)
{
    size_t nLines = nCharacterInString(buffer, '\n') + (size_t) 1;

    char** text = (char**) calloc(nLines + 1, sizeof(char*));
    
    text[nLines] = NULL;

    size_t line = 0;

    text[line] = buffer;
    line++;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i] == delimiter)
        {
            text[line] = buffer + i + 1;
            line++;
        }
    }
    
    return text;
}


void printLine(const char* input)
{
    assert(input);
    for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++)
    {
        fputc(input[i], stdout);
    }
    fputc('\n', stdout);
}