#include "Exit.h"
#include "ApplicationManager.h"
#include "Selection.h"
//#include "AND2.h"
//#define MessageBoxA //MessageBoxA
//#define MessageBoxButtons
using namespace std;
Exit::Exit(void)
{
}

Exit::~Exit(void)
{
}

void Exit::ReadActionParameters(ApplicationManager *pManager)
{
}

void Exit::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	int button1;
	//Message box 
	button1=MessageBox(NULL,"Do you want to save?","Exit",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	switch(button1)
	{
	case(6): //Yes
		pManager->ExecuteAction(SAVE);
		break;
	case(7): //NO
		return;
	}
}
void Exit::Undo(ApplicationManager *pManager){}
void Exit::Redo(ApplicationManager *pManager){}