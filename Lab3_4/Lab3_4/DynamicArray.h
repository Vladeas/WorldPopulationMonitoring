#pragma once
#include "Country.h"
#define CAPACITY 10

typedef Country* TElement;

typedef struct
{
	TElement* elemns;
	int lenght;
	int capacity;

}DynamicArray;


DynamicArray* createDynamicArray(int capacity);
void destroy(DynamicArray* arr);

int getlenghtA(DynamicArray* arr);
TElement get(DynamicArray* arr, int pos);

void addD(DynamicArray* arr, TElement t);
void deleteD(DynamicArray* arr, int pos);
