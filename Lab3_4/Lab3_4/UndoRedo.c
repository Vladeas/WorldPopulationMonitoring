#include "UndoRedo.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Operation * createOperation(Country * c, char * opType)
{
	Operation* o = (Operation*)malloc(sizeof(Operation));
	o->country = copyCountry(c);
	if (opType != NULL)
	{
		o->opType = (char*)malloc(strlen(opType) + 1);
		strcpy(o->opType, opType);
	}
	else
		o->opType = NULL;

	return o;
}

void destroyOperation(Operation * o)
{
	if (o == NULL)
		return;

	destroyCountry(o->country);
	free(o->opType);
	free(o);

}

Operation * copyOperation(Operation * o)
{
	if (o == NULL)
		return NULL;

	Operation* newOp = createOperation(o->country, o->opType);
	return newOp;
}

char * getOpType(Operation * o)
{
	return o->opType;
}

Country * getcountries(Operation * o)
{
	return o->country;
}

//----------------------------------------------------------------

OperationStack * createStack()
{
	OperationStack* s = (OperationStack*)malloc(sizeof(OperationStack));
	s->length = 0;

	return s;
}


void destroyStack(OperationStack * s)
{
	if (s == NULL)
		return;

	for (int i = 0; i < s->length; i++)
		destroyOperation(s->op[i]);
	free(s);
}

void push(OperationStack * s, Operation * o)
{
	if (isFull(s))
		return;
	s->op[s->length++] = copyOperation(o);
}

Operation * pop(OperationStack * s)
{
	if (isEmpty(s))
		return NULL;
	s->length--;
	return s->op[s->length];
}

int isEmpty(OperationStack * s)
{
	return (s->length == 0);
}

int isFull(OperationStack * s)
{
	return (s->length == 100);
}

//--------------------------------------------------------

OperationRedo * createRedo()
{
	OperationRedo* r = (OperationRedo*)malloc(sizeof(OperationRedo));
	r->lengthr = 0;
	return r;
}

void destroyRedo(OperationRedo * r)
{
	if (r == NULL)
		return;

	for (int i = 0; i < r->lengthr; i++)
		destroyOperation(r->redo[i]);
	free(r);
}

void pushRedo(OperationRedo * r, Operation * o)
{
	if (isFullRedo(r))
		return;
	r->redo[r->lengthr++] = copyOperation(o);
}

OperationRedo * popRedo(OperationRedo * r)
{
	if (isEmptyRedo(r))
		return NULL;
	r->lengthr--;
	return r->redo[r->lengthr];
}

int isEmptyRedo(OperationRedo * r)
{
	return (r->lengthr == 0);
}

int isFullRedo(OperationRedo * r)
{
	return (r->lengthr == 100);
}
