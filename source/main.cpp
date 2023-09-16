#include "..\include\stringOperations.h"
#include "..\include\sortingOperations.h"
#include "..\include\test.h"

//#define TEST

/*
TODO:
- Make a struct that contains every line's length +
- quickSort
- console input +
- better swap function 
- lexogra... change comments
*/

enum Error
{
    FILE_OPEN_ERROR,
    MEM_ALLOCATION_ERROR,
    STAT_ERROR,
    INVALID_ARGS,
    UNEXPECTED_ERROR,
};

enum Mode
{
    ORIGINAL,
    STRAIGHT_SORT,
    REVERSED_SORT,
    TEST,
    ERROR,
};

Mode parseArguments(int argc, char** argv, char** inFile, char** outFile);

int main(int argc, char** argv)
{
    char*  inputFile_name = NULL;
    char* outputFIle_name = NULL;
    Mode mode = parseArguments(argc, argv, &inputFile_name, &outputFIle_name);
    printf("Input file: %s \nOutput file: %s \n", inputFile_name, outputFIle_name);
    if (mode == ERROR)
        return INVALID_ARGS;
        
    if (mode == TEST)
    {
        testCompareString();
        testSorting(bubbleSort, compare_ints);
        return 0;
    }


    FILE* outputFile = fopen(outputFIle_name, "w");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        return FILE_OPEN_ERROR;
    }

    // Create a buffer.
    ssize_t sizeErr = getFileSize(inputFile_name);
    if (sizeErr == -1)
        return STAT_ERROR;
    size_t size = (size_t)sizeErr;

    char* buffer = FileToBuffer(&size, inputFile_name);
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


    // buffer should look like: "aaa \n bbb \n ccc \n asdasd \0 "  
    
    switch (mode)
    {
        case ORIGINAL:
            fputs(buffer, outputFile);
            break;
        case STRAIGHT_SORT:
            qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToLines);
            printTextToFile(txt, outputFile, '\n');
            break;
        case REVERSED_SORT:
            qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToReversedLines);
            printTextToFile(txt, outputFile, '\n');
            break;
        default:
            return UNEXPECTED_ERROR;
            break;
    }

    fclose(outputFile);
    free(txt);
    free(buffer);
}

// Function to parse command line arguments.
Mode parseArguments(int argc, char** argv, char** inFile, char** outFile) 
{
    Mode mode = ORIGINAL; // Original by default.

    if (argc < 3) 
    {
        fprintf(stderr, "Invalid options, use: %s [-s|-r|-o] -input <input_file> -output <output_file>\n", argv[0]);
        return ERROR;
    }

    for (int i = 1; i < argc; i++) 
    {
        if      (strcmp(argv[i], "-s") == 0)  mode = STRAIGHT_SORT; 
        else if (strcmp(argv[i], "-r") == 0)  mode = REVERSED_SORT; 
        else if (strcmp(argv[i], "-o") == 0)  mode = ORIGINAL; 
        else if (strcmp(argv[i], "-t") == 0)  mode = TEST;
        else if (strcmp(argv[i], "-input") == 0 && i + 1 < argc) 
        {
            *inFile = argv[i + 1];
            i++; // Skip the next argument
        }
        else if (strcmp(argv[i], "-output") == 0 && i + 1 < argc) 
        {
            *outFile = argv[i + 1];
            i++; // Skip the next argument
        } 
        else 
        {
            fprintf(stderr, "Invalid option or argument: %s\n", argv[i]);
            return ERROR;
        }
    }
    return mode;
}