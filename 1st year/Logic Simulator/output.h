#pragma once

#include "Input.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include <string>
class Output	//The application manager should have a pointer to this class
{
private:
	window* pDrawingWindow;	//Pointer to the Graphics Window
	window *pwindow;
	int MgX;
	int MgY;
public:
	Output();
	~Output();

	Input* CreateInput(); //creates a pointer to the Input object

	//void ChangeTitle(string Title);
	void DrawComp(int x,int y,image *I);
	void PrintMessage(string msg);	//Print a message on Status bar
	void ClearStatesBar();
	void DrawLine(int x1,int y1,int x2,int y2);
	void DrawLine(int x1,int y1,int x2,int y2,const color);
	void printUserInput();
	//void DrawToolbarSetting();
	//void DrawToolbarGates();
	//void WriteMeg(string s,int x,int y);
	bool SetBuffering(const bool bSetting);
	void UpdateBuffer();
	//void WriteMsg(string s,int x,int y);
	void Draw_new_Window();
	void Draw_new_window_sim();
	void ClearAddrBar();
	void DrawAddrBar(string S);
	void Draw_TRUTH_TABLE(int i,int j);
	window *get_new_window();
	void setwindow(window *pwindow);
	void print_msg_in_truthtable(int i,int j,string s);
	void deletewindow();

};
