#ifndef _DELET_H
#define _DELET_H

#include "action.h"
//#include "AND2.h"
#include "Component.h"
#include "Connect.h"
class Delete :public Action
{
private:
	enum{FIXED = 5};
	Component *pComp;
	OutputPin* Left[FIXED];
	InputPin* Right[FIXED];

public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	//Execute action (code depends on action type)
	virtual void Draw_Connect(ApplicationManager *pManager){};
	virtual void Execute(ApplicationManager *pManager);
	virtual void change_connection(Component *c){};
	virtual void Undo(ApplicationManager *pManager);
	virtual void Redo(ApplicationManager *pManager);
	Delete(void);
	virtual ~Delete(void);
};

#endif