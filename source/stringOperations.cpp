#include "..\include\stringOperations.h"


void printTextToFile(line* txt, FILE* file, const char delim)
{
    for (int i = 0; txt[i].str; i++)
    {
        printLineToFile(txt[i].str, delim, file);
    }

}

Error FileToBuffer(char** buffer, const size_t size, const char* FILE_NAME)
{
    char* buf = (char*)calloc(size + 1, sizeof(char));
    if (buf == NULL)
    {
        perror("Memory allocation error");
        return MEM_ALLOCATION_ERROR;
    }

    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL)
    {
        perror("File opening error");
        return FILE_OPEN_ERROR;
    }

    if (fread(buf, sizeof(char), size, file) != size)
    {
        perror("Reading from file error.");
        return FREAD_ERROR;
    }
    fclose(file);

    buf[size] = '\0';
    *buffer = buf;

    return NO_ERROR;
}


Error getFileSize(const char* fileName, size_t* size)
{
    struct stat bf = {};
    int error = stat(fileName, &bf);
    if (error == -1)
    {
        perror("Stat error");
        return STAT_ERROR;
    }

    *size = bf.st_size;
    return NO_ERROR;
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


line* parseBufferToLines(char* buffer, size_t* nLines, const char delimiter)
{
    // If there are 2 \n, there might be 3 lines, hence + 1.
    *nLines = nCharactersInString(buffer, delimiter) + 1U;

    line* text = (line*)calloc(*nLines + 1U, sizeof(line));
    if (text == NULL)
    {
        perror("Memory allocation error");
        return NULL;
    }

    size_t line = 0U;

    text[line].str = buffer;
    line++;

    char* newLine = buffer;
    char* oldLine = buffer;
    while ((newLine = strchr(newLine, delimiter)) != NULL)
    {
        text[line - 1].len = ((size_t)newLine - (size_t)oldLine) / sizeof(char);
        text[line].str = ++newLine;
        oldLine = newLine;
        line++;
    }
    text[line - 1].len = ((size_t)strchr(text[line - 1].str, '\0') - (size_t)text[line - 1].str) / sizeof(char);
    text[*nLines].str = nullptr;

    return text;
}


void printLineToFile(const char* input, const char delim, FILE* file)
{
    for (int i = 0; input[i] != delim && input[i] != '\0'; i++)
    {
        fputc(input[i], file); // <----------------------------- fix slow
    }
    fputc('\n', file);
}
