#include "AddORgate2.h"
#include "ApplicationManager.h"


AddORgate2::AddORgate2(void)
{
}


AddORgate2::~AddORgate2(void)
{
}

void AddORgate2::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("2-Input OR Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddORgate2::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\OR2.jpg");
	GInfo.IMGsel= new image("images\\OR2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Comp = new OR2(GInfo, OR2_FANOUT); 
	pManager->AddComponent(Comp);
	}
}

void AddORgate2::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddORgate2::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddORgate2::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\OR2.jpg");
	GInfo.IMGsel= new image("images\\OR2sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	OR2 *pA=new OR2(GInfo, OR2_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}