
#include <iostream>
#include <sstream>
#include <cmath>

#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"	// where Pause is found

// Function to wait for a mouse click and clear the screen
void WaitNClear(window &inputWindow);

#include "ApplicationManager.h"


int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the drawing window
		AppManager.UpdateInterface();
	

	}while(ActType != EXIT);

	
	return 0;
}
