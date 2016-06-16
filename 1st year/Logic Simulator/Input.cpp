#include "Input.h"
#include "Output.h"
Input::Input(window* pW)
{
	pDrawingWindow = pW; //point to the passed window
}

Input::~Input()
{}

clicktype Input::GetMouseInput(int &iX, int &iY)
{
	return pDrawingWindow->WaitMouseClick(iX,iY);
}

keytype Input::WaitKeyPress(char &cKey)
{
	return pDrawingWindow->WaitKeyPress(cKey);
}

string Input::GetString(Output* O)
{
	char ch;
	FlushKeyQueue();
	FlushMouseQueue();
	WaitKeyPress(ch);
	O->ClearAddrBar();
	string s;
	do 
	{
		s+=ch;
		if (ch=='\b')
		{
			s.erase(s.length()-1,1);
			if (!s.empty())
				s.erase(s.length()-1,1);
		}
		O->ClearAddrBar();
		O->DrawAddrBar(s);
		WaitKeyPress(ch);
	}
	while (ch!='\r');
	
	return s;
}
void Input::FlushKeyQueue()
{
	pDrawingWindow->FlushKeyQueue();
}
void Input::FlushMouseQueue()
{
	pDrawingWindow->FlushMouseQueue();
}
buttonstate Input:: GetButtonState(button btMouse, int &iX, int &iY)
{
	return pDrawingWindow->GetButtonState(btMouse,iX,iY);
}
