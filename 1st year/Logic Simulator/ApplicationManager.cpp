#include <fstream>
#include "ApplicationManager.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
#include "AddBUFFERgate.h"
#include "AddLed.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddNORgate3.h"
#include "AddNOTgate.h"
#include "AddORgate2.h"
#include "AddSwitch.h"
#include "AddXNORgate2.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"
#include "Simulation.h"
#include "Save.h"
#include "Load.h"
#include "Connect.h"
#include "Move.h"
#include "UndoA.h"
#include "RedoA.h"
#include "AddLabel.h"
#include "Selection.h"
#include "Delete.h"
#include "Exit.h"
#include "TruthTable.h"
#include <typeinfo>
ApplicationManager::ApplicationManager()
{
	ifstream in("Saved Files\\Savedfiles.txt");
	CompCount = 0;
	NO_of_Saved_files = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;
	for(int i=0; i<50; i++)
		Savedfileslist[i] = "";
	char save[80];
	int i=0;
	while(!in.eof())
	{
		in.getline(save,80);
		Savedfileslist[i] = (string)save;
		NO_of_Saved_files++;
		i++;
	}

	O = new Output;
	I = O->CreateInput();

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	if(empty(pComp->getgraphicsinfo()))
		//handle the case of Components more than compcount
		CompList[CompCount++] = pComp;	
	else
	{
		WriteAddBar("This place is occupied");
		delete pComp;
		ActionList.top()->Execute(this);
	}

}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	for(int i=0; i<CompCount; i++)
		CompList[i]->SetMark(true);

	I->GetMouseInput(x,y);
	UpdateInterface();

	if(O->get_new_window() != NULL)
		O->deletewindow();
	if(x>=98&& x<=161 &&y>=30 && y<=83)
		return ADD_AND_GATE_2;
	else if(x>=166&& x<=230 &&y>=28 && y<=81)
		return ADD_AND_GATE_3;
	else if(x>=235&& x<=303 &&y>=28 && y<=82)
		return ADD_OR_GATE_2;
	else if(x>=309&& x<=388 &&y>=28 && y<=81)
		return ADD_XOR_GATE_2;
	else if(x>=393&& x<=466 &&y>=30 && y<=82)
		return ADD_XOR_GATE_3;
	else if(x>=473&& x<=521 &&y>=31 && y<=84)
		return ADD_BUFFER_GATE;
	else if(x>=529&& x<=587 &&y>=30 && y<=85)
		return ADD_NOT_GATE;
	else if(x>=594&& x<=663 &&y>=30 && y<=83)
		return ADD_NOR_GATE_2;
	else if(x>=670&& x<=737 &&y>=33 && y<=83)
		return ADD_NOR_GATE_3;
	else if(x>=742&& x<=802 &&y>=33 && y<=83)
		return ADD_NAND_GATE_2;
	else if(x>=807&& x<=888 &&y>=33 && y<=83)
		return ADD_XNOR_GATE_2;
	else if(x>=893 && x<=948&&y>29&&y<51)
		return ADD_SWITCH;
	else if(x>=895&& x<=947 && y>=61 && y<=84)
		return ADD_LED;
	else if(x>=10 && x<=91 && y>=208 && y<=277)
		return CONNECT;
	else if (x>=15&& x<=93 && y>=277 && y<=331)
		return LABEL;
	else if (x >=16 && x<=88 && y>=102 && y<=162)
		return SIMULATION;
	else if (x >=17 && x <=85 && y>=165 && y<=204)
		return TRUTHTABLE;	
	else if (x >=12 && x <=90 && y>=336 && y<=409)
		return MOVE;
	else if (x >=12 && x <=86 && y>=410 && y<=466)
		return UNDO;
	else if (x >=11 && x <=87 && y>=472 && y<=521)
		return REDO;
	else if (x >=10 && x <=88 && y>=528 && y<=586)
		return DEL;
	else if (x >=12 && x <=88 && y>=588 && y<=642)
		return SAVE;
	else if (x >=8 && x <=90 && y>=643 && y<=694)
		return LOAD;
	else if (x >=974 && x <=1009 && y>=33 && y<=70)
		return EXIT;
	else 
		return SELECT;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType A)
{

	Action* pAct;
	switch (A)
	{
	case ADD_AND_GATE_2:
		pAct= new AddANDgate2;
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3;
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2;
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2;
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3;
		break;
	case ADD_BUFFER_GATE:
		pAct = new AddBUFFERgate;
		break;
	case ADD_NOT_GATE:
		pAct = new AddNOTgate;
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2;
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3;
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2;
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2;
		break;
	case ADD_SWITCH:
		pAct = new AddSwitch;
		break;
	case ADD_LED:
		pAct = new AddLed;
		break;
	case SIMULATION:
		pAct = new Simulation;
		break;
	case TRUTHTABLE:
		pAct = new TruthTable;
		break;
	case CONNECT:
		pAct= new Connect;
		break;
	case SAVE:
		pAct = new Save;
		break;
	case LOAD:
		pAct = new Load;
		break;
	case MOVE:
		pAct = new Move;
		break;
	case UNDO:
		pAct = new UndoA;
		break;
	case REDO:
		pAct = new RedoA;
		break;
	case LABEL:
		pAct = new AddLabel;
		break;
	case SELECT:
		pAct = new Selection;
		break;
	case DEL:
		pAct = new Delete;
		break;
	case EXIT:
		pAct = new Exit; 
		break;
	}
	if(A!=REDO&&A!=UNDO&&A!=SELECT&&A!=TRUTHTABLE&&A!=SIMULATION)
	{
		while(!RedoList.empty())
		{
			Action* A = RedoList.top();
			RedoList.pop();
			delete A;
		}

		ActionList.push(pAct); 
		pAct->Execute(this);
	}
	else 
	{ 
		pAct->Execute(this);
		delete pAct;
	}
	L.Update(this);

}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	SetBuffering(true);
	if(L.ComponentSorted.size()==0||!L.ComponentSorted[0]->getSimulation())
		Draw_new_Window();
	else
		O->Draw_new_window_sim();
	for(int i=0; i<CompCount; i++)
	{CompList[i]->Draw(this);}
	UpdateBuffer();
	SetBuffering(false);  

}
void ApplicationManager::UpdateInterface(int x)
{
	Draw_new_Window();

	for(int i=0; i<CompCount; i++)
	{CompList[i]->Draw(this);}	
}
////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];	
	while(!ActionList.empty())
	{
		Action* A = ActionList.top();
		ActionList.pop();
	}
	while(!RedoList.empty())
	{
		Action* A = RedoList.top();
		RedoList.pop();
		delete A;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::PrintMessage(string msg)
{
	O->PrintMessage(msg);
}
///////////////////////////////////////////////////////////////////

void ApplicationManager::ClearStatesBar()
{
	O->ClearStatesBar();
}
//////////////////////////////////////////////////////////////////

void ApplicationManager::DrawComp(int x,int y,image *I)
{
	O->DrawComp(x,y,I);
}
//////////////////////////////////////////////////////////////////

keytype ApplicationManager::WaitKeyPress(char &cKey)
{
	return I->WaitKeyPress(cKey);
}
/////////////////////////////////////////////////////////////////

clicktype ApplicationManager::GetMouseInput(int &x, int &y)
{
	return I->GetMouseInput(x,y);
}
////////////////////////////////////////////////////////////////////

string ApplicationManager::GetString()
{
	return I->GetString(O);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::WriteAddBar(string S)
{
	O->DrawAddrBar(S);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ClearAddBar()
{
	O->ClearAddrBar();
}
////////////////////////////////////////////////////////////////////

Component* ApplicationManager::FindComp(int x,int y)
{
	GraphicsInfo G;
	for(int i=0;i<CompCount;i++)
	{
		G = CompList[i]->getgraphicsinfo();
		if(x > G.x1 && x < G.x2 && y > G.y1 && y < G.y2)
			return CompList[i];
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////

Component* ApplicationManager::getComponent()
{
	int x,y;
	GetMouseInput(x,y);
	return FindComp(x,y);
}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::getComponent(InputPin* Pin)
{
	for (int i =0;i<CompCount;i++)
	{
		for(int j =0;j<CompList[i]->getInputs();j++)
		{
			if (&CompList[i]->getInputPin()[j] == Pin )
				return CompList[i];
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::DrawLine(int x1,int y1 ,int x2,int y2)
{
	O->DrawLine( x1, y1 , x2, y2);
}
///////////////////////////////////////////////////////////////////

buttonstate  ApplicationManager::GetButtonState(button btMouse, int &iX, int &iY)
{
	return I->GetButtonState(btMouse,iX,iY);
}
/////////////////////////////////////////////////////////////////

bool ApplicationManager::SetBuffering(const bool bSetting)
{
	return O->SetBuffering(bSetting);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::Draw_new_Window()
{
	O->Draw_new_Window();
}
//////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateBuffer()
{
	O->UpdateBuffer();
}
///////////////////////////////////////////////////////////////////

void ApplicationManager::FlushKeyQueue()
{
	I->FlushKeyQueue();
}
/////////////////////////////////////////////////////////////////

void ApplicationManager::FlushMouseQueue()
{
	I->FlushMouseQueue();
}
////////////////////////////////////////////////////////////////////

Action*ApplicationManager::get_Undo_Action()
{
	if(!ActionList.empty())
	{
		Action* A=ActionList.top();
		RedoList.push(A);
		ActionList.pop();
		return A;
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////
Action*ApplicationManager::get_Redo_Action()
{
	if(!RedoList.empty())
	{
		Action*A= RedoList.top();
		ActionList.push(A);
		RedoList.pop();
		return A;
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::RemoveComponent(Component*pComp)
{
	for(int i = 0 ; i<CompCount;i++)
		if(CompList[i]==pComp)
		{
			CompList[i]=CompList[--CompCount];
			CompList[CompCount]=NULL;
			return;
		}
}
////////////////////////////////////////////////////////////////////

bool ApplicationManager::empty(GraphicsInfo GFx)
{
	if(FindComp(GFx.x1,GFx.y1)==NULL)
		if(FindComp(GFx.x2,GFx.y1)==NULL)
			if(FindComp(GFx.x1,GFx.y2)==NULL)
				if(FindComp(GFx.x2,GFx.y2)==NULL)
					if(FindComp((GFx.x1+GFx.x2)/2,(GFx.y1+GFx.y2)/2)==NULL)
						return true;
	return false;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::getCompNo(Component* &comp ,int i)
{
	comp = CompList[i];
}
////////////////////////////////////////////////////////////////////

int ApplicationManager::degreeComponent(Component *c)
{
	for(int i=0;i<CompCount;i++)
	{
		if(c==CompList[i])
			return i;
	}
	return -1;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::Del()
{
	for(int i=0; i<CompCount; i++)
	{
		delete CompList[i];	
		CompList[i]=NULL;
	}
	while(!ActionList.empty())
	{
		Action* A = ActionList.top();
		ActionList.pop();
	}
	while(!RedoList.empty())
	{
		Action* A = RedoList.top();
		RedoList.pop();
		delete A;
	}
	CompCount = 0;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::getComponent(int x,int y,Component *Com[2],InputPin* &inp)
{
	PinInfo p;
	int x1,x2, y1, y2,x3;
	InputPin* Inp;
	for(int i=0;i<CompCount;i++)
	{
		OutputPin* outp=CompList[i]->getOutputPin();
		p = CompList[i]->getOutputPin()->getPinInfo();
		x1=p.x+CompList[i]->getgraphicsinfo().x1;
		y1=p.y+CompList[i]->getgraphicsinfo().y1;
		for(int z=0;z<outp->ConnectedNo();z++){
			Component *c=this->getComponent(outp->getInputPins()[z]);
			for(int r=0;r<c->getInputs();r++){
				Inp=&c->getInputPin()[r];
				x2=Inp->getPinInfo().x+c->getgraphicsinfo().x1;
				y2=Inp->getPinInfo().y+c->getgraphicsinfo().y1;
				x3=(x2-x1)/2+x1;
				if(x1<x2&&y1>y2){
					if(((x+2 > x1 ) ||(x-2 > x1))&&( y+2 <= y1)||( y-2 <= y1 )&&((x+2<x2)||(x-2<x2))&&((y-2>y2)||(y+2>y2)))
					{
						if(((x+2<x2)||(x-2<x2))&&((y-2>y2)||(y+2>y2)))
						{
							if(((x+2>x1)||(x-2>x1))&&((x+2<x3)||(x-2<x3)))
							{
								if(y-y1==0||y-y1==2||y-y1==1||y-y1==-1||y-y1-2){
									Com[0]=CompList[i];
									Com[1]=c;
									inp=Inp;
									break;
								}
							}
							else if((x-x3)==2||(x-x3)==-2||(x-x3)==-1||(x-x3)==1||(x-x3)==0)
							{
								Com[0]=CompList[i];
								Com[1]=c;
								inp=Inp;
								break;
							}
							else if(((x+2>x3)||((x-2>x3)))&&((x+2<x2)||(x-2<x2)))
							{if(y-y1==0||y-y1==2||y-y1==1||y-y1==-1||y-y1==-2){
							}
							else	{Com[0]=CompList[i];
							Com[1]=c;
							inp=Inp;
							break;
							}
							}
						}

					}
				}
				else if(x1<x2&&y1<y2){
					if((x+2>x1||x-2>x1)&&((y+2>=y1)||(y-2>=y1))&&((x+2<x2)||x-2<x2)&&((y+2<=y2)||(y-2<=y2)))
					{
						if(((x+2<x2)||x-2<x2)&&((y+2<=y2)||(y-2<=y2)))
						{if(((x+2>x1)||((x-2>x1)))&&((x+2<x3)||(x-2<x3)))
						{if(Com[0]==NULL){
							Com[0]=CompList[i];
							Com[1]=c;
							inp=Inp;
							break;}
						}
						else if((x-x3)==2||(x-x3)==-2||(x-x3)==-1||(x-x3)==1||(x-x3)==0)
						{if(Com[0]==NULL){
							Com[0]=CompList[i];
							Com[1]=c;
							inp=Inp;
							break;}
						}
						else if(((x+2>x3)||(x-2>x3))&&((x+2<x2)||(x-2<x2)))
						{if(y-y1==0||y-y1==2||y-y1==1||y-y1==-1||y-y1==-2){
						}
						else {if(Com[0]==NULL){
							Com[0]=CompList[i];
							Com[1]=c;
							inp=Inp;
							break;}
						}
						}}

					}
				}
			}}}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateSavedFilesList(string S)
{
	Savedfileslist[NO_of_Saved_files] = S;
	ofstream out("Saved Files\\Savedfiles.txt",ios::app);
	out<<Savedfileslist[NO_of_Saved_files]<<"\n";
	NO_of_Saved_files++;
}
////////////////////////////////////////////////////////////////////

bool ApplicationManager::CheckSavedFile(string S)
{
	for(int i=0; i<NO_of_Saved_files; i++)
	{
		if(S == Savedfileslist[i])
			return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ClearSavedFilesList()
{
	ofstream out("Saved Files\\Savedfiles.txt");
	out<<"";
	for(int i=0; i<NO_of_Saved_files; i++)
		Savedfileslist[i] = "";
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::print_msg_in_truthtable(int i,int j,string s)
{
	O->print_msg_in_truthtable(i,j,s);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::Draw_TRUTH_TABLE(int i,int j)
{
	O->Draw_TRUTH_TABLE(i,j);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::getConnections(InputPin*& In,OutputPin *& Out, int x,int y)
{
	vector<WireInfo> Wires;		//initializing a vector of wires , where wires is a stuct 
								//that holds the position of the wires and holds the pins between this wire
	for(int i =0 ; i<CompCount;i++)
	{
		if(CompList[i]->getOutputPin()!=NULL)
			for(int j =0 ; j <CompList[i]->getOutputPin()->ConnectedNo();j++)
			{
				//filling the vector with x's and y's of the wire and the pins of all possible connections
				Wires.push_back(WireInfo(CompList[i]->getOutputPin()->getPinInfo().x+CompList[i]->getgraphicsinfo().x1,
					CompList[i]->getOutputPin()->getPinInfo().y+CompList[i]->getgraphicsinfo().y1,
					CompList[i]->getOutputPin()->getInputPins()[j]->getPinInfo().x+
					getComponent(CompList[i]->getOutputPin()->getInputPins()[j])->getgraphicsinfo().x1,
					CompList[i]->getOutputPin()->getInputPins()[j]->getPinInfo().y+
					getComponent(CompList[i]->getOutputPin()->getInputPins()[j])->getgraphicsinfo().y1,
					CompList[i]->getOutputPin(),CompList[i]->getOutputPin()->getInputPins()[j]));

				Wires[Wires.size()-1].midx1= (Wires[Wires.size()-1].x1+Wires[Wires.size()-1].x2)/2;
				Wires[Wires.size()-1].midx2= (Wires[Wires.size()-1].x1+Wires[Wires.size()-1].x2)/2;
				Wires[Wires.size()-1].midy1= Wires[Wires.size()-1].y1;
				Wires[Wires.size()-1].midy2= Wires[Wires.size()-1].y2;

				if(Wires[Wires.size()-1].midy2<Wires[Wires.size()-1].midy1)
				{
					int T = Wires[Wires.size()-1].midy2;
					Wires[Wires.size()-1].midy2=Wires[Wires.size()-1].midy1;
					Wires[Wires.size()-1].midy1=T;
				}
			}
	}
	for (unsigned int i = 0 ; i<Wires.size();i++)
	{ //comapres the point click with every wire until found
		if((x>=Wires[i].x1&&x<=Wires[i].midx1&&y<=(Wires[i].y1+2)&&y>=(Wires[i].y1-2) )||
			(y>=Wires[i].midy1&&y<=Wires[i].midy2&&x<=(Wires[i].midx1+2)&&x>=(Wires[i].midx2-2) )||
			(x>=Wires[i].midx2&&x<=Wires[i].x2&&y<=(Wires[i].y2+2)&&y>=(Wires[i].y2-2) ))
		{
			Out=Wires[i].O;
			In=Wires[i].I;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::DrawLine(int x1,int y1 ,int x2,int y2,const color rcolor)
{
	O->DrawLine( x1, y1 , x2, y2,rcolor);
}