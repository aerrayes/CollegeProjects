#pragma once
#include "action.h"
#include "Component.h"
class Connect :
	public Action
{
	Component *pComp1,*pComp2;
	int InputConn;
public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);
	virtual void Undo(ApplicationManager *pManager);
	virtual void Redo(ApplicationManager *pManager);
	Connect(){pComp1=NULL;pComp2=NULL;};
};

