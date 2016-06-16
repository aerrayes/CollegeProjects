#ifndef _AND2_H
#define _AND2_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"

class AND2:public Gate
{
public:
	AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(ApplicationManager* );	//Draws 2-input gate
	virtual void DrawConnections(ApplicationManager*A);
	virtual OutputPin *getOutputPin(){return &m_OutputPin;};
	//virtual int getLevel(){return Level;};
	virtual void setLevel(int rLevel){Level=rLevel;};
	virtual InputPin* getInputPin(){return m_InputPins;};
	virtual int getInputs(){return m_Inputs;};
	virtual void change_graphic(int x,int y);
	virtual void SaveComponent(int i,ApplicationManager *pManager);
	virtual CompInfo getCompSave();
	virtual string getComp_Type();

};

#endif