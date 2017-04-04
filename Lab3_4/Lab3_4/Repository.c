#include "Repository.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


CountryRepo* createRepo()
{
	//This funtion creates the repository
	CountryRepo* repo = (CountryRepo*)malloc(sizeof(CountryRepo));
	repo->countries = createDynamicArray(CAPACITY);

	return repo;
}


void destroyRepo(CountryRepo* repo)
{
	//This function destroy the repo after the promgram is stoped
	for (int i = 0; i < getlenghtA(repo->countries); i++)
	{
		Country* m = get(repo->countries, i);
		destroyCountry(m);
	}
	destroy(repo->countries);
	free(repo);
}


int find(CountryRepo* repo, char* name)
{
	/*
		This function finds if there exit two or more countries with the same name
		input:repo-is the actual repository,name- the name of the country
		output:returns 1 if there is no other country with the same name,otherwise 0
	*/
	for (int i = 0; i < getlenghtA(repo->countries); i++)
	{
		if (strcmp(getName(repo->countries->elemns[i]), name) == 0)
			return 0;
	}
	return 1;
}



Country * getCountryOnPos(CountryRepo * repo, int pos)
{
	/*
		checks if the position is in the correct interval
		it returns the elements on that position,otherwise NULL
	*/
	if (pos<0 || pos >= getlenghtA(repo->countries))
		return NULL;
	return get(repo->countries, pos);
}


void deletei(CountryRepo * repo, int poz)
{
	//This function deletes a country on a specific position
	//Input:repo-the repositoy, poz-the position of the element which must be removed
	int i;
	destroyCountry(repo->countries->elemns[poz]);
	deleteD(repo->countries, poz);
}

void update(CountryRepo * repo, char* continent, long population, int poz)
{
	//This function updates a country with a specific continent and population
	//Input:repo-the repository, continent/population to update, poz-the position of the element which must be updated

	//printf("%s", repo->monitor[poz]->continent);
	strcpy(repo->countries->elemns[poz]->continent, continent);
	repo->countries->elemns[poz]->population = population;
}

Country * sort(CountryRepo * res)
{
	/*
		This function sort by total population a given repository
		Input:res the repository to sort
		Output:returns the repostory sorted
	*/
	int j;
	Country* aux;
	for (int i = 0; i <getlenghtA(res->countries) - 1; i++)
	{
		for (j = i + 1; j < getlenghtA(res->countries); j++)
		{
			if (res->countries->elemns[i]->population > res->countries->elemns[j]->population)
			{
				aux = res->countries->elemns[i];
				res->countries->elemns[i] = res->countries->elemns[j];
				res->countries->elemns[j] = aux;
			}
		}
	}
	//destroyCountry(aux);
	return res;
}

Country * sortN(CountryRepo * reponew)
{
	/*
		This function sort alphabetic a given repository
		>res the repository to sort
		>returns the repostory sorted
	*/
	int j;
	Country* aux;
	for (int i = 0; i <getlenghtA(reponew->countries) - 1; i++)
	{
		for (j = i + 1; j < getlenghtA(reponew->countries); j++)
		{
			if (reponew->countries->elemns[i]->population < reponew->countries->elemns[j]->population)
			{
				aux = reponew->countries->elemns[i];
				reponew->countries->elemns[i] = reponew->countries->elemns[j];
				reponew->countries->elemns[j] = aux;
			}
		}
	}
	return reponew;
}


int add(CountryRepo * repo, Country * m)
{
	//This function adds a new element to the array
	//Returns 1 if the name is unigue,otherwise 0
	if (find(repo, m->name) != 1)
		return 0;
	addD(repo->countries, m);
	return 1;
}
