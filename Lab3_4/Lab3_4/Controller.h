#pragma once
#include "Repository.h"
#include "UndoRedo.h"

typedef struct
{
	CountryRepo* repo;
	OperationStack* undoStack;
	OperationRedo* redoStack;
}Controller;

Controller* createController(CountryRepo* repo, OperationStack* undoStack, OperationRedo* redoStack);
void destroyController(Controller* cont);

int AddCountry(Controller* cont, char* name, char* continent, long population, int c);

CountryRepo* getrepo(Controller* cont);

CountryRepo* listcountrybystring(Controller* cont, char symbol[]);

int deleteitem(Controller* cont, char name[], int d);

int updatecont(Controller* cont, char name[], char* continent, long population, int k);

CountryRepo* searchCont(Controller* cont, char continent[]);

CountryRepo* filterCont(Controller* cont, long population);

int undo(Controller* cont);

int redo(Controller* cont);

int updateMigCont(Controller* cont, char* name1, char* name2, long population);