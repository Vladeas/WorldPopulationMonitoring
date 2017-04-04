#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include "Repository.h"
#include "Ui.h"
#include <Windows.h>
#include "Test.h"
#include <assert.h>


void TestCountry()
{
	//Creates the Controller and Repository
	CountryRepo* repot = createRepo();
	OperationStack* opStack = createStack();
	OperationRedo* opRedo = createRedo();
	Controller* contt = createController(repot, opStack, opRedo);


	//Adds some elements to be tested
	AddCountry(contt, "Moldova", "Europe", 4000000, 0);
	AddCountry(contt, "Romania", "Europe", 18000000, 0);
	AddCountry(contt, "Mexic", "AmericaN", 98056161, 0);
	AddCountry(contt, "Canada", "AmericaN", 24654641, 0);


	//ADD tests
	assert(getlenghtA(repot->countries) == 4);
	assert(AddCountry(contt, "Albania", "Europe", 1560, 0) == 1);
	assert(getlenghtA(repot->countries) == 5);
	assert(AddCountry(contt, "Albania", "Europe", 1560, 0) == 0);
	assert(getlenghtA(repot->countries) == 5);
	assert(AddCountry(contt, "Albuz", "Europe", 15600, 0) == 1);
	assert(getlenghtA(repot->countries) == 6);


	//DELETE tests
	assert(deleteitem(contt, "Albania", 0) == 1);
	assert(getlenghtA(repot->countries) == 5);
	assert(deleteitem(contt, "Albania", 0) == 0);
	assert(getlenghtA(repot->countries) == 5);
	assert(deleteitem(contt, "Albanfghfhia", 0) == 0);
	assert(getlenghtA(repot->countries) == 5);
	assert(deleteitem(contt, "Canada", 0) == 1);
	assert(getlenghtA(repot->countries) == 4);


	//UPDATE tests
	assert(updatecont(contt, "Franta", "TTTT", 5789, 0) == 0);
	assert(updatecont(contt, "Moldova", "TTTT", 5789, 0) == 1);
	assert(updatecont(contt, "dfhfghghf", "TTTT", 5789, 0) == 0);


	//SEARCH tests
	CountryRepo* repo2 = searchCont(contt, "Europe");
	assert(repo2->countries->lenght == 2);
	destroyRepo(repo2);
	CountryRepo* repo3 = searchCont(contt, "Eurtope");
	assert(repo3->countries->lenght == 0);
	destroyRepo(repo3);
	CountryRepo* repo4 = searchCont(contt, "Null");
	assert(repo4->countries->lenght == 4);
	destroyRepo(repo4);


	//FILTER tests
	CountryRepo* repo5 = filterCont(contt, 1000000);
	assert(repo5->countries->lenght == 2);
	destroyRepo(repo5);
	CountryRepo* repo6 = filterCont(contt, 100);
	assert(repo6->countries->lenght == 4);
	destroyRepo(repo6);
	CountryRepo* repo7 = filterCont(contt, 999999999);
	assert(repo7->countries->lenght == 0);
	destroyRepo(repo7);


	//Destroy the Controller and Repository
	destroyController(contt);
}
