#include "AddNORgate2.h"
#include "ApplicationManager.h"


AddNORgate2::AddNORgate2(void)
{
}


AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("2-Input NOR Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddNORgate2::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);

	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{	
		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GInfo.IMG= new image("images\\NOR2.jpg");
		GInfo.IMGsel= new image("images\\NOR2sel.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		Comp = new Nor2(GInfo, Nor2_FANOUT); 
		pManager->AddComponent(Comp);
	}
}

void AddNORgate2::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddNORgate2::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddNORgate2::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\NOR2.jpg");
	GInfo.IMGsel= new image("images\\NOR2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Nor2 *pA=new Nor2(GInfo, Nor2_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}