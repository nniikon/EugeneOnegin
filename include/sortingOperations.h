#ifndef SORTING_OPERATIONS_H
#define SORTING_OPERATIONS_H

#include <assert.h>
#include <string.h>
#include "..\include\stringOperations.h"

int compare_ints(const void* a, const void* b); // For testing purposes.

// https://en.cppreference.com/w/c/algorithm/qsort
void my_qsort(void* arr, size_t arrSize, size_t elemSize, int (*compare)(const void*, const void*));

/**
 * @brief Sorts an array based on the given comparison function using the bubble sorting algorithm.
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
int compareLines(const char* str1, const char* str2);


/**
 * @brief Compares two reversed lines for alphabetical order.
 *
 * @param str1 First  string.
 * @param str2 Second string.
 *
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal.
 */
int compareReversedLines(const char* str1, size_t len1, const char* str2, size_t len2);


/**
 * @brief Compares two line* pointers for alphabetical order.
 *
 * @param pstr1 First  pointer.
 * @param pstr2 Second pointer.
 *
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal.
 */
int compareLinePointersToLines(const void* pline1, const void* pline2);

/**
 * @brief Compares two line* pointers for alphabetical order in reversed lines.
 *
 * @param pstr1 First  pointer.
 * @param pstr2 Second pointer.
 *
 * @return `-1` if in alphabetical order, `1` if not in alphabetical order, `0` if equal.
 */
int compareLinePointersToReversedLines(const void* pline1, const void* pline2);

#endif