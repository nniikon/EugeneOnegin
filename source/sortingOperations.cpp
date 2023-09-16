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
    return compareReversedLines(*(const char* const*)pstr1, *(const char* const*)pstr2);
}

int compareReversedLines(const void* str1, const void* str2)
{
    const char* cStr1 = (const char*)str1;
    const char* cStr2 = (const char*)str2;

    int index1 = my_strlen(cStr1, '\n');
    int index2 = my_strlen(cStr2, '\n');

    bool isLetter1 = false;
    bool isLetter2 = false;
    do
    {
        isLetter1 = false;
        isLetter2 = false;

        // Iterate to the letter.
        while (!isLetter1)
        {
            index1--;
            if(index1 < 0)
            {
                isLetter1 = false;
                break;
            }
            isLetter1 = isalpha(cStr1[index1]);
        }

        // Iterate to the letter.
        while (!isLetter2)
        {
            index2--;
            if(index2 < 0)
            {
                isLetter2 = false;
                break;
            }
            isLetter2 = isalpha(cStr2[index2]);
        }

        // Compare the letters ignoring the register.
        if(int(tolower(cStr2[index2])) - int(tolower(cStr1[index1])) > 0)
        {
            return -1;
        }
        else if (int(tolower(cStr2[index2])) - int(tolower(cStr1[index1])) < 0)
        {
            return 1;
        }
    } while (isLetter1 && isLetter2);

    return 0;
}

int comparePointersToLines(const void* pstr1, const void* pstr2)
{
    return compareLines(*(const char* const*)pstr1, *(const char* const*)pstr2);
}

int compareLinePointersToLines(const void* pline1, const void* pline2) {
    const line* line1 = (const line*)pline1;
    const line* line2 = (const line*)pline2;

    return compareLines(line1->str, line2->str);
}
int compareLinePointersToReversedLines(const void* pline1, const void* pline2) {
    const line* line1 = (const line*)pline1;
    const line* line2 = (const line*)pline2;

    return compareReversedLines(line1->str, line2->str);
}
int compareLines(const void* str1, const void* str2)
{
    const char* cStr1 = (const char*)str1; 
    const char* cStr2 = (const char*)str2; 

    int index1 = -1;
    int index2 = -1;

    bool isLetter1 = false;
    bool isLetter2 = false;
    do
    {
        isLetter1 = false;
        isLetter2 = false;

        // Iterate to the letter.
        while (!isLetter1)
        {
            index1++;
            if(cStr1[index1] == '\0' || cStr1[index1] == '\n')
            {
                isLetter1 = false;
                break;
            }
            isLetter1 = isalpha(cStr1[index1]);
        }

        // Iterate to the letter.
        while (!isLetter2)
        {
            index2++;
            if(cStr2[index2] == '\0' || cStr2[index2] == '\n')
            {
                isLetter2 = false;
                break;
            }
            isLetter2 = isalpha(cStr2[index2]);
        }

        // Compare the letters ignoring the register.
        if(int(tolower(cStr2[index2])) - int(tolower(cStr1[index1])) > 0)
        {
            return -1;
        }
        else if (int(tolower(cStr2[index2])) - int(tolower(cStr1[index1])) < 0)
        {
            return 1;
        }
    } while (isLetter1 && isLetter2);

    return 0;
}

static void swap(void* str1, void* str2, const size_t elemSize)
{
    assert(str1 != NULL && str2 != NULL);
    size_t i = 0;

    long* long1 = (long*)str1; 
    long* long2 = (long*)str2; 
    long temp = 0l;

    for (i = 0; i < elemSize / sizeof(long); i++)
    {
        memcpy(&temp, long1, sizeof(long));
        memcpy(long1, long2, sizeof(long)); // FIX
        memcpy(long2, &temp, sizeof(long));
    }

    char* char1 = (char*)str1;
    char* char2 = (char*)str2;
    char ctemp = '0';

    for (size_t j = 0; j < elemSize - i * sizeof(long); j++)
    {
        ctemp = char1[j];
        char1[j] = char2[j];
        char2[j] = ctemp;
    }
    
     
}

void bubbleSort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*))
{
    size_t unsortedSize = arrSize;
    for (size_t i = 0; i < arrSize; i++)
    {
        for (size_t j = 0; j < unsortedSize - 1; j++)
        {
            void* element1 = (void*)((size_t*)arr + j * elemSize);
            void* element2 = (void*)((size_t*)arr + (j + 1) * elemSize);

            if (compare(element1, element2) > 0)
            {
                swap(element1, element2, elemSize);
            }
        }
        unsortedSize--;
    }
}

void convQuickSort(int* arr, int low, int high, int (*compare)(const void*, const void*))
{
    int piv = (high - low) / 2;
    while (low < high)
    {
        printf("low = %u \nhigh = %u \n", low, high);

        while (arr[low]  < arr[piv])  low++;
        while (arr[high] > arr[piv]) high--;

        swap((void*)(arr + low), (void*)(arr + high), sizeof(int));
    }
}


void quickSort(int* arr, size_t arrSize, int (*compare)(const void*, const void*))
{
    if(arrSize < 4)
    {
        bubbleSort((void*)arr, arrSize, sizeof(int), compare);
        return;
    }
    int low  = 0;
    int high = int(arrSize) - 1;

    printf("\t\tQSORT: \nlow = %u \nhigh = %u \npiv = %u \n", low, high);
    return convQuickSort(arr, low, high, compare);
}