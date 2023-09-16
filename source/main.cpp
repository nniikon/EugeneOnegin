#include "..\include\stringOperations.h"
#include "..\include\sortingOperations.h"
//#include "..\include\test.h"

static const char* FILE_NAME = "EugeneOnegin.txt";

//#define TEST

/*
TODO:
- Make a struct that contains every line's length
- quickSort
- console input
- better swap function
- lexogra... change comments
*/
enum error
{
    FILE_OPEN_ERROR,
    MEM_ALLOCATION_ERROR,
    STAT_ERROR,
};


int main()
{
    #ifdef TEST

    testCompareString();
    testSorting(bubbleSort, compare_ints);
    printf("my_strlen(<0123456789>) = %u", my_strlen("0123456789\n", '\n'));
    return 0;

    #endif


    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        return FILE_OPEN_ERROR;
    }


    // Create a buffer.
    ssize_t sizeErr = getFileSize(FILE_NAME);
    if (sizeErr == -1)
        return STAT_ERROR;
    size_t size = (size_t)sizeErr;

    char* buffer = FileToBuffer(&size, FILE_NAME);
    if (buffer == NULL)
        return FILE_OPEN_ERROR;
    

    // Replace different EOL symbols on '\n'.
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');
    size_t nLines = 0;

    // Parse the buffer into the lines using \n as a delimiter.
    line* txt = parseBufferToLines(buffer, &nLines, '\n');
    if (txt == NULL)
        return MEM_ALLOCATION_ERROR;
    
    for (size_t i = 0; txt[i].str; i++)
    {
        printLineToFile(txt[i].str, '\n', stdout);
        printf("%u\n", txt[i].len);
    }


    // buffer should look like: "aaa \n bbb \n ccc \n asdasd \0 "  
    
    fputs("Straight sorting\n\n", outputFile);
    qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToLines);
    printTextToFile(txt, outputFile, '\n');

    fputs("\nReversed sorting\n\n", outputFile);
    qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToReversedLines);
    printTextToFile(txt, outputFile, '\n');

    fputs("\nOriginal\n\n", outputFile);
    fputs(buffer,           outputFile);

    fclose(outputFile);
    free(txt);
    free(buffer);
}
