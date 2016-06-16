#ifndef _ACTION_H
#define _ACTION_H

#include "CMUgraphicsLib\CMUgraphics.h"
class ApplicationManager; //forward class declaration


//Base class for all possible actions (abstract class)
class Action
{
public:
	//Reads parameters required for action to execute
	virtual void ReadActionParameters(ApplicationManager *pManager)=0;
	
	//Execute action (code depends on action type)
	virtual void Execute(ApplicationManager *pManager)=0;

	virtual void Undo(ApplicationManager *pManager)=0;

	virtual void Redo(ApplicationManager *pManager)=0;
};

#endif