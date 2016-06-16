#include "Simulation.h"
#include "ApplicationManager.h"
#include "Level.h"

void Simulation::ReadActionParameters(ApplicationManager*pManager)
{

	pManager->UpdateInterface();
	pManager->PrintMessage("Simulation Mode ON (press again on simulation icon to exit)");
	A=pManager->GetUserAction();
	x=pManager->Getx();
	y=pManager->Gety();
}

void Simulation::Execute(ApplicationManager*pManager)
{
	int z=0;bool t = false;
	while(pManager->getComponentList()[z]!=NULL&& !t)
	{ //remove from actionlist
		if(pManager->getComponentList()[z]->getOutputPin()!=NULL)
			if(pManager->getComponentList()[z]->getOutputPin()->ConnectedNo()==0)
			{
				/*pManager->ClearStatesBar();
				pManager->PrintMessage("Error Some or one of the gates are not all connected");*/

				MessageBox(NULL,"Error! Some or one of the gates are not all connected all connected pins are set to low","Warning",MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);break;
			}
		for (int i =0 ; i<pManager->getComponentList()[z]->getInputs();i++)
		{
			if(pManager->getComponentList()[z]->getInputPin()[i].getConnected())
				continue;
			else 
			{
					/*pManager->ClearStatesBar();
					pManager->PrintMessage("Error Some or one of the gates are not all connected");*/
				MessageBox(NULL,"Error! Some or one of the gates are not all connected all connected pins are set to low","Warning",MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
				i = pManager->getComponentList()[z]->getInputs(); t=true; break;
			}
		}
			z++;
	};
	if(pManager->getLevel()->ComponentSorted[0]->getLevel()!=0)
		MessageBox(NULL,"Gates exist in the first level!","Warning",MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
	for (int i =0;i<pManager->GetCompCount();i++) pManager->getComponentList()[i]->setSimulation(true);
	while(1)
	{ //x and y are not yet defined
		ReadActionParameters(pManager);
		//pManager->PrintMessage("Simulation Mode ON");
		if(A == SIMULATION) 
		{
			for(unsigned int i = 0 ; i<pManager->getLevel()->ComponentSorted.size();i++)
			{
				if(pManager->getLevel()->ComponentSorted[i]->getInputPin() == NULL)
					pManager->getLevel()->ComponentSorted[i]->setONOFF(false);
				if(pManager->getLevel()->ComponentSorted[i]->getOutputPin() ==NULL)
					pManager->getLevel()->ComponentSorted[i]->getInputPin()->setStatus(LOW);
			}
			for (int i =0;i<pManager->GetCompCount();i++) pManager->getComponentList()[i]->setSimulation(false);
			pManager->ClearStatesBar();
			return;
		}
		if(pManager->FindComp(x,y)!=NULL)
			if(pManager->FindComp(x,y)->getInputPin()==NULL)
			{
				pManager->FindComp(x,y)->setONOFF(!pManager->FindComp(x,y)->getONOFF());
			}
			for(unsigned int i = 0 ;i<pManager->getLevel()->ComponentSorted.size();i++)
			{
				pManager->getLevel()->ComponentSorted[i]->Operate();
				if(pManager->getLevel()->ComponentSorted[i]->getOutputPin() !=NULL)
					pManager->getLevel()->ComponentSorted[i]->getOutputPin()->sync();
			}
	}
}