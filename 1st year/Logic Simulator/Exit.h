#ifndef _ADD_EXIT_H
#define _ADD_EXIT_H

#include "action.h"
//#include "AND2.h"
#include "Component.h"
class Exit :public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	//AND2 *pA;
public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);
	//virtual void change_connection(Component *c){};
	//virtual void Draw_Connect(ApplicationManager *pManager){};
	virtual void Undo(ApplicationManager *pManager);
	virtual void Redo(ApplicationManager *pManager);
	Exit(void);
	virtual ~Exit(void);
};

#endif