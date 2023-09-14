#pragma once
#include <random>
#include <ctime>
#include "..\include\stringOperations.h"

void testCompareString();

void testSorting(void (*sort)(void*, size_t, size_t, int (*cmp)(const void*, const void*)),
                                                     int (*cmp)(const void*, const void*));