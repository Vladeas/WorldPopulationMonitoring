#include "Ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UI* CreateUI(Controller *ctrl)
{
	/*
		Create the UI
		Allocate memory for UI in memory 
	*/
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->cont = ctrl;
	return ui;
}


void DestroyUI(UI* ui)
{
	/*
		Free UI Memory
	*/
	destroyController(ui->cont);
	free(ui);
}



int AddCountryUI(UI* ui)
{
	/*
		Add a new country :
		> enter country name
		> enter continent
		> enter population
	*/
	char name[20], continent[20];
	long population;

	printf("<<< Enter country : ");
	scanf("%19s", name);
	do
	{
		printf("<<< Enter continent : ");
		scanf("%19s", continent);
		printf("<<< Enter population : ");
		scanf("%d", &population);
		/*
			Population must be bigger than 0
			Continent must be one of the given 5
		*/
	} while (population<0 && strcmp(continent, "Europe") != 0 && strcmp(continent, "America") != 0 && strcmp(continent, "Asia") != 0 && strcmp(continent, "Africa") != 0 && strcmp(continent, "Australia") != 0);

	return AddCountry(ui->cont, name, continent, population, 1);

}


void Interface()
{
	// User Interface ::
	printf("\n______________________________________________________________________\n\n");
	printf("	[0].Exit.\n");
	printf("	[1].Add country.\n");
	printf("	[2].Delete country.\n");
	printf("	[3].Update contry.\n");
	printf("	[4].List country by string.\n");
	printf("	[5].List all.\n");
	printf("	[6].List all for continent.\n");
	printf("	[7].Filter by population.\n");
	printf("	[8].Migration\n");
	printf("	[9].Undo.\n");
	printf("	[10].Redo.\n");
	printf("\n______________________________________________________________________\n\n");
}


int ReadIntNumber()
{
	//This function checks whether the command is an integer or not
	//Returns the command as integer
	char s[10];
	int res = 0, r = 0;
	while (r == 0)
	{
		printf("<<< Enter command : ");
		scanf("%s", s);
		r = sscanf(s, "%d", &res);
		if (r == 0)
			printf(">>> ERROR !\n");
	}
	return res;
}


int ValidCom(int com)
{
	//This function checks if the command is in the correct interval
	if (com >= 0 && com <= 10)
		return 1;
	else
		return 0;
}


void ListAll(UI* ui)
{
	//This function list all the elements
	//CountryRepo* repo = getrepo(ui->cont);
	int lenght = getlenghtA(ui->cont->repo->countries);

	if (lenght == 0)
	{
		char* str = ">>> NO COUNTRIES !";
		printf("%s \n", str);
	}

	for (int i = 0; i < getlenghtA(ui->cont->repo->countries); i++)
	{
		char str[200];
		toString(getCountryOnPos(ui->cont->repo, i), str);
		printf("%s\n", str);
	}

}


void ListCountryString(UI* ui)
{
	//This function reads from user a string and verify if the string match with the name of the countries
	//input:ui the address of the ui
	char s[20];
	printf("<<< Enter string : ");
	scanf("%19s", s);
	CountryRepo* res = listcountrybystring(ui->cont, s);
	int lenght = getlenghtA(res->countries);
	if (lenght == 0)
		printf(">>> NO MATCH !");
	else
		for (int i = 0; i < lenght; i++)
		{
			char str[200];
			toString(getCountryOnPos(res, i), str);
			printf("%s\n", str);
		}

	destroyRepo(res);
}


void DeleteUI(UI* ui)
{
	//This function reads from user the name of the country and checks if the country was removed or not
	//input:ui the address of the ui 
	char name[20];
	printf("<<< Enter country : ");
	scanf("%19s", name);
	int c = deleteitem(ui->cont, name, 1);
	if (c == 1)
	{
		printf(">>> SUCCESS !");
		//listally(ui);
	}
	else
		printf(">>> COUNTRY NOT FOUND !");
}


void UpdateUI(UI* ui)
{
	//This function reads from user the name of the country, the continent and the population 
	//Checks if the country was updated with success
	char name[20], continent[20];
	long population, c = 0;
	printf("<<< Enter country : ");
	scanf("%19s", name);
	do
	{
		printf("<<< Enter continent : ");
		scanf("%19s", continent);
		printf("<<< Enter population : ");
		scanf("%d", &population);
	} while (population<0 && strcmp(continent, "Europe") != 0 && strcmp(continent, "Asia") != 0 && strcmp(continent, "Africa") != 0 && strcmp(continent, "America") != 0 && strcmp(continent, "Australia") != 0);


	c = updatecont(ui->cont, name, continent, population, 1);
	if (c == 1)
		printf(">>> SUCCESS !\n");
	else
		printf(">>> ERROR !\n");

}

void SearchUI(UI* ui)
{
	//This function read from user a continent 
	//Checks if the continent contains any countries
	char continent[20];
	printf("<<< Enter continent : ");
	scanf("%19s", continent);

	CountryRepo* c = searchCont(ui->cont, continent);
	if (c->countries->lenght == 0)
		printf(">>> CONTINENT NOT FOUND !\n");
	else
		for (int i = 0; i < c->countries->lenght; i++)
		{
			char str[200];
			toString(getCountryOnPos(c, i), str);
			printf("%s\n", str);
		}

	destroyRepo(c);
}


void FilterUI(UI* ui)
{
	//This function reads from user a number of people
	//Print the sorted list of elements which contains the countries with the population higher than the input
	long population;

	do
	{
		printf("<<< Enter population : ");
		scanf("%d", &population);
	} while (population<0);
	CountryRepo* c = filterCont(ui->cont, population);
	if (c->countries->lenght == 0)
		printf(">>> HIGHER POPULACE NOT AVAILEBLE !\n");
	else
		for (int i = 0; i < c->countries->lenght; i++)
		{
			char str[200];
			toString(getCountryOnPos(c, i), str);
			printf("%s\n", str);
		}
	destroyRepo(c);
}


void Migration(UI* ui)
{
	long population;
	char name1[20], name2[20];
	do
	{
		printf("<<< Enter population : ");
		scanf("%d", &population);
	} while (population < 0);
	printf("<<< Enter origin country : ");
	scanf("%19s", name1);
	printf("<<< Enter destination country : ");
	scanf("%19s", name2);

	if (updateMigCont(ui->cont, name1, name2, population) == 1)
		printf(">>> SUCCESS !\n");
	else
		printf(">>> ERROR !\n");

}


void SUI(UI * ui)
{
	int go = 1, comm, arg, c;
	//printf("fhhYY45hggfhgfjgfhfdhff6789999Yhj\n");

	while (go == 1)
	{
		Interface();
		comm = ReadIntNumber();

		while (ValidCom(comm) == 0)
		{
			printf(">>> INVALID COMMAND !\n ");
			comm = ReadIntNumber();
		}

		if (comm == 0)
			break;

		if (comm == 1)
		{
			arg = AddCountryUI(ui);
			if (arg == 1)
				printf(">>> SUCCESS !\n");
			else
				printf(">>> ERROR !\n");
		}
		if (comm == 2)
		{
			DeleteUI(ui);
		}
		if (comm == 3)
			UpdateUI(ui);
		if (comm == 4)
		{
			ListCountryString(ui);
		}

		if (comm == 5)
		{
			ListAll(ui);
		}
		if (comm == 6)
		{
			SearchUI(ui);
		}
		if (comm == 7)
		{
			FilterUI(ui);
		}
		if (comm == 8)
		{
			Migration(ui);
		}
		if (comm == 9)
		{
			c = undo(ui->cont);
			if (c == 1)
				printf(">>> SUCCESS ! \n");
			else
				printf(">>> ERROR !\n");
		}
		if (comm == 10)
		{
			int co = redo(ui->cont);
			if (co == 1)
				printf(">>> SUCCESS !\n");
			else
				printf(">>> ERROR !\n");
		}
	}


}
