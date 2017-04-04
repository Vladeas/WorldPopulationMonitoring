#pragma once

typedef struct
{
	char* name;
	char* continent;
	long population;
}Country;

//This function creates the domain of elements
Country* createCountry(char* name, char* continent, long population);

//This function destroy the domain
void destroyCountry(Country* m);

//This function returns the Name of the country
char* getName(Country* m);
//This function returns the Continent on which the country is
char* getContinent(Country* m);
//This function returns the Population of the country
long getPopulation(Country* m);

//This function prints the elements of the array
void toString(Country* m, char str[]);

Country* copyCountry(Country* m);