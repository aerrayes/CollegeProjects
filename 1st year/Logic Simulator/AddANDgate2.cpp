#include "AddANDgate2.h"
#include "ApplicationManager.h"

AddANDgate2::AddANDgate2(void)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("2-Input AND Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddANDgate2::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GInfo.IMG= new image("images\\AND2.jpg");
		GInfo.IMGsel = new image("images\\AND2sel.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		Comp =new AND2(GInfo, AND2_FANOUT); 
		pManager->AddComponent(Comp);
	}
}
void AddANDgate2::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddANDgate2::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddANDgate2::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\AND2.jpg");
	GInfo.IMGsel = new image("images\\AND2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Component *pA=new AND2(GInfo, AND3_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}