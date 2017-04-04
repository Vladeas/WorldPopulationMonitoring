#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include "Repository.h"
#include "Ui.h"
#include "UndoRedo.h"
#include <Windows.h>




int main()
{
	TestCountry();

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CountryRepo* repo = createRepo();
	OperationStack* opStack = createStack();
	OperationRedo* opRedo = createRedo();
	Controller* cont = createController(repo, opStack, opRedo);


	AddCountry(cont, "Grece", "Europe", 4000000, 0);
	AddCountry(cont, "Romania", "Europe", 18000000, 0);
	AddCountry(cont, "Chile", "America", 98056161, 0);
	AddCountry(cont, "Canada", "America", 24654641, 0);
	AddCountry(cont, "Panama", "America", 1565794, 0);
	AddCountry(cont, "Japan", "Asia", 1450484430, 0);
	AddCountry(cont, "India", "Asia", 106984743, 0);
	AddCountry(cont, "Germany", "Europe", 67054675, 0);
	AddCountry(cont, "France", "Europe", 57994400, 0);
	AddCountry(cont, "Hungary", "Europe", 120078567, 0);

	UI* ui = CreateUI(cont);

	SUI(ui);
	DestroyUI(ui);


	_CrtDumpMemoryLeaks();
	return 0;
}