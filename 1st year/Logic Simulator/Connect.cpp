#include "Connect.h"
#include "Component.h"
#include "ApplicationManager.h"


void Connect::ReadActionParameters(ApplicationManager *pManager)
{
	clicktype k;
	do
	{
		pManager->PrintMessage("You have selected connection Tool , select the first Component (right click to exit)");
		int x,y;
		k=pManager->GetMouseInput(x,y);  //breaks the loop and the function if the user clicked right click
		pComp1 = pManager->FindComp(x,y); 
		pManager->ClearStatesBar();
	}
	while (pComp1 == NULL && k!=RIGHT_CLICK);

	if(k==RIGHT_CLICK) return;
	do
	{
		pManager->PrintMessage("Select the second Component");
		int x,y;
		pManager->GetMouseInput(x,y);
		pComp2 = pManager->FindComp(x,y);
		pManager->ClearStatesBar();
	}
	while(pComp2==NULL);
}

void Connect::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);

	if(pComp1!=pComp2 && pComp1 !=NULL &&pComp2!=NULL)
		for (int i =0;i<pComp2->getInputs();i++)
		{
			if (!pComp2->getInputPin()[i].getConnected())
			{
				if(pComp1->getOutputPin()->ConnectTo(&pComp2->getInputPin()[i]))
				{
					InputConn=i;
					return;
				}
				else 
				{
					i=pComp2->getInputs(); 
					InputConn=-1;
				}
			}
		}

}
void Connect::Undo(ApplicationManager *pManager)
{
	if (pComp1!=NULL && pComp2!=NULL)
		pComp1->getOutputPin()->Disconnect(&pComp2->getInputPin()[InputConn]);
	//disconnects the connection made before
}

void Connect::Redo(ApplicationManager *pManager)
{
	if (pComp1!=NULL && pComp2!=NULL)
		pComp1->getOutputPin()->ConnectTo(&pComp2->getInputPin()[InputConn]);
	//reconnects the same connection
}