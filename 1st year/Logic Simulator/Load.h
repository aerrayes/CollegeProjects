#pragma once
#include "Action.h"
#include <string>

class Load:public Action
{
private:
	string S;
public:
	Load(void);
	virtual ~Load(void);
	virtual void ReadActionParameters(ApplicationManager *pManager);
	virtual void Execute(ApplicationManager *pManager);
	virtual void Undo(ApplicationManager *pManager){};
	virtual void Redo(ApplicationManager *pManager){};
};

