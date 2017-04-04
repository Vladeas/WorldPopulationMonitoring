#include "Country.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Country* createCountry(char* name, char* continent, long population)
{
	Country* m = (Country*)malloc(sizeof(Country));
	m->name = (char*)malloc(strlen(name) + 1);
	strcpy(m->name, name);
	m->continent = (char*)malloc(strlen(continent) + 1);
	strcpy(m->continent, continent);
	m->population = population;

	return m;
}

void destroyCountry(Country* m)
{
	free(m->name);
	free(m->continent);

	free(m);
}

char* getName(Country *m)
{
	return m->name;
}

char* getContinent(Country* m)
{
	return m->continent;
}

long getPopulation(Country * m)
{
	return m->population;
}

void toString(Country * m, char str[])
{
	sprintf(str, "		Continent :  %s || Country :  %s || Population :  %d", m->continent, m->name, m->population);
}

Country * copyCountry(Country * m)
{
	if (m == NULL)
		return NULL;
	Country* newcountry = createCountry(m->name, m->continent, m->population);
	return newcountry;
}



