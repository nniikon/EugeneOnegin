#include "..\include\stringOperations.h"
#include "..\include\test.h"

static const char* FILE_NAME = "EugeneOnegin.txt";

//#define TEST


static void swap(void* str1, void* str2, const size_t elemSize)
{
    void* temp = malloc(elemSize);
    assert(temp);

    memcpy(temp, str1, elemSize);
    memcpy(str1, str2, elemSize);
    memcpy(str2, temp, elemSize);
}


static void bubbleSort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*))
{
    size_t unsortedSize = arrSize;
    for (size_t i = 0; i < arrSize; i++)
    {
        for (size_t j = 0; j < unsortedSize - 1; j++)
        {
            printf("\tBUBBLE_SORT: compare(%d, %d)\n", ((size_t)arr + j*elemSize), 
                                                     ((size_t)arr + (j+1)*elemSize));
            if (compare((void*)((size_t)arr + j*elemSize), 
                        (void*)((size_t)arr + (j+1)*elemSize)) == 1)
            {
                swap((void*)((size_t)arr + j*elemSize), 
                     (void*)((size_t)arr + (j+1)*elemSize), elemSize);
            }
        }
        unsortedSize--;
    }
}

int main()
{
    #ifdef TEST
    testCompareString();
    #else

    off_t size = getFileSize(FILE_NAME);
    char* buffer = FileToBuffer(size, FILE_NAME);
    

    // Replace different EOL symbols on '\n'.
    replaceCharacter          (buffer, '\r', '\n');
    deleteRepetitiveCharacters(buffer, '\n');
    size_t nLines = 0;

    // Parse the buffer into the lines using \n as a delimiter.
    char** text = parseBufferToLines(buffer, &nLines, '\n');

    // buffer: <aaa \n bbb \n ccc \n asdasd \0 >

    text[nLines] = NULL;
    

    for (int i = 0; text[i] != '\0'; i++)
    {
        printLine(text[i], '\n');
    }

    puts("\nSorting\n");
    bubbleSort((void*)(text), nLines, sizeof(char*), compareLines);

    for (int i = 0; text[i]; i++)
    {
        printf("%u, text[%.2d] = ", size_t(text + i), i);
        printLine(text[i], '\n');
    }

    free(text);
    free(buffer);
    #endif
    
}