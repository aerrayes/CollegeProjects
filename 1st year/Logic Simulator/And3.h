#pragma once
#include "gate.h"

class And3 :
	public Gate
{
public:
	And3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(ApplicationManager*);	//Draws 2-input gate
	virtual void DrawConnections(ApplicationManager*A);
	//virtual OutputPin *getOutputPin(){return &m_OutputPin;};
	virtual int getLevel(){return Level;};
	virtual void setLevel(int rLevel){Level=rLevel;};
	//virtual InputPin* getInputPin(){return m_InputPins;};
	//virtual int getInputs(){return m_Inputs;};
	virtual void change_graphic(int x,int y);
	virtual void SaveComponent(int i,ApplicationManager *pManager);
	virtual CompInfo getCompSave();
	virtual string getComp_Type();
};

