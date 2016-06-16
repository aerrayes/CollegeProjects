#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "action.h"
#include "Led.h"

class AddLed :	public Action
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
	AddLed(void);
	virtual ~AddLed(void);
};

#endif