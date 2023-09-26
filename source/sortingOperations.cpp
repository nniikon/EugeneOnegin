#include "..\include\sortingOperations.h"

// Copypasted^{tm}
int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return  1;
    return 0;
}


int compareReversedLines(const char* str1, size_t len1, const char* str2, size_t len2)
{
    const char* cStr1 = (const char*)str1;
    const char* cStr2 = (const char*)str2;

    int index1 = len1;
    int index2 = len2;

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
        if(tolower(cStr2[index2]) - tolower(cStr1[index1]) > 0)
        {
            return -1;
        }
        else if (tolower(cStr2[index2]) - tolower(cStr1[index1]) < 0)
        {
            return 1;
        }
    } while (isLetter1 && isLetter2);

    return 0;
}


int compareLinePointersToStrings(const void* pline1, const void* pline2) 
{
    const line* line1 = (const line*)pline1;
    const line* line2 = (const line*)pline2;

    return compareLines(line1->str, line2->str);
}


int compareLinePointersToReversedStrings(const void* pline1, const void* pline2) 
{
    const line* line1 = (const line*)pline1;
    const line* line2 = (const line*)pline2;

    return compareReversedLines(line1->str, line1->len, line2->str, line2->len);
}


int compareLines(const char* str1, const char* str2)
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

    size_t currentSize = elemSize;
    while(currentSize >= sizeof(__int64))
    {
        // printf("1current size = %d\n", currentSize);
        __int64 ltemp = *((__int64*)str1);
        *((__int64*)str1) = *((__int64*)str2);
        *((__int64*)str2) = ltemp;
        currentSize -= sizeof(__int64);
        
        if (currentSize == 0)
            return;

        str1 = (void*)((size_t)str1 + sizeof(__int64));
        str2 = (void*)((size_t)str2 + sizeof(__int64));
    } 
    
    char* char1 = (char*)str1;
    char* char2 = (char*)str2;

    for (size_t j = 0; j < currentSize; j++)
    {
        char ctemp = char1[j];
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
            void* element1 = (void*)((size_t)arr +  j      * elemSize);
            void* element2 = (void*)((size_t)arr + (j + 1) * elemSize);

            if (compare(element1, element2) > 0)
            {
                swap(element1, element2, elemSize);
            }
        }
        unsortedSize--;
    }
}


static size_t partition(void* arr, int low, int high, size_t elemSize, 
                        int (*compare)(const void*, const void*))
{
    //printf("\t\tpartition:\n");
    
    int pivoIndex = high;
    while (low < high)
    {
        //printf("\tlow = %d, high = %d\n", low, high);
     
        while (compare((void*)((size_t)arr + low * elemSize), 
                       (void*)((size_t)arr + pivoIndex * elemSize)) < 0
                        && low < high)
        {
            low++;
        }

        while (compare((void*)((size_t)arr + high * elemSize), 
                       (void*)((size_t)arr + pivoIndex * elemSize)) >= 0 
                        && low < high)
        {
            high--;
        }

        swap((void*)((size_t)arr + low  * elemSize), 
             (void*)((size_t)arr + high * elemSize), elemSize);
    }
    
    swap((void*)((size_t)arr + low       * elemSize), 
         (void*)((size_t)arr + pivoIndex * elemSize), elemSize);
    return low;
}

static void qsortRecursion(void* arr, int low, int high, size_t elemSize, 
                           int (*compare)(const void*, const void*))
{
    if (high - low < 4)
        return bubbleSort(arr, (size_t)(high-low+1), elemSize, compare);
    if (low < high && high > 0)
    {
        int pivoIndex = partition(arr, low, high, elemSize, compare);
    
        qsortRecursion(arr, low          , pivoIndex - 1, elemSize, compare);
        qsortRecursion(arr, pivoIndex + 1, high         , elemSize, compare);
    }
}

void my_qsort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*))
{
    qsortRecursion(arr, 0, arrSize - 1, elemSize, compare);
}

