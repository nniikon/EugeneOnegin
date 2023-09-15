#include "..\include\stringOperations.h"
#include "..\include\test.h"

static const char* FILE_NAME = "EugeneOnegin.txt";

//#define TEST

static FILE* openFile(const char* fileName)
{
    FILE* outputFile = fopen(fileName, "w");
    if (outputFile == NULL) 
    {
        perror("Error opening file");
        abort();
    }
}


int main()
{
    #ifdef TEST

    testCompareString();
    testSorting(bubbleSort, compare_ints);
    printf("my_strlen(<0123456789>) = %u", my_strlen("0123456789\n", '\n'));

    #else

    // Create the output file.
    FILE* outputFile = openFile("output.txt");
    
    // Create a buffer.
    off_t size = getFileSize(FILE_NAME);
    char* buffer = FileToBuffer(&size, FILE_NAME);
    
    // Replace different EOL symbols on '\n'.
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');
    size_t nLines = 0;

    // Parse the buffer into the lines using \n as a delimiter.
    char** text = parseBufferToLines(buffer, &nLines, '\n');

    // buffer: "aaa \n bbb \n ccc \n asdasd \0 "

    for (int i = 0; text[i]; i++)
        printLineToFile(text[i], '\n', outputFile);

    fputs("\nStraight sorting\n\n", outputFile);
    qsort(text, nLines, sizeof(char*), comparePointersToLines);

    for (int i = 0; text[i]; i++)
        printLineToFile(text[i], '\n', outputFile);

    fputs("\nReversed sorting\n\n", outputFile);
    bubbleSort((void*)(text), nLines, sizeof(char*), comparePointersToReversedLines);

    for (int i = 0; text[i]; i++)
        printLineToFile(text[i], '\n', outputFile);

    fclose(outputFile);
    free(text);
    free(buffer);
    #endif
}