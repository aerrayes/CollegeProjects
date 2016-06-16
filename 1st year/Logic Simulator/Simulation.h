#pragma once
#include "action.h"
#include "Defs.H"
class Simulation :
	public Action
{
	int x,y;
	ActionType A;
public:
	virtual void ReadActionParameters(ApplicationManager*pManager);
	virtual void Execute(ApplicationManager*pManager);
	virtual void Undo(ApplicationManager*pManager){};
	virtual void Redo(ApplicationManager* pManager){};
};

