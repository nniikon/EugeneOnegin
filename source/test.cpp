#include "..\include\test.h"

static void testSingleCompareString(const char* str1, const char* str2, int expectedValue)
{
    int cmp = compareLines(str1, str2);
    if (cmp == expectedValue)
        printf("%50s", "COMPARE STRING TEST PASSED\n");
    else
    {
        printf("TEST FAILED!!!\nSTR1 = <%s> \nSTR2 = <%s> \nresult: %d \nExpected: %d \n", 
                                       str1,         str2,          cmp,           expectedValue);
    }
}

void testCompareString()
{
    const int maxStrLength = 100;
    char str1[maxStrLength] = "ABCDEFG";
    char str2[maxStrLength] = "AAAAAAA";
    testSingleCompareString(str1, str2, 1);


    strncpy(str1, "ABCDEF", maxStrLength);
    strncpy(str2, "ABCDEF", maxStrLength);
    testSingleCompareString(str1, str2, 0);
    

    strncpy(str1, "As real expert does by chance. He could be silent in discussion", maxStrLength);
    strncpy(str2, "It was the art of tender passion, By Nazon brightly glorified.",  maxStrLength);
    testSingleCompareString(str1, str2, -1);

    strncpy(str1, "Insurgent youth is not yet endless. When Eugene was to change his sort", maxStrLength);
    strncpy(str2, "A pedant but of science man. He had a happy talent then:",               maxStrLength);
    testSingleCompareString(str1, str2, 1);

    strncpy(str1, "aaaaaaaa", maxStrLength);
    strncpy(str2, "bbbbbbbb", maxStrLength);
    testSingleCompareString(str1, str2, -1);
    
}


void testSorting(void (*sort)(void*, size_t, size_t, int (*cmp)(const void*, const void*)),
                                                     int (*cmp)(const void*, const void*))
{
    srand(time(NULL));
    const int arrSize = 15;
    int qSortArr[arrSize];
    int  sortArr[arrSize];
    for (int i = 0; i < arrSize; i++)
    {
        qSortArr[i] = rand() % 100;
        sortArr[i] = qSortArr[i];
    }
    qsort((void*)qSortArr, arrSize, sizeof(int), cmp);
    sort ((void*) sortArr, arrSize, sizeof(int), cmp);

    for (int i = 0; i < arrSize; i++)
    {
        if (qSortArr[i] != sortArr[i])
        {
            printf("SORTING TEST FAILED!!!\n");
            for (int j = 0; j < arrSize; j++)
            {
                printf("qsort: %d, sort: %d\n", qSortArr[j], sortArr[j]);
            }
            return;
        }
        
    }
    
    printf("%50s", "SORTING TEST PASSED\n");
    
}