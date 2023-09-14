#include "..\include\sortingOperations.h"

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return  1;
    return 0;
}


int comparePointersToReversedLines(const void* pstr1, const void* pstr2)
{
    return compareReversedLines(*(const char**)pstr1, *(const char**)pstr2);
}

int compareReversedLines(const void* str1, const void* str2)
{
    const int MAX_LINE_SIZE = 512;

    char strdup1[MAX_LINE_SIZE] = "";
    char strdup2[MAX_LINE_SIZE] = "";

    strncpy(strdup1, ((const char*)str1), MAX_LINE_SIZE);
    strncpy(strdup2, ((const char*)str2), MAX_LINE_SIZE);

    deleteNonLetterCharacters(strdup1, '\n');
    deleteNonLetterCharacters(strdup2, '\n');

    int str1_len = int(my_strlen(strdup1, '\n')) - 1; 
    int str2_len = int(my_strlen(strdup2, '\n')) - 1; 

    // printf("\t\t I'm comparing:\nstr1 = ");
    // printLine(strdup1, '\n');
    // printf("\t size = %d\n", str1_len);
    // printf("str2 = ");
    // printLine(strdup2, '\n');
    // printf("\t size = %d\n", str2_len);

    while (str1_len > 0 && str2_len > 0)
    {
        //printf("%c vs %c\n", strdup1[str1_len], strdup2[str2_len]);
        if      (int(strdup1[str1_len]) < int(strdup2[str2_len])) return -1;
        else if (int(strdup1[str1_len]) > int(strdup2[str2_len])) return  1; 
        str1_len--;
        str2_len--;
    }

    // If strdup1 and strdup2 are the same length.
    if (str1_len == 0 && str2_len == 0)
    {
        return 0;
    }
    // If strdup1 is shorter...
    if (str1_len == 0) 
        return 1;
    else
        return -1;

    assert(0);
    return(-10);
}

int comparePointersToLines(const void* pstr1, const void* pstr2)
{
    return compareLines(*(const char**)pstr1, *(const char**)pstr2);
}

int compareLines(const void* str1, const void* str2)
{
    const int MAX_LINE_SIZE = 512;

    char strdup1[MAX_LINE_SIZE] = "";
    char strdup2[MAX_LINE_SIZE] = "";

    strncpy(strdup1, ((const char*)str1), MAX_LINE_SIZE);
    strncpy(strdup2, ((const char*)str2), MAX_LINE_SIZE);

    deleteNonLetterCharacters(strdup1, '\n');
    deleteNonLetterCharacters(strdup2, '\n');

    int i = 0;
    for (i = 0; strdup1[i] != '\n'  && strdup2[i] != '\n' && strdup1[i] && strdup2[i]; i++)
    {
        // Ignore register to compare strings 
        strdup1[i] = (char)tolower(strdup1[i]);
        strdup2[i] = (char)tolower(strdup2[i]);

        if      (int(strdup1[i]) < int(strdup2[i])) return -1;
        else if (int(strdup1[i]) > int(strdup2[i])) return  1;
    }
    // If strdup1 and strdup2 are the same length.
    if ((strdup1[i] == '\0' || strdup1[i] == '\n') && (strdup2[i] == '\0' || strdup2[i] == '\n'))
    {
        return 0;
    }
    // If strdup1 is shorter...
    else if (strdup1[i] == '\0' || strdup1[i] == '\n')
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

static void swap(void* str1, void* str2, const size_t elemSize)
{
    void* temp = malloc(elemSize);
    assert(temp);

    memcpy(temp, str1, elemSize);
    memcpy(str1, str2, elemSize);
    memcpy(str2, temp, elemSize);
}

void bubbleSort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*))
{
    size_t unsortedSize = arrSize;
    for (size_t i = 0; i < arrSize; i++)
    {
        for (size_t j = 0; j < unsortedSize - 1; j++)
        {
            //printf("\tBUBBLE_SORT: compare(%d, %d)\n", ((size_t)arr +   j  *elemSize), 
            //                                           ((size_t)arr + (j+1)*elemSize));
            if (compare((void*)((size_t)arr + j    *elemSize), 
                        (void*)((size_t)arr + (j+1)*elemSize)) == 1)
            {
                swap((void*)((size_t)arr + j    *elemSize), 
                     (void*)((size_t)arr + (j+1)*elemSize), elemSize);
            }
        }
        unsortedSize--;
    }
}