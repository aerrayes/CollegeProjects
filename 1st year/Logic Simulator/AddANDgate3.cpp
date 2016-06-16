#include "AddANDgate3.h"
#include "ApplicationManager.h"


AddANDgate3::AddANDgate3(void)
{
}


AddANDgate3::~AddANDgate3(void)
{
}

void AddANDgate3::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("3-Input AND Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddANDgate3::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GInfo.IMG= new image("images\\And3.jpg");
		GInfo.IMGsel = new image("images\\And3sel.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		Comp = new And3(GInfo, AND3_FANOUT); 
		pManager->AddComponent(Comp);
	}
}

void AddANDgate3::Undo(ApplicationManager*pManager)
{
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
		pManager->RemoveComponent(Comp);
}
void AddANDgate3::Redo(ApplicationManager*pManager)
{
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
		pManager->AddComponent(Comp);
}

void AddANDgate3::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\And3.jpg");
	GInfo.IMGsel = new image("images\\And3sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	And3 *pA=new And3(GInfo, AND3_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}