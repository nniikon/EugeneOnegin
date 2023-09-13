#include "..\include\test.h"

static void testSingleCompareString(const char* str1, const char* str2, int expectedValue)
{
    int cmp = compareLines(str1, str2);
    if (cmp == expectedValue)
        printf("TEST PASSED\n");
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