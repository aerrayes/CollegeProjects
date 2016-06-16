#include "UndoA.h"
#include "ApplicationManager.h"
//#include "AND2.h"


void UndoA::ReadActionParameters(ApplicationManager *pManager)
{

}

void UndoA::Execute(ApplicationManager *pManager)
{
	Action * A = pManager->get_Undo_Action();
	if(A!=NULL)
		A->Undo(pManager);
}
void UndoA::Undo(ApplicationManager *pManager){}
void UndoA::Redo(ApplicationManager *pManager){}