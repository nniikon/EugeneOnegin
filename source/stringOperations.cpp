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

void deleteNonLetterCharacters(char* input, const char delim)
{
    const char ascii_a = 97;
    const char ascii_z = 122;
    const char ascii_A = 65;
    const char ascii_Z = 90;

    size_t currentEmptySpace = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        //putc(input[i], stdout);
        if ((ascii_a <= input[i] && input[i] <= ascii_z) || (ascii_A <= input[i] && input[i] <= ascii_Z))
        {
            input[currentEmptySpace] = input[i];
            currentEmptySpace++;
        }
    }
    input[currentEmptySpace] = '\0';
}


int compareLines(const void* str1, const void* str2)
{
    // printf("\t\t compareLines:\n");
    // printf("\t\t adress_1: %u", (size_t)str1);
    // printLine((char*)str1, '\n');
    // printf("\t\t adress_2: %u", (size_t)str2);
    // printLine((char*)str2, '\n');

    char strdup1[MAX_LINE_SIZE] = "";
    char strdup2[MAX_LINE_SIZE] = "";

    strncpy(strdup1, (*(const char**)str1), MAX_LINE_SIZE);
    strncpy(strdup2, (*(const char**)str2), MAX_LINE_SIZE);

    deleteNonLetterCharacters(strdup1, '\n');
    deleteNonLetterCharacters(strdup2, '\n');
    int  i = 0;
    for (i = 0; strdup1[i] != '\n'  && strdup2[i] != '\n' && strdup1[i] && strdup2[i]; i++)
    {
        // Ignore register to compare strings 
        strdup1[i] = (char)tolower(strdup1[i]);
        strdup2[i] = (char)tolower(strdup2[i]);
        if (int(strdup1[i]) < int(strdup2[i]))
        {
            return -1;
        }
        else if (int(strdup1[i]) > int(strdup2[i]))
        {
            return 1;
        }
    }
    // If strdup1 and strdup2 are the same length.
    if (strdup1[i] == '\0' && strdup2[i] == '\0')
    {
        return 0;
    }
    // If strdup1 is shorter...
    else if (strdup1[i] == '\0')
    {
        return 1; // ... it goes first
    }
    else
    {
        return -1;
    }
    
    // Error
    assert(0);
    return -100;
}
    


char* FileToBuffer(off_t size, const char* FILE_NAME)
{
    char*  buf = (char*)calloc(size, sizeof(char));
    assert(buf);

    FILE  *file = fopen(FILE_NAME, "rb");
    assert(file);

    fread (buf, sizeof(char), size, file);
    buf[size] = '\0';
    return buf;
}


off_t getFileSize(const char* fileName)
{
    struct stat bf;
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
    // If there are 2 \n, there are 3 lines, hence + 1.
    *nLines = nCharactersInString(buffer, '\n') + (size_t) 1;

    char** text = (char**)calloc(*nLines + 1, sizeof(char*));
    
    text[*nLines] = NULL;

    size_t line = 0;

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


void printLine(const char* input, const char delim)
{
    assert(input);
    for (int i = 0; input[i] != delim && input[i] != '\0'; i++)
    {
        fputc(input[i], stdout);
    }
    fputc('\n', stdout);
}