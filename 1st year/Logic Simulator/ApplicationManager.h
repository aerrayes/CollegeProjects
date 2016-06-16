//#ifndef APPLICATION_MANAGER_H
//#define APPLICATION_MANAGER_H
//
//#include "Defs.h"
//#include "Action.h"
//#include "Component.h"
//#include "Input.h"
//#include "Output.h"
//#include <string>
//#include <stack>
//#include "Level.h"
////Main class that manages everything in the application.
//class ApplicationManager
//{
//
//	enum { MaxCompCount = 200 };	//Max no of Components
//	enum { MaxFigCount = 200 };	//Max no of figures
//
//private:
//	int CompCount;		//Actual number of Components
//	Component *CompList[MaxCompCount];	//List of all Components (Array of pointers)
//	int NO_of_Saved_files;
//	string Savedfileslist[50];
//	Input* I;
//	Output* O;
//	stack<Action*> ActionList;
//	stack<Action*> RedoList;
//	Level L;
//	int x,y;
//public:
//
//
//public:	
//	ApplicationManager(); //constructor	
//
//	//Reads the required action from the user and returns the corresponding action type
//	ActionType GetUserAction();
//	Level* getLevel(){return &L;};
//	int Getx(){return x;};
//	int Gety(){return y;};
//	//Creates an action and executes it
//	void ExecuteAction(ActionType);
//	Action*get_Undo_Action();
//	Action*get_Redo_Action();
//	void UpdateInterface();	//Redraws all the drawing window
//	int degreeComponent(Component *c);
//	void FlushKeyQueue();
//	void UpdateInterface(int x);
//	void FlushMouseQueue();
//	void Clearwindow(){};
//	buttonstate  GetButtonState(button btMouse, int &iX, int &iY);
//	bool SetBuffering(const bool bSetting);
//	void UpdateBuffer();
//	void Draw_new_Window();
//	//Adds a new component to the list of components
//	void AddComponent(Component *pComp);
//	void RemoveComponent(Component *pComp);
//	bool empty(GraphicsInfo GFx );
//	Component** getComponentList(){return CompList;};
//	Component* FindComp(int x,int y);
//	Component* getComponent();
//	Component* getComponent(InputPin*);
//	int GetCompCount(){return CompCount;};
//	void getCompNo(Component*& comp ,int i); 
//	
//	//Output Functions
//	void PrintMessage(string msg);
//	void ClearStatesBar();
//	void DrawComp(int x,int y,image *I);
//	void WriteAddBar(string S);
//	void ClearAddBar();
//	void DrawLine(int x1,int y1 ,int x2,int y2);
//	void DrawLine(int x1,int y1 ,int x2,int y2,const color);
//	//Input Functions
//	keytype WaitKeyPress(char &cKey);
//	clicktype GetMouseInput(int &x, int &y);
//	string GetString();
//	void Del();
//	void getComponent(int x,int y,Component *Com[2],InputPin* &inp);
//	bool CheckSavedFile(string);
//	void UpdateSavedFilesList(string);
//	void ClearSavedFilesList();
//	void Draw_TRUTH_TABLE(int i,int j);
//	void print_msg_in_truthtable(int i,int j,string s);
//	void getConnections(InputPin*& In,OutputPin *& Out, int x,int y);
//	//destructor
//	~ApplicationManager();
//};
//
//#endif
#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "Action.h"
#include "Component.h"
#include "Input.h"
#include "Output.h"
#include <string>
#include <stack>
#include "Level.h"
//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int CompCount;		//Actual number of Components
	Component *CompList[MaxCompCount];	//List of all Components (Array of pointers)
	int NO_of_Saved_files;		
	string Savedfileslist[50];
	Input* I;
	Output* O;
	stack<Action*> ActionList;
	stack<Action*> RedoList;
	Level L;
	int x,y;
public:


public:	
	ApplicationManager(); //constructor	

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	Level* getLevel(){return &L;};  //returns pointer at level class
	int Getx(){return x;};		//returns x of GetUserAction Function
	int Gety(){return y;};		//returns y of GetUserAction Function
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	Action*get_Undo_Action();
	Action*get_Redo_Action();
	void UpdateInterface();	//Redraws all the drawing window
	int degreeComponent(Component *c);	//returns component id
	void FlushKeyQueue();
	void UpdateInterface(int x);
	void FlushMouseQueue();
	void Clearwindow(){};		
	buttonstate  GetButtonState(button btMouse, int &iX, int &iY);
	bool SetBuffering(const bool bSetting);		//change buffer status
	void UpdateBuffer();
	void Draw_new_Window();		//draw new interface image
	//Adds a new component to the list of components
	void AddComponent(Component *pComp);
	void RemoveComponent(Component *pComp);
	bool empty(GraphicsInfo GFx );		//check if this place is empty or not
	Component** getComponentList(){return CompList;};
	Component* FindComp(int x,int y);	//find component with GrafixInfo
	Component* getComponent();
	Component* getComponent(InputPin*);		//find Component with Inputpin
	int GetCompCount(){return CompCount;};	//returns number of component
	void getCompNo(Component*& comp ,int i); 
	//Output Functions
	void PrintMessage(string msg);		//print msg on statusbar
	void ClearStatesBar();
	void DrawComp(int x,int y,image *I);
	void WriteAddBar(string S);			//print msg on addressbar
	void ClearAddBar();
	void DrawLine(int x1,int y1 ,int x2,int y2);
	void DrawLine(int x1,int y1 ,int x2,int y2,const color);
	//Input Functions
	keytype WaitKeyPress(char &cKey);
	clicktype GetMouseInput(int &x, int &y);
	string GetString();
	void Del();		//delete pointers in application manager
	void getComponent(int x,int y,Component *Com[2],InputPin* &inp);
	bool CheckSavedFile(string);		//check if the file is saved or not
	void UpdateSavedFilesList(string);	//save file in saved list
	void ClearSavedFilesList();
	void Draw_TRUTH_TABLE(int i,int j);		//draw truth tabel in new window
	void print_msg_in_truthtable(int i,int j,string s);		//enter data in truth tabel
	void getConnections(InputPin*& In,OutputPin *& Out, int x,int y);
	//destructor
	~ApplicationManager();
};

#endif