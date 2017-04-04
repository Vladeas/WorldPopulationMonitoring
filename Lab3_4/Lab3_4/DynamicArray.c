#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->lenght = 0;
	da->elemns = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elemns == NULL)
		return NULL;
	return da;
}


void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	free(arr->elemns);
	arr->elemns = NULL;

	free(arr);
	arr = NULL;
}

int getlenghtA(DynamicArray * arr)
{
	if (arr == NULL)
		return -1;

	return arr->lenght;
}

TElement get(DynamicArray * arr, int pos)
{
	return arr->elemns[pos];
}

void resize(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	arr->capacity *= 2;
	arr->elemns = (TElement*)realloc(arr->elemns, arr->capacity * sizeof(TElement));
}

void addD(DynamicArray * arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elemns == NULL)
		return;
	if (arr->lenght == arr->capacity)
		resize(arr);
	arr->elemns[arr->lenght++] = t;
}

void deleteD(DynamicArray * arr, int pos)
{
	if (arr == NULL)
		return;
	if (arr->elemns == NULL)
		return;
	for (int i = pos; i < arr->lenght - 1; i++)
		arr->elemns[i] = arr->elemns[i + 1];
	arr->lenght--;
}
