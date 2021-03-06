#pragma once
#include "Action.h"
#include "Xor2.h"

class AddXORgate2 :public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	Component* Comp;
public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager); //reads the point the user clicked
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager); //adds the component to component list at the point the user clicked
	virtual void Undo(ApplicationManager *pManager); //removes component from component List 
	virtual void Redo(ApplicationManager*pManager); //adds it again to component list

	static  void Load(int,int Level_no,int x,int y,string Label,ApplicationManager *pManager); //loads the component by adding to component list
	AddXORgate2(void);
	virtual ~AddXORgate2(void);
};

