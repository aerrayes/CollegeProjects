#include "AddLabel.h"
#include "ApplicationManager.h"


AddLabel::AddLabel(void)
{
}


AddLabel::~AddLabel(void)
{
}

void AddLabel::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->FlushKeyQueue();
	pManager->FlushMouseQueue();
	pManager->PrintMessage("Select Component to write label");
	while(1)
	{
		pManager->GetMouseInput(Cx, Cy);
		C = pManager->FindComp(Cx,Cy);
		pManager->ClearStatesBar();
		if(C==NULL)return;
		if(C->getString()=="-")
		{
			pManager->PrintMessage("Write here:");
			S = pManager->GetString(); 
			pManager->ClearStatesBar(); return;
		}
		else 
		{
			pManager->PrintMessage("Component Label is "+C->getString()+" change it (y/n)?");
			char c;
			pManager->WaitKeyPress(c);
			switch (c)
			{
			case'y':
			case'Y':
				{
					pManager->ClearStatesBar();
					pManager->PrintMessage("Write here (leave blank and press enter to delete):");
					S = pManager->GetString();
					if(S.compare("\r")==0) S="-";
					return;
				}
			default:
				{
					S = C->getString();
					pManager->ClearStatesBar();
					return;
				}
			}
		}
	}
}

void AddLabel::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	if(C != NULL)
		C->setString(S);
}
void AddLabel::Undo(ApplicationManager *pManager)
{
	C = pManager->FindComp(Cx,Cy);
	if(C != NULL)
		C->setString("-");
}

void AddLabel::Redo(ApplicationManager *pManager)
{
	C = pManager->FindComp(Cx,Cy);
	if(C != NULL)
		C->setString(S);
}
