#pragma once

#include "CMUgraphicsLib\CMUgraphics.h"
class Output;


class Input		//The application manager should have a pointer to this class
{
private:
	window *pDrawingWindow;	//Pointer to the Graphics Window

public:
	Input(window *pW);
	~Input();

	clicktype GetMouseInput(int &x, int &y);	//Get coordinate where user clicks
	string GetString(Output* O);	//Returns a string entered by the user
	keytype WaitKeyPress(char &cKey);
	void FlushKeyQueue();
	buttonstate GetButtonState(button btMouse, int &iX, int &iY);
	void FlushMouseQueue();
};
