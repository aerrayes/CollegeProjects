#include "RedoA.h"
#include "ApplicationManager.h"
//#include "AND2.h"

void RedoA::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("you click redo button");
}

void RedoA::Execute(ApplicationManager *pManager)
{
	Action * A = pManager->get_Redo_Action();
	if(A!=NULL)
		A->Redo(pManager);		
}
void RedoA::Undo(ApplicationManager *pManager)
{
}
void RedoA::Redo(ApplicationManager *pManager){}
