#include "AddXNORgate2.h"
#include "ApplicationManager.h"

AddXNORgate2::AddXNORgate2(void)
{
}


AddXNORgate2::~AddXNORgate2(void)
{
}

void AddXNORgate2::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("2-Input XNOR Gate: Click to add the gate");
	
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddXNORgate2::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\XNor2.jpg");
	GInfo.IMGsel= new image("images\\XNor2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Comp = new XNOR2(GInfo, AND2_FANOUT); 
	pManager->AddComponent(Comp);
	}
}

void AddXNORgate2::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddXNORgate2::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddXNORgate2::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\XNor2.jpg");
	GInfo.IMGsel= new image("images\\XNor2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	XNOR2 *pA=new XNOR2(GInfo, AND2_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}