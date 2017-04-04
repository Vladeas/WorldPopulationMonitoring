#pragma once
#include "Country.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* countries;
}CountryRepo;


CountryRepo* createRepo();
void destroyRepo(CountryRepo* repo);


int add(CountryRepo* repo, Country* mi);

int find(CountryRepo* repo, char* name);

Country* getCountryOnPos(CountryRepo* repo, int pos);

void deletei(CountryRepo* repo, int poz);

void update(CountryRepo* repo, char* continent, long population, int poz);

void setrepo(CountryRepo* repo, CountryRepo* newrepo);

Country* sort(CountryRepo* res);

Country* sortN(CountryRepo* reponew);


