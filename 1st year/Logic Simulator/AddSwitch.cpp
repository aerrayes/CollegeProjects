#include "AddSwitch.h"
#include "ApplicationManager.h"
#include "Switch.h"
AddSwitch::AddSwitch(void)
{
}
AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("Switch: Click where you wish to add it");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddSwitch::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo;
	GInfo.IMG=new image("images\\Switch OFF.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	GInfo.IMGsel = new image("images\\Switch ON.jpg");
	Comp = new Switch(GInfo);
	pManager->AddComponent(Comp);
	}
}
void AddSwitch::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddSwitch::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddSwitch::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\Switch OFF.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	GInfo.IMGsel = new image("images\\Switch ON.jpg");
	Component *pA=new Switch(GInfo);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}