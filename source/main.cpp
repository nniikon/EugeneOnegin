#include "..\include\stringOperations.h"
#include "..\include\test.h"

static const char* FILE_NAME = "EugeneOnegin.txt";

//#define TEST

/*
TODO:
- Add error ENUM
- Check for errors(calloc, fopen...)
- Make a struct that contains every line's length
- quickSort
- console input
*/

int main()
{
    #ifdef TEST

    testCompareString();
    testSorting(bubbleSort, compare_ints);
    printf("my_strlen(<0123456789>) = %u", my_strlen("0123456789\n", '\n'));
    return 0;
    #endif

    FILE* outputFile = fopen(FILE_NAME, "w");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        return 1;
    }


    /*
    TODO:
    make a function
    make a struct
    get line lengths while creating the buffer
    */

    // Create a buffer.
    off_t size = getFileSize(FILE_NAME);
    char* buffer = FileToBuffer(&size, FILE_NAME);

    // Replace different EOL symbols on '\n'.
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');
    size_t nLines = 0;

    // Parse the buffer into the lines using \n as a delimiter.
    char** text = parseBufferToLines(buffer, &nLines, '\n');

    // buffer looks like: "aaa \n bbb \n ccc \n asdasd \0 "

    fputs("Straight sorting\n\n", outputFile);
    qsort(text, nLines, sizeof(char*), comparePointersToLines);

    printTextToFile(text, outputFile, '\n');

    fputs("\nReversed sorting\n\n", outputFile);
    bubbleSort((void*)(text), nLines, sizeof(char*), comparePointersToReversedLines);

    printTextToFile(text, outputFile, '\n');

    fputs("\nOriginal\n\n", outputFile);

    fputs(buffer, outputFile);

    fclose(outputFile);
    free(text);
    free(buffer);
}
