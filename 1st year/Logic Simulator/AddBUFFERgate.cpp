#include "AddBUFFERgate.h"
#include "ApplicationManager.h"


AddBUFFERgate::AddBUFFERgate(void)
{
}


AddBUFFERgate::~AddBUFFERgate(void)
{
}

void AddBUFFERgate::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("BUFFER Gate: Click to add the gate");
	pManager->GetMouseInput(Cx,Cy);
	pManager->ClearStatesBar();
}

void AddBUFFERgate::Execute(ApplicationManager *pManager)
{
	//Get Center point of the Gate
	ReadActionParameters(pManager);
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
	{
		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GInfo.IMG= new image("images\\Buffer.jpg");
		GInfo.IMGsel= new image("images\\Buffersel.jpg");
		int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
		GInfo.x1 = Cx - Len/2;
		GInfo.x2 = Cx + Len/2;
		GInfo.y1 = Cy - Wdth/2;
		GInfo.y2 = Cy + Wdth/2;
		Comp = new Buffer(GInfo, Buffer_FANOUT); 
		pManager->AddComponent(Comp);
	}
}

void AddBUFFERgate::Undo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
		pManager->RemoveComponent(Comp);
}
void AddBUFFERgate::Redo(ApplicationManager*pManager)
{
	if(Cx > 95 && Cy > 105 && Cy < 620 && Cx < 960)
		pManager->AddComponent(Comp);
}

void AddBUFFERgate::Load(int id,int Level_no,int x,int y,string Label,ApplicationManager *pManager)
{
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	GInfo.IMG= new image("images\\Buffer.jpg");
	GInfo.IMGsel= new image("images\\Buffersel.jpg");
	int Len = GInfo.IMG->GetWidth(), Wdth = GInfo.IMG->GetHeight();
	GInfo.x1 = x - Len/2;
	GInfo.x2 = x + Len/2;
	GInfo.y1 = y - Wdth/2;
	GInfo.y2 = y + Wdth/2; 
	Buffer *pA = new Buffer(GInfo, AND2_FANOUT);
	pA->setString(Label);
	pA->SetID(id);
	pA->setLevel(Level_no);
	pManager->AddComponent(pA);
}