#include "AddNANDgate2.h"
#include "ApplicationManager.h"


AddNANDgate2::AddNANDgate2(void)
{
}


AddNANDgate2::~AddNANDgate2(void)
{
}

void AddNANDgate2::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("2-Input NAND Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddNANDgate2::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GInfo.IMG= new image("images\\Nand2.jpg");
		GInfo.IMGsel= new image("images\\Nand2sel.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		Comp = new Nand2(GInfo, NAND2_FANOUT); 
		pManager->AddComponent(Comp);
	}
}

void AddNANDgate2::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddNANDgate2::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddNANDgate2::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\Nand2.jpg");
	GInfo.IMGsel= new image("images\\Nand2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Nand2 *pA=new Nand2(GInfo, NAND2_FANOUT); 
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}