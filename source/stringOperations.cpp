#include "..\include\stringOperations.h"


const int MAX_LINE_SIZE = 512;
/*
    static char* my_strdup(const char* input)
    {
        size_t inputLength = strlen(input);
        char* result = (char*)malloc(inputLength + 1);
        memcpy(result, input, inputLength+1);
        return result;
    }
*/
/*
void deleteNonLetterCharacters(char* input, const char delim // fignya
{
    const char ascii_a = 97;
    const char ascii_z = 122;
    const char ascii_A = 65;
    const char ascii_Z = 90;



    size_t readIndex = 0;
    size_t writeIndex = 0;

    while (input[readIndex] != '\0' && input[readIndex] != delim)
    {
        if ((ascii_a <= input[readIndex] && input[readIndex] <= ascii_z) ||
            (ascii_A <= input[readIndex] && input[readIndex] <= ascii_Z))
        {
            input[writeIndex] = input[readIndex];
            writeIndex++;
        }

        readIndex++;
    }

    input[writeIndex] = delim;
}
*/

void printTextToFile(char** text, FILE* file, const char delim)
{
    for (int i = 0; text[i]; i++)
        printLineToFile(text[i], delim, file);

}

char* FileToBuffer(off_t* size, const char* FILE_NAME)
{
    char*  buf = (char*)calloc(*size + 1, sizeof(char));
    assert(buf)

    FILE  *file = fopen(FILE_NAME, "rb");
    assert(file)

    *size = fread(buf, sizeof(char), *size, file);
    buf[*size] = '\0';

    fclose(file);

    return buf;
}


off_t getFileSize(const char* fileName)
{
    struct stat bf = {};
    stat(fileName, &bf);
    return bf.st_size;
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


size_t nCharactersInString(const char input[], const char chr)
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

char** parseBufferToLines(char* buffer, size_t* nLines, const char delimiter)
{
    // If there are 2 \n, there might be 3 lines, hence + 1.
    *nLines = nCharactersInString(buffer, '\n') + 1ULL;

    char** text = (char**)calloc(*nLines + 1ULL, sizeof(char*));

    text[*nLines] = nullptr;

    size_t line = 0ULL;

    text[line] = buffer;
    line++;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if(buffer[i] == delimiter)
        {
            text[line] = (buffer + i + 1);
            line++;
        }
    }

    return text;
}

size_t my_strlen(const char* input, const char delim)
{
    size_t i = 0;
    for (i = 0; input[i] != delim && input[i] != '\0'; i++)
    {}
    return i;
}

void printLineToFile(const char* input, const char delim, FILE* file)
{
    for (int i = 0; input[i] != delim && input[i] != '\0'; i++)
    {
        3A_fputc_SLOMAY_KOLENO(input[i], file);
    }
    fputc('\n', file);
}
