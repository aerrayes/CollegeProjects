#include "AddLed.h"
#include "ApplicationManager.h"
#include "Led.h"
AddLed::AddLed(void)
{
}

AddLed::~AddLed(void)
{
}

void AddLed::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("Led: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddLed::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);

	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
		GraphicsInfo GInfo; 
		GInfo.IMG= new image("images\\ledOFF.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		GInfo.IMGsel = new image("images\\ledON.jpg");
		Comp = new Led(GInfo);
		pManager->AddComponent(Comp);
	}
}
void AddLed::Undo(ApplicationManager *pManager)
{/*
 GraphicsInfo G=pManager->get_last_comp()->getgraphicsinfo();
 pManager->Clear_image(G.x1,G.y1,G.x2,G.y2);
 pManager->DeletComp(pManager->get_last_comp());*/
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddLed::Redo(ApplicationManager *pManager)
{/*
 GraphicsInfo G=pManager->get_last_delet()->getgraphicsinfo();
 pManager->DrawComp(pManager->get_last_delet()->getgraphicsinfo().x1,pManager->get_last_delet()->getgraphicsinfo().y1,pManager->get_last_delet()->getgraphicsinfo().IMG);
 pManager->return_Delete_Comp();*/
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}


void AddLed::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\ledOFF.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	GInfo.IMGsel = new image("images\\ledON.jpg");
	Component *pA=new Led(GInfo);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}