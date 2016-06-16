#include "AddXORgate3.h"
#include "ApplicationManager.h"


AddXORgate3::AddXORgate3(void)
{
}


AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("3-Input XOR Gate: Click to add the gate");
	
	pManager->GetMouseInput(Cx,Cy);

	pManager->ClearStatesBar();
}

void AddXORgate3::Execute(ApplicationManager *pManager)
{
	ReadActionParameters(pManager);
	
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
	GraphicsInfo GInfo; 
	GInfo.IMG= new image("images\\Xor3.jpg");
	GInfo.IMGsel= new image("images\\Xor3sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	Comp = new Xor3(GInfo, Xor3_FANOUT); 
	pManager->AddComponent(Comp);
	}
}

void AddXORgate3::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->RemoveComponent(Comp);
}
void AddXORgate3::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	pManager->AddComponent(Comp);
}

void AddXORgate3::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\Xor3.jpg");
	GInfo.IMGsel= new image("images\\Xor3sel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2;
	Xor3 *pA = new Xor3(GInfo, Xor3_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}