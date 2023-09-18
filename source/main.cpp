#include "..\include\stringOperations.h"
#include "..\include\sortingOperations.h"
#include "..\include\test.h"

/*
TODO:
- better swap function 
- lexogra... change comments
- add -h
- better README 
- bubble sort or qsort arg option
- shorter partition lines
- MODE_ prefixes
- Better error and free(), close() handling.
    Change return values for that
- wrap File to normilized buffer into a function
- fix printLineToFile();
*/

enum Error
{
    NO_ERROR,
    FILE_OPEN_ERROR,
    MEM_ALLOCATION_ERROR,
    STAT_ERROR,
    INVALID_ARGS,
    UNEXPECTED_ERROR,
};

/// @brief Represents the program's operating mode.
enum Mode
{
    MODE_ORIGINAL,      ///< Copies the original text.
    MODE_STRAIGHT_SORT, ///< Sorts lines lexicographically.
    MODE_REVERSED_SORT, ///< Sorts reversed lines lexicographically.
    MODE_TEST,          ///< Runs some tests.
    MODE_ERROR,         ///< ERROR.
};

static Mode parseArguments(int argc, char** argv, char** inFile, const char** outFile);

int main(int argc, char** argv)
{
    char*        inputFile_name = NULL;
    const char* outputFIle_name = NULL;

    Mode mode = parseArguments(argc, argv, &inputFile_name, &outputFIle_name);

    if (mode == MODE_ERROR)
        return INVALID_ARGS;
        
    if (mode == MODE_TEST)
    {
        testCompareString();
        testSorting(qsort, compare_ints);
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
        case MODE_ORIGINAL:
            fputs(buffer, outputFile);
            break;
        case MODE_STRAIGHT_SORT:
            my_qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToLines);
            printTextToFile(txt, outputFile, '\n');
            break;
        case MODE_REVERSED_SORT:
            my_qsort((void*)(txt), nLines, sizeof(line), compareLinePointersToReversedLines);
            printTextToFile(txt, outputFile, '\n');
            break;
        case MODE_ERROR:
            return UNEXPECTED_ERROR;
        case MODE_TEST:
            return UNEXPECTED_ERROR;
        default:
            return UNEXPECTED_ERROR;
    }

    fclose(outputFile);
    free(txt);
    free(buffer);
}

// Parse command line arguments.
static Mode parseArguments(int argc, char** argv, char** inFile, const char** outFile) 
{
    Mode mode = MODE_ERROR; // Original by default.

    *inFile = NULL;
    const char* defaultOuputName = "output.txt";
    *outFile = defaultOuputName;

    if (argc < 2) 
    {
        fprintf(stderr, "Invalid options, use: %s [-s|-r|-o] -input <input_file> [-output <output_file>]\n", argv[0]);
        return MODE_ERROR;
    }

    for (int i = 1; i < argc; i++) 
    {
        if      (strcmp(argv[i], "-s") == 0)  mode = MODE_STRAIGHT_SORT; 
        else if (strcmp(argv[i], "-r") == 0)  mode = MODE_REVERSED_SORT; 
        else if (strcmp(argv[i], "-o") == 0)  mode = MODE_ORIGINAL; 
        else if (strcmp(argv[i], "-t") == 0)  return MODE_TEST;
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
            fprintf(stderr, "Invalid option or missing argument: %s\n", argv[i]);
            return MODE_ERROR;
        }
    }
    if (*inFile == NULL)
    {
        fprintf(stderr, "Invalid options, use: %s [-s|-r|-o] -input <input_file> [-output <output_file>ЫЫЫЫЫЫЫЫ\n", argv[0]);
        return MODE_ERROR;
    }

    return mode;
}