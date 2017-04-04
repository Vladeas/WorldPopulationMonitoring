#include "Controller.h"
#include <string.h>
#include <stdlib.h>


Controller * createController(CountryRepo * repo, OperationStack* undoS, OperationRedo* redoS)
{
	//This function creates the controller
	//input:repo which is the repository that contains the elements
	//returns the object controllers

	Controller* cont = (Controller*)malloc(sizeof(Controller));
	cont->repo = repo;
	cont->undoStack = undoS;
	cont->redoStack = redoS;

	return cont;
}


void destroyController(Controller* cont)
{
	//This function destroys the controller after the program is stoped
	destroyRepo(cont->repo);
	destroyStack(cont->undoStack);
	destroyRedo(cont->redoStack);
	free(cont);
}


int AddCountry(Controller * cont, char * name, char * continent, long population, int c)
{
	//This function adds a new elements to the array;
	//input:name-the name of the country,continent-continent names,population-the population of a country
	//output:returns 1 if the elements was added with success,otherwise 0
	Country* m = createCountry(name, continent, population);
	int res = add(cont->repo, m);
	if (res == 0)
		destroyCountry(m);

	if (c == 1)
	{
		Operation* o = createOperation(m, "add");
		push(cont->undoStack, o);
		destroyOperation(o);
		for (int i = 0; i < cont->redoStack->lengthr; i++)
			destroyOperation(cont->redoStack->redo[i]);
		cont->redoStack->lengthr = 0;
	}
	return res;
}


CountryRepo * getrepo(Controller * cont)
{
	//This function returns the hole repository
	return cont->repo;
}

CountryRepo * listcountrybystring(Controller * cont, char symbol[])
{
	//This function makes a new repo which will contain the elements which match with a given string
	//Input:cont the controller,symbol-the string to check
	//Output:returns the new repository
	CountryRepo* repo1 = createRepo();

	if (strcmp(symbol, "Null") == 0)
	{
		for (int j = 0; j < getlenghtA(cont->repo->countries); j++)
		{
			Country* newcountry = createCountry(cont->repo->countries->elemns[j]->name, cont->repo->countries->elemns[j]->continent, cont->repo->countries->elemns[j]->population);
			add(repo1, newcountry);
		}
		return repo1;
	}

	for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
	{
		Country* m = getCountryOnPos(cont->repo, i);
		if (strstr(getName(m), symbol) != NULL)
		{
			Country* newcountry = createCountry(m->name, m->continent, m->population);
			add(repo1, newcountry);
		}
	}
	return repo1;

}


int deleteitem(Controller* cont, char name[], int d)
{
	//This function checks if a country with a specific name can be deleted
	//Input:cont-the controller,name-The name of the country to check
	//Ouput:returns 1 if the country was removed, otherwise 0
	int lenght = getlenghtA(cont->repo->countries);
	char name1[20], continent[20];
	long population;

	for (int i = 0; i<lenght; i++)
	{
		if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
		{
			if (d == 1)
			{
				strcpy(name1, getName(cont->repo->countries->elemns[i]));
				strcpy(continent, getContinent(cont->repo->countries->elemns[i]));
				population = getPopulation(cont->repo->countries->elemns[i]);
				Country* m = createCountry(name1, continent, population);
				Operation* o = createOperation(m, "delete");
				push(cont->undoStack, o);
				destroyOperation(o);
				destroyCountry(m);
				for (int i = 0; i < cont->redoStack->lengthr; i++)
					destroyOperation(cont->redoStack->redo[i]);
				cont->redoStack->lengthr = 0;
			}
			deletei(cont->repo, i);
			return 1;
		}
	}
	return 0;


}

int updatecont(Controller * cont, char name[], char* continent, long population, int k)
{
	//This function checks if a country with a specific name can be updated
	//Input:cont-the controller,name-The name of the country to check
	//Ouput:returns 1 if the country was updated, otherwise 0
	int lenght = getlenghtA(cont->repo->countries);

	for (int i = 0; i < lenght; i++)
	{
		if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
		{
			if (k == 1)
			{
				Country* m = createCountry(getName(cont->repo->countries->elemns[i]), getContinent(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
				Operation* o = createOperation(m, "update");
				push(cont->undoStack, o);
				destroyOperation(o);
				destroyCountry(m);
				for (int i = 0; i < cont->redoStack->lengthr; i++)
					destroyOperation(cont->redoStack->redo[i]);
				cont->redoStack->lengthr = 0;
			}
			update(cont->repo, continent, population, i);
			return 1;
		}
	}
	return 0;
}

CountryRepo * searchCont(Controller * cont, char continent[])
{
	//This function checks if on a specific continent exists and return all it's countries
	//Input:cont-the controller,continent-the continent to check
	//Output:returns a new list which contains all the countries on a specific continent
	CountryRepo* reponew = createRepo();

	if (strcmp(continent, "Null") == 0)
		for (int j = 0; j < getlenghtA(cont->repo->countries); j++)
		{
			Country* newcountry = createCountry(cont->repo->countries->elemns[j]->name, cont->repo->countries->elemns[j]->continent, cont->repo->countries->elemns[j]->population);
			add(reponew, newcountry);
		}

	for (int i = 0; i<getlenghtA(cont->repo->countries); i++)
	{
		if (strcmp(getContinent(cont->repo->countries->elemns[i]), continent) == 0)
		{
			Country* newconuntry = createCountry(cont->repo->countries->elemns[i]->name, cont->repo->countries->elemns[i]->continent, cont->repo->countries->elemns[i]->population);
			add(reponew, newconuntry);
		}
	}
	if ((reponew->countries->lenght) != 0)
	{
		Country* c = sortN(reponew);
		return c;
	}
	else
		return reponew;

}

CountryRepo * filterCont(Controller * cont, long population)
{
	//This function makes a new repo which contains the element which have the population higher than a given number
	//Input:cont-the controller, population-The number of population to check
	//Output:returns the repo sorted
	CountryRepo* res = createRepo();
	for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
	{
		if (getPopulation(cont->repo->countries->elemns[i]) >= population)
		{
			Country* newconuntry = createCountry(cont->repo->countries->elemns[i]->name, cont->repo->countries->elemns[i]->continent, cont->repo->countries->elemns[i]->population);
			add(res, newconuntry);
		}
	}

	if ((res->countries->lenght) != 0)
	{
		Country* c = sort(res);
		return c;
	}
	else
		return res;
}


int updateMing(Controller* cont, char* name2, long population)
{
	for (int j = 0; j < getlenghtA(cont->repo->countries); j++)
		if (strcmp(getName(cont->repo->countries->elemns[j]), name2) == 0)
		{
			Country* m = createCountry(getName(cont->repo->countries->elemns[j]), getContinent(cont->repo->countries->elemns[j]), getPopulation(cont->repo->countries->elemns[j]));
			Operation* o = createOperation(m, "updateM");
			push(cont->undoStack, o);
			destroyOperation(o);
			destroyCountry(m);
			cont->repo->countries->elemns[j]->population += population;
			return 1;
		}
	return 0;
}



int updateMigCont(Controller * cont, char * name1, char * name2, long population)
{
	for (int i = 0; i<getlenghtA(cont->repo->countries); i++)
		if (strcmp(getName(cont->repo->countries->elemns[i]), name1) == 0 && getPopulation(cont->repo->countries->elemns[i])>population)
			if (updateMing(cont, name2, population) == 1)
			{
				Country* m1 = createCountry(getName(cont->repo->countries->elemns[i]), getContinent(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
				Operation* o = createOperation(m1, "updateM");
				push(cont->undoStack, o);
				destroyOperation(o);
				destroyCountry(m1);
				cont->repo->countries->elemns[i]->population -= population;
				for (int i = 0; i < cont->redoStack->lengthr; i++)
					destroyOperation(cont->redoStack->redo[i]);
				cont->redoStack->lengthr = 0;
				return 1;
			}
	return 0;
}



int undo(Controller * cont)
{
	if (isEmpty(cont->undoStack))
	{
		return 0;
	}

	int c;
	Operation* operation = pop(cont->undoStack);
	if (strcmp(getOpType(operation), "add") == 0)
	{
		Country* country = getcountries(operation);
		Operation* op = createOperation(country, "add");
		pushRedo(cont->redoStack, op);
		destroyOperation(op);
		char name[20];
		strcpy(name, getName(country));
		for (int i = 0; i<getlenghtA(cont->repo->countries); i++)
			if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
				deletei(cont->repo, i);
	}
	else
		if (strcmp(getOpType(operation), "delete") == 0)
		{
			Country* country = getcountries(operation);
			Operation* op = createOperation(country, "delete");
			pushRedo(cont->redoStack, op);
			destroyOperation(op);
			char name[20], continent[20];
			long population = getPopulation(country);
			strcpy(name, getName(country));
			strcpy(continent, getContinent(country));
			Country* m = createCountry(name, continent, population);
			add(cont->repo, m);
		}
		else
			if (strcmp(getOpType(operation), "update") == 0)
			{
				Country* country = getcountries(operation);
				char continent[20], name[20];
				long population = getPopulation(country);
				strcpy(name, getName(country));
				strcpy(continent, getContinent(country));
				for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
					if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
					{
						Country* con = createCountry(getName(cont->repo->countries->elemns[i]), getContinent(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
						Operation* op = createOperation(con, "update");
						pushRedo(cont->redoStack, op);
						destroyOperation(op);
						destroyCountry(con);
						update(cont->repo, continent, population, i);
					}
			}
			else
				if (strcmp(getOpType(operation), "updateM") == 0)
				{
					Country* country = getcountries(operation);
					char continent[20], name[20];
					long population = getPopulation(country);
					strcpy(name, getName(country));
					strcpy(continent, getContinent(country));
					for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
						if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
						{
							Country* con = createCountry(getName(cont->repo->countries->elemns[i]), getContinent(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
							//printf("%s,%d\n", getName(cont->repo->countries->elemns[i]),getPopulation(cont->repo->countries->elemns[i]));
							Operation* op = createOperation(con, "updateM");
							pushRedo(cont->redoStack, op);
							destroyOperation(op);
							destroyCountry(con);
							update(cont->repo, continent, population, i);
						}

					destroyOperation(operation);

					Operation* operation1 = pop(cont->undoStack);
					Country* country1 = getcountries(operation1);
					char continent1[20], name1[20];
					long population1 = getPopulation(country1);
					strcpy(name1, getName(country1));
					strcpy(continent1, getContinent(country1));
					for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
						if (strcmp(getName(cont->repo->countries->elemns[i]), name1) == 0)
						{
							Country* con1 = createCountry(getName(cont->repo->countries->elemns[i]), getContinent(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
							//printf("%s,%d\n", getName(cont->repo->countries->elemns[i]), getPopulation(cont->repo->countries->elemns[i]));
							Operation* op = createOperation(con1, "updateM");
							pushRedo(cont->redoStack, op);
							destroyOperation(op);
							destroyCountry(con1);
							update(cont->repo, continent1, population1, i);
						}
					destroyOperation(operation1);
					c = 1;
				}
	if (c == 0)
		destroyOperation(operation);
	//printf("k");
	return 1;
}

int redo(Controller* cont)
{
	if (isEmpty(cont->redoStack))
		return 0;

	int c;
	Operation* op = popRedo(cont->redoStack);
	if (strcmp(getOpType(op), "add") == 0)
	{
		Country* country = getcountries(op);
		char name[20], continent[20];
		long population = getPopulation(country);
		strcpy(name, getName(country));
		strcpy(continent, getContinent(country));
		Country* m = createCountry(name, continent, population);
		add(cont->repo, m);
	}
	else
		if (strcmp(getOpType(op), "delete") == 0)
		{
			Country* country = getcountries(op);
			char name[20];
			strcpy(name, getName(country));
			for (int i = 0; i<getlenghtA(cont->repo->countries); i++)
				if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
					deletei(cont->repo, i);
		}
		else
			if (strcmp(getOpType(op), "update") == 0)
			{
				Country* country = getcountries(op);
				char continent[20], name[20];
				long population = getPopulation(country);
				strcpy(name, getName(country));
				strcpy(continent, getContinent(country));
				for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
					if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
						update(cont->repo, continent, population, i);
			}
			else
				if (strcmp(getOpType(op), "updateM") == 0)
				{
					Country* country = getcountries(op);
					char continent[20], name[20];
					long population = getPopulation(country);
					strcpy(name, getName(country));
					strcpy(continent, getContinent(country));
					for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
						if (strcmp(getName(cont->repo->countries->elemns[i]), name) == 0)
							cont->repo->countries->elemns[i]->population = population;

					destroyOperation(op);

					Operation* op1 = popRedo(cont->redoStack);
					Country* country1 = getcountries(op1);
					char continent1[20], name1[20];
					long population1 = getPopulation(country1);
					strcpy(name1, getName(country1));
					strcpy(continent1, getContinent(country1));
					for (int i = 0; i < getlenghtA(cont->repo->countries); i++)
						if (strcmp(getName(cont->repo->countries->elemns[i]), name1) == 0)
							update(cont->repo, continent1, population1, i);

					destroyOperation(op1);
					c = 1;
				}
	if (c == 0)
		destroyOperation(op);

	return 1;
}

