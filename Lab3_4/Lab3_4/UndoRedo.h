#pragma once
#include "Country.h"
#include "DynamicArray.h"
#include <string.h>

typedef struct
{
	Country* country;
	char* opType;

}Operation;

//Creates a new operation which contains the country obj and the type of that operation
Operation* createOperation(Country* c, char* opType);

//Destroy the object operation
void destroyOperation(Operation* o);

//Make a copy of the current operation 
Operation* copyOperation(Operation* o);

//Returns the type of the operation
char* getOpType(Operation* o);

//Returns the corresponding country of the operation
Country* getcountries(Operation* o);


typedef struct
{
	Operation* op[100];
	int length;
}OperationStack;

//Creates the stack for undo
OperationStack* createStack();

//Destroy the object undo
void destroyStack(OperationStack* s);

//This function push in the list the current operation
void push(OperationStack* s, Operation* o);

//This function pops from the list the current operation
Operation* pop(OperationStack* s);

//This function verify if the list is empty
int isEmpty(OperationStack* s);

//This function verify if the list is full
int isFull(OperationStack* s);

typedef struct
{
	Operation* redo[100];
	int lengthr;
}OperationRedo;

//Creates the stack for redo
OperationRedo* createRedo();

//Destroy the object redo
void destroyRedo(OperationRedo* r);

//This function push in the list the current operation
void pushRedo(OperationRedo* r, Operation* o);

//This function pops from the list the current operation
OperationRedo* popRedo(OperationRedo* r);

//This function verify if the list is empty
int isEmptyRedo(OperationRedo* r);

//This function verify if the list is full
int isFullRedo(OperationRedo* r);

