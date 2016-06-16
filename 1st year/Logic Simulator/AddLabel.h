#pragma once
#include "Action.h"
#include "Component.h"


class AddLabel : public Action
{
	int Cx, Cy;	//Center point of the gate
	string S;
	Component *C;
public:
	AddLabel(void);
	virtual ~AddLabel(void);

	virtual void ReadActionParameters(ApplicationManager *pManager);
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager);
	virtual void Undo(ApplicationManager *pManager);
	virtual void Redo(ApplicationManager*pManager);

};

