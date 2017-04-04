#pragma once
#include "Controller.h"


typedef struct
{
	Controller* cont;
}UI;

/*
This function creates the UI
*/
UI* createUI(Controller* cont);
/*
This function destroy the UI
*/
void destroyUI(UI* ui);


/*
This function starts the program
*/
void startUI(UI* ui);