#include <fstream>
#include <string>

#include "Load.h"
#include "ApplicationManager.h"
#include "AddSwitch.h"
#include "AddLed.h"
#include "AddNOTgate.h"
#include "AddBUFFERgate.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
#include "AddORgate2.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddNORgate3.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"
#include "AddXNORgate2.h"


Load::Load(void)
{
}


Load::~Load(void)
{
}

void Load::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("Enter the file name you want to open");
	S = pManager->GetString();
	S = "Saved Files\\"+S+".txt";
	pManager->ClearStatesBar();
}

void Load::Execute(ApplicationManager *pManager)
{
	int MaxCompNo = 0,MaxCompNo1 = 0,f = 0,n = 0;
	int Number_of_Circuit_Levels,Number_of_Level_Components[60],
		Comp_ID[100],Component_Graphics_info_x[100],Component_Graphics_info_y[100],
		Source_Comp_ID[300],Target_Comp_ID[300],Pin_number[300];
	
	string Comp_Type[100],Label[100],Connections;
	int button;
	button = MessageBox(NULL,"your work will be removed""\n""Do you want to Load?","Load",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
	switch(button)
	{
	case(6): //Yes
		{
			pManager->UpdateInterface(1);
			ReadActionParameters(pManager);
			if(pManager->CheckSavedFile(S))
			{
				pManager->Del();
				ifstream In(S);
				In>>Number_of_Circuit_Levels;
				if(Number_of_Circuit_Levels == 0) return;
				for(int i=0;i<Number_of_Circuit_Levels;i++)
				{
					In>>Number_of_Level_Components[i];
					MaxCompNo += Number_of_Level_Components[i];
					while(f<MaxCompNo)
					{
						In	>>Comp_Type[f]
							>>Comp_ID[f]
							>>Label[f]
							>>Component_Graphics_info_x[f]
							>>Component_Graphics_info_y[f];
						f++;
					}
				}
				In>>Connections;
				int s=0;
				int x;
				In >> x;
				while(x!=-1)
				{
					Source_Comp_ID[s]=x;
					In >>Target_Comp_ID[s]
						>>Pin_number[s];
					s++;
					In>>x;
				}
				for(int m=0;m<Number_of_Circuit_Levels;m++)
				{
					MaxCompNo1 += Number_of_Level_Components[m];
					while(n < MaxCompNo1)
					{
						if (Comp_Type[n] == "SWITCH")
							AddSwitch::Load(Comp_ID[n],0,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "LED")
							AddLed::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "NOT")
							AddNOTgate::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "BUFFER")
							AddBUFFERgate::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "AND2")
							AddANDgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);	
						else if(Comp_Type[n] == "AND3")
							AddANDgate3::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "OR2")
							AddORgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "NAND2")
							AddNANDgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "NOR2")
							AddNORgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "NOR3")
							AddNORgate3::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "XOR2")
							AddXORgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "XOR3")
							AddXORgate3::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						else if(Comp_Type[n] == "XNOR2")
							AddXNORgate2::Load(Comp_ID[n],m,Component_Graphics_info_x[n],Component_Graphics_info_y[n],Label[n],pManager);
						n++;
					}
				}
				Component *C1= NULL,*C2=NULL;
				for(int z=0;z<s;z++)
				{
					for(int l=0;l<MaxCompNo;l++)
					{
						if(Source_Comp_ID[z] == Comp_ID[l])
							C1 = pManager->FindComp(Component_Graphics_info_x[l],Component_Graphics_info_y[l]);
						else if(Target_Comp_ID[z] == Comp_ID[l])
							C2 = pManager->FindComp(Component_Graphics_info_x[l],Component_Graphics_info_y[l]);
						else if(C1 != NULL && C2 != NULL)
							l = MaxCompNo;
					}
					if(C1 != NULL && C2 != NULL)
					{
						C1->getOutputPin()->ConnectTo(&C2->getInputPin()[--Pin_number[z]]);
						C1= NULL;C2=NULL;
					}
				}
			}
			else
				MessageBox(NULL,"there is no file with this name",NULL,MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
			break;
	}
	case(7): //NO
		return;
	}
}