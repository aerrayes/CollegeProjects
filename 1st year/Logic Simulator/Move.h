#pragma once
#include "action.h"
#include "Component.h"
class Move :
	public Action
{
	Component *pComp1;
	GraphicsInfo Before;
	GraphicsInfo After;
	int Cx,Cy;
	clicktype k;
	public:

	virtual void ReadActionParameters(ApplicationManager *pManager);
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);

	virtual void Undo(ApplicationManager *pManager);
	virtual void Redo(ApplicationManager *pManager);
};