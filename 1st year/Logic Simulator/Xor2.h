#pragma once

#include "Gate.h"

class Xor2 :public Gate
{
public:
	Xor2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();
	virtual void Draw(ApplicationManager *A);
	virtual void DrawConnections(ApplicationManager*A);
	virtual OutputPin *getOutputPin(){return &m_OutputPin;};
	virtual int getLevel(){return Level;};
	virtual void setLevel(int rLevel){Level=rLevel;};
	virtual InputPin* getInputPin(){return m_InputPins;};
	virtual int getInputs(){return m_Inputs;};
	virtual void change_graphic(int x,int y);
	virtual void SaveComponent(int i,ApplicationManager *pManager);
	virtual CompInfo getCompSave();
	virtual string getComp_Type();
};

