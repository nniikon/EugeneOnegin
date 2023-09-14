#pragma once

#include "..\include\stringOperations.h"
#include <string.h>
#include <assert.h>

int compare_ints(const void* a, const void* b);

/**
 * @brief Sorts an array based on the given comparison function.
 * 
 * @param arr      The array to be sorted.
 * @param arrSize  The number of elements in the given array.
 * @param elemSize The size of each element.
 * @param compare  The function to compare elements.
 */
void bubbleSort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*));

/**
 * @brief Compares two lines for alphabetical order.
 * 
 * @param str1 First  string.
 * @param str2 Second string.
 * 
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal. 
 */
int compareLines(const void* str1, const void* str2);


/**
 * @brief Compares two reversed lines for alphabetical order.
 * 
 * @param str1 First  string.
 * @param str2 Second string.
 * 
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal. 
 */
int compareReversedLines(const void* str1, const void* str2);



/**
 * @brief Compares two char** pointers for alphabetical order.
 * 
 * @param pstr1 First  pointer.
 * @param pstr2 Second pointer.
 * 
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal. 
 */
int comparePointersToLines(const void* pstr1, const void* pstr2);

/**
 * @brief Compares two char** pointers for alphabetical order in reversed lines.
 * 
 * @param pstr1 First  pointer.
 * @param pstr2 Second pointer.
 * 
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal. 
 */
int comparePointersToReversedLines(const void* pstr1, const void* pstr2);
