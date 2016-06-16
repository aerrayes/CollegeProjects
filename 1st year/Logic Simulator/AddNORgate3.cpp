#include "AddNORgate3.h"
#include "ApplicationManager.h"

AddNORgate3::AddNORgate3(void)
{
}


AddNORgate3::~AddNORgate3(void)
{
}

void AddNORgate3::ReadActionParameters(ApplicationManager *pManager)
{

	pManager->PrintMessage("3-Input NOR Gate: Click to add the gate");
	
	pManager->GetMouseInput(Cx,Cy);

	pManager->ClearStatesBar();
}

void AddNORgate3::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);
	
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\NOR3.jpg");
	GInfo.IMGsel= new image("images\\NOR3sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Comp = new Nor3(GInfo, Nor3_FANOUT); 
	pManager->AddComponent(Comp);
	}
}

void AddNORgate3::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddNORgate3::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddNORgate3::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\NOR3.jpg");
	GInfo.IMGsel= new image("images\\NOR3sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Nor3 *pA=new Nor3(GInfo, Nor3_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}