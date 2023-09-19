#include "..\include\stringOperations.h"
#include "..\include\sortingOperations.h"
#include "..\include\test.h"

/*
TODO:
- lexogra... change comments
- better README 
- bubble sort or qsort arg option
- shorter partition lines
- Better error and free(), close() handling.
    Change return values for that
- wrap File to normilized buffer into a function
- fix printLineToFile();
*/


/// @brief Represents the program's operating mode.
enum Mode
{
    MODE_ORIGINAL,      ///< Copies the original text.
    MODE_STRAIGHT_SORT, ///< Sorts lines lexicographically.
    MODE_REVERSED_SORT, ///< Sorts reversed lines lexicographically.
    MODE_TEST,          ///< Runs some tests.
    MODE_HELP,          ///< Prints help commands.
    MODE_ERROR,         ///< ERROR.
};

static Mode parseArguments(int argc, char** argv, char** inFile, const char** outFile);

int main(int argc, char** argv)
{
    char*        inputFile_name = NULL;
    const char* outputFIle_name = NULL;
    Error error = NO_ERROR;

    Mode mode = parseArguments(argc, argv, &inputFile_name, &outputFIle_name);

    if (mode == MODE_ERROR)
        return INVALID_ARGS;
        
    if (mode == MODE_TEST)
    {
        testCompareString();
        testSorting(qsort, compare_ints);
        return 0;
    }

    if (mode == MODE_HELP)
    {
        printf("-s      Standart sorting.              \n"
               "-r      Sorting of the reversed lines. \n"
               "-o      No sorting (original).         \n"
               "-h      Prints this message.           \n"
               "-t      Run tests.                     \n");
        return NO_ERROR;
    }

    // MEM_WARNING: outputFile was opened.
    FILE* outputFile = fopen(outputFIle_name, "w");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        return FILE_OPEN_ERROR;
    }

    // Create a buffer.
    size_t size = 0;
    error = getFileSize(inputFile_name, &size);
    if (error != NO_ERROR)
    {
        fclose(outputFile);
        return error;
    }

    // MEM_WARNING: buffer was allocated.
    char* buffer = NULL;
    error = FileToBuffer(&buffer, size, inputFile_name);
    if (error != NO_ERROR)
    {
        free(buffer);
        return error;
    }

    // Replace different EOL symbols on '\n'.
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');
    size_t nLines = 0;



    // MEM_WARNING: txt was allocated.
    // Parse the buffer into the lines using \n as a delimiter.
    line* txt = NULL;
    error = parseBufferToLines(&txt, buffer, &nLines, '\n');
    if (error != NO_ERROR)
    {
        free(buffer);
        return error;
    }

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
        case MODE_HELP:
            return UNEXPECTED_ERROR;
        default:
            return UNEXPECTED_ERROR;
    }

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
        fprintf(stderr, "Invalid options, use: %s [-s|-r|-o|-h] -input <input_file> [-output <output_file>]\n", argv[0]);
        return MODE_ERROR;
    }

    for (int i = 1; i < argc; i++) 
    {
        if      (strcmp(argv[i], "-s") == 0)    mode = MODE_STRAIGHT_SORT; 
        else if (strcmp(argv[i], "-r") == 0)    mode = MODE_REVERSED_SORT; 
        else if (strcmp(argv[i], "-o") == 0)    mode = MODE_ORIGINAL; 
        else if (strcmp(argv[i], "-t") == 0)    return MODE_TEST;
        else if (strcmp(argv[i], "-h") == 0)    return MODE_HELP;
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
        fprintf(stderr, "Invalid options, use: %s [-s|-r|-o|-h] -input <input_file> [-output <output_file>ЫЫЫЫЫЫЫЫ\n", argv[0]);
        return MODE_ERROR;
    }

    return mode;
}