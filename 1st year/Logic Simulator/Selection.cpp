#include "Selection.h"
#include "ApplicationManager.h"

Selection::Selection(void)
{
}


Selection::~Selection(void)
{
}

void Selection::ReadActionParameters(ApplicationManager *pManager)
{
	Cx = pManager->Getx();
	Cy = pManager->Gety();
}

void Selection::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);

	bool T = false;
	C = pManager->FindComp(Cx,Cy);
	if(C != NULL)
		C->SetMark(T);
}