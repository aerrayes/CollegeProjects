#pragma once
#include "Action.h"
#include "Component.h"

class Selection:public Action
{
private:
	Component *C;
	int Cx, Cy;
public:
	Selection(void);
	virtual ~Selection(void);
	virtual void ReadActionParameters(ApplicationManager *pManager);
	virtual void Execute(ApplicationManager *pManager);
	virtual void Undo(ApplicationManager *pManager){};
	virtual void Redo(ApplicationManager *pManager){};
};

