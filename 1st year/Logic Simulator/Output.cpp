#include "Output.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include <string>

Output::Output()
{
	pDrawingWindow = new window(1024,798,0,0);
	pDrawingWindow->ChangeTitle("Logic Simulator");
	pDrawingWindow->DrawImage("InterFace\\Interface.jpg",0,0);
	MgX = 80;
	MgY = 35;
	pwindow = NULL;
	//double dRed,dGreen,dBlue;
	//pDrawingWindow->GetColor(512, 384, dRed, dGreen, dBlue);
	//pDrawingWindow->SetBrush(dRed,dGreen,dBlue);
	//pDrawingWindow->SetPen(dRed,dGreen,dBlue);
	//pDrawingWindow->DrawRectangle(0,0,pDrawingWindow->GetWidth(),pDrawingWindow->GetHeight());
	//pDrawingWindow->DrawImage("InterFace\\Interface.jpg",0,0);
	//pDrawingWindow = new window(750, 600, 0, 0);
	//pDrawingWindow->ChangeTitle("Programming Techniques Project");
	//pDrawingWindow->SetPen(RED , 0.5);
	//pDrawingWindow->SetBrush(LAVENDERBLUSH);
	//pDrawingWindow-> DrawRectangle(0,0, 746,30, FILLED,20,20);
	//pDrawingWindow->DrawLine(10, 30, pDrawingWindow->GetWidth()-10, 30);
	//pDrawingWindow->SetPen(HOTPINK, 3);
	//pDrawingWindow->DrawLine(0, pDrawingWindow->GetHeight()-50, pDrawingWindow->GetWidth(), pDrawingWindow->GetHeight()-50);
	//pDrawingWindow->SetPen(RED , 0.5);
	//pDrawingWindow->DrawLine( 70, 0,70, 30);
	//pDrawingWindow->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	//pDrawingWindow->DrawString(15, 10, "Gates");
	//pDrawingWindow->DrawLine(140, 0,140, 30);
	//pDrawingWindow->DrawString(75, 10, "setting");
}

Input* Output::CreateInput()
{
	Input* pIn = new Input(pDrawingWindow);
	return pIn;
}
//
//void Output::ChangeTitle(string Title)
//{
//	pDrawingWindow->ChangeTitle(Title);
//}

Output::~Output()
{
	delete pDrawingWindow;
}

void Output::DrawComp(int x,int y,image *I)
{
	pDrawingWindow->DrawImage(I,x,y);
}

void Output::PrintMessage(string S)
{	
	int MsgX = 160;
	int MsgY = 670/*pDrawingWindow->GetHeight() - 35*/;
	pDrawingWindow->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");   
	pDrawingWindow->SetPen(BLUE); 
	pDrawingWindow->DrawString(MsgX, MsgY, S);
}

void Output::ClearStatesBar()
{ //to be removed and replaced with draw window
	pDrawingWindow->SetPen(WHITE);
	pDrawingWindow->SetBrush(WHITE);
	pDrawingWindow->DrawRectangle(140,630,910,700);
	//Draw_new_Window();
}
void Output::DrawLine(int x1,int y1,int x2, int y2)
{
	pDrawingWindow->SetPen(BLACK,2);
	int X;
	X=(x2-x1)/2;
	pDrawingWindow->DrawLine(x1,y1,x1+X,y1);
	pDrawingWindow->DrawLine(x1+X,y1,x1+X,y2);
	pDrawingWindow->DrawLine(x1+X,y2,x2,y2);

}
void Output::DrawLine(int x1,int y1,int x2, int y2,const color rcolor)
{
	pDrawingWindow->SetPen(rcolor,2);
	int X;
	X=(x2-x1)/2;
	pDrawingWindow->DrawLine(x1,y1,x1+X,y1);
	pDrawingWindow->DrawLine(x1+X,y1,x1+X,y2);
	pDrawingWindow->DrawLine(x1+X,y2,x2,y2);

}
bool Output::SetBuffering(const bool bSetting){
	return pDrawingWindow->SetBuffering(bSetting);
}
////////////////////////////////////////////////////////////////////////////////
void Output::UpdateBuffer(){
	pDrawingWindow->UpdateBuffer();
}
//////////////////////////////////////////////////////////////////////////////

void Output::Draw_new_Window()
{
	
	pDrawingWindow->DrawImage("InterFace\\Interface.jpg",0,0);
	/*init();
	DrawswitchSetting();*/
}


void Output::DrawAddrBar(string S)
{
	int MsgX = 550;
	int MsgY = 670;
	pDrawingWindow->SetFont(16, BOLD | ITALICIZED, BY_NAME, "Arial");   
	pDrawingWindow->SetPen(BLUE); 
	pDrawingWindow->DrawString(MsgX, MsgY, S);
}

void Output::ClearAddrBar()
{
	pDrawingWindow->SetPen(WHITE);
	pDrawingWindow->SetBrush(WHITE);
	pDrawingWindow->DrawRectangle(545,640,910,700);
}

void Output::Draw_TRUTH_TABLE(int i,int j)
{
	window *pwindow=new window(500,500,1024,0);
	setwindow(pwindow);
	get_new_window()->SetPen(BLACK,2);
	get_new_window()->DrawLine(75,30,75+((i+j)*55),30);
	get_new_window()->DrawLine(75,60,75+((i+j)*55),60);
	get_new_window()->DrawLine(75,30,75,60+((int)pow((double)2,(double)i)*30));
	for(int u=1;u<=i+j;u++)
	{
		for(int d=1;d<=(int)pow((double)2,(double)i);d++)
		{
			get_new_window()->DrawLine(75,60+(d*30),75+(u*55),60+(d*30));
			get_new_window()->DrawLine(75+(u*55),30,75+(u*55),60+(d*30));
		}
	}  
}

void Output::setwindow(window *pwindow)
{
	this->pwindow=pwindow;
}

void Output::print_msg_in_truthtable(int i,int j,string s)
{
	int Mgx=MgX+(j*55);
	int Mgy=MgY+(i*30);
	get_new_window()->SetFont(14, BOLD | ITALICIZED, BY_NAME, "Arial");
	get_new_window()->SetPen(BLUE); 
	get_new_window()->DrawString(Mgx, Mgy, s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
window *Output::get_new_window()
{
	return pwindow;
}

void Output::deletewindow()
{
	delete pwindow;
	pwindow = NULL;
}
void Output::Draw_new_window_sim()
{
	pDrawingWindow->DrawImage("InterFace\\Interface Sim.jpg",0,0);
}