#include "Delete.h"
#include "ApplicationManager.h"
using namespace std;
#include "Connect.h"
Delete::Delete(void)
{
	for (int i =0 ; i<FIXED;i++)
	{
		Left[i]=NULL;
		Right[i]=NULL;
	}
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("Select the Component or Connection you wish to Delete (click anywhere to close)");
	int x,y;
	pManager->GetMouseInput(x,y);
	pComp=pManager->FindComp(x,y);
	if(pComp==NULL)
	{
		pManager->getConnections(Right[0],Left[0],x,y);
	}
}

void Delete::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);

	if(pComp==NULL)
	{
		if(Right[0]!=NULL&&Left[0]!=NULL)
			Left[0]->Disconnect(Right[0]);
	}
	else
	{

		for (int i =0;i<pComp->getInputs();i++)
		{                 //disconnects every thing connected to input
			int j=0; bool T=true;
			while(pManager->getComponentList()[j]!=NULL&&T)
			{
				if(pManager->getComponentList()[j]->getOutputPin())
				if(pManager->getComponentList()[j]->getOutputPin()->Disconnect(&pComp->getInputPin()[i]))
				{
					Left[i]=pManager->getComponentList()[j]->getOutputPin();
					T=false;
				}
				j++;
			}
		}
		if(pComp->getOutputPin()!=NULL)
		{
			int Conns=pComp->getOutputPin()->ConnectedNo();
			for(int i=0;i<Conns;i++)
			{    //disconnects every pin from output pin
				Right[i] = pComp->getOutputPin()->getInputPins()[0];
				pComp->getOutputPin()->Disconnect(pComp->getOutputPin()->getInputPins()[0]);
			}
		}
			pManager->RemoveComponent(pComp);
	}
}
void Delete::Undo(ApplicationManager *pManager)
{
	if(pComp==NULL)
	{
		if(Right[0]!=NULL&&Left[0]!=NULL)
			Left[0]->ConnectTo(Right[0]);
	}
	else
	{
		pManager->AddComponent(pComp);
		for (int i = 0;i<FIXED;i++)
		{
			if(Left[i]!=NULL)
				Left[i]->ConnectTo(&pComp->getInputPin()[i]);
			//}
			//for(int i =0 ; i<FIXED;i++)
			//{
			if(Right[i]!=NULL)
				pComp->getOutputPin()->ConnectTo(Right[i]);
		}
	}
	//add connections
}
void Delete::Redo(ApplicationManager *pManager)
{
	if(pComp==NULL)
	{
		if(Right[0]!=NULL&&Left[0]!=NULL)
			Left[0]->Disconnect(Right[0]);

	}
	else
	{
		pManager->RemoveComponent(pComp);
		for(int i = 0 ;i<FIXED ; i++)
		{
			if(Left[i]!=NULL)
				Left[i]->Disconnect(&pComp->getInputPin()[i]);
			if(Right[i]!=NULL)
				pComp->getOutputPin()->Disconnect(Right[i]);
		}
	}
	//remove connections again
}