#include "..\include\stringOperations.h"
#include "..\include\sortingOperations.h"
#include "..\include\test.h"


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


static Mode parseArguments(int argc, char** argv, char** inFile, const char** outFile,
                           void (**sort)(void*, size_t, size_t, int (*)(const void*, const void*)));
static void help();
static void runTests();


int main(int argc, char** argv)
{
    char*        inputFile_name = NULL;
    const char* outputFIle_name = NULL;
    Error error = NO_ERROR;
    void (*sort)(void*, size_t, size_t, int (*)(const void*, const void*)) = my_qsort;

    Mode mode = parseArguments(argc, argv, &inputFile_name, &outputFIle_name, &sort);

    if (mode == MODE_ERROR)
        return INVALID_ARGS;

    if (mode == MODE_TEST)
    {
        runTests();
        return NO_ERROR;
    }

    if (mode == MODE_HELP)
    {
        help();
        return NO_ERROR;
    }

    // MEM_WARNING: outputFile was opened.
    FILE* outputFile = fopen(outputFIle_name, "w");
    if (outputFile == NULL)
    {
        perror("Error opening file");
        return FILE_OPEN_ERROR;
    }

    char* buffer = NULL;
    // MEM_WARNING: buffer was allocated.
    error = fileToNormilizedBuffer(inputFile_name, &buffer);
    if (error != NO_ERROR)
        return error;

    size_t nLines = 0;
    line* txt = NULL;
    // MEM_WARNING: txt was allocated.
    // Parse the buffer into the lines using \n as a delimiter.
    error = parseBufferToLines(&txt, buffer, &nLines, '\n');
    if (error != NO_ERROR)
    {
        free(txt);
        free(buffer);
        return error;
    }

    // Decide what to do with the buffer based on the mode.
    switch (mode)
    {
        case MODE_ORIGINAL:
            fputs(buffer, outputFile);
            break;
        case MODE_STRAIGHT_SORT:
            sort((void*)(txt), nLines, sizeof(line), compareLinePointersToStrings);
            printTextToFile(txt, outputFile);
            break;
        case MODE_REVERSED_SORT:
            sort((void*)(txt), nLines, sizeof(line), compareLinePointersToReversedStrings);
            printTextToFile(txt, outputFile);
            break;
        case MODE_ERROR:
        case MODE_TEST:
        case MODE_HELP:
        default:
            free(txt);
            free(buffer);
            return UNEXPECTED_ERROR;
    }

    free(txt);
    free(buffer);
    return error;
}





// Parse command line arguments.
static Mode parseArguments(int argc, char** argv, char** inFile, const char** outFile,
                           void (**sort)(void*, size_t, size_t, int (*)(const void*, const void*)))
{
    Mode mode = MODE_ORIGINAL; // Original   by default.
    *sort = my_qsort;          // Quick sort by default.

    const char invalidOptionErrorText[] = 
    "Invalid options or missing argument, use: %s [-s|-r|-o] [-qsort|-bubble] [-h|-t] -input <input_file> [-output] <output_file>\n";

    *inFile = NULL;
    const char* defaultOuputName = "output.txt";
    *outFile = defaultOuputName;

    if (argc < 2) 
    {
        fprintf(stderr, invalidOptionErrorText, argv[0]);
        return MODE_ERROR;
    }

    for (int i = 1; i < argc; i++) 
    {
        if      (strcmp(argv[i], "-s") == 0)    mode = MODE_STRAIGHT_SORT; 
        else if (strcmp(argv[i], "-r") == 0)    mode = MODE_REVERSED_SORT; 
        else if (strcmp(argv[i], "-o") == 0)    mode = MODE_ORIGINAL; 
        else if (strcmp(argv[i], "-t") == 0)    return MODE_TEST;
        else if (strcmp(argv[i], "-h") == 0)    return MODE_HELP;
        else if (strcmp(argv[i], "-qsort")  == 0)    *sort = my_qsort;
        else if (strcmp(argv[i], "-bubble") == 0)    *sort = bubbleSort;
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
            fprintf(stderr, invalidOptionErrorText, argv[0]);
            return MODE_ERROR;
        }
    }
    if (*inFile == NULL || mode == MODE_ERROR)
    {
        fprintf(stderr, invalidOptionErrorText, argv[0]);
        return MODE_ERROR;
    }

    // fprintf(stderr, "output: %s\n", *outFile);
    // fprintf(stderr, "infile: %s\n", *inFile);

    return mode;
}


static void help()
{
    printf("-s      Standart sorting.                     \n"
           "-r      Sorting of the reversed lines.        \n"
           "-o      No sorting (by default).              \n"
           "-h      Prints this message.                  \n"
           "-t      Run tests.                            \n"
           "-qsort  Use quick sort algorithm (by default) \n"
           "-bubble Use bubble sort algorithm             \n");
}


static void runTests()
{
    testCompareString();
    testSorting(qsort, compare_ints);
}
