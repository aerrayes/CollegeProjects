#include "AddNOTgate.h"
#include "ApplicationManager.h"


AddNOTgate::AddNOTgate(void)
{
}


AddNOTgate::~AddNOTgate(void)
{
}

void AddNOTgate::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("NOT Gate: Click to add the gate");
	
	pManager->GetMouseInput(Cx,Cy);

	pManager->ClearStatesBar();
}

void AddNOTgate::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\NOT.jpg");
	GInfo.IMGsel= new image("images\\NOTsel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Comp = new Not(GInfo, Not_FANOUT); 
	pManager->AddComponent(Comp);
	}
}

void AddNOTgate::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddNOTgate::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddNOTgate::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\NOT.jpg");
	GInfo.IMGsel= new image("images\\NOTsel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Not *pA=new Not(GInfo, Not_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}