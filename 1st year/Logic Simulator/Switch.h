#ifndef _Switch_H
#define _Switch_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "Component.h"
#include "OutputPin.h"

//#include "Output.h"
//#include "ApplicationManager.h"
class ApplicationManager;
class Switch:public Component
{
	bool ON;
	OutputPin m_OutputPin;
public:
	Switch(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	//parameter was sent here that cause it to fail
	virtual void Draw(ApplicationManager *pManager);	//Draws 2-input gate
	virtual OutputPin *getOutputPin(){return &m_OutputPin;};
	virtual InputPin * getInputPin(){return NULL;};
	virtual int getInputs(){return 0;};
	virtual void change_graphic(int x,int y);
	virtual GraphicsInfo getgraphicsinfo(){return m_GfxInfo;};
	//void change_image(int x,int y);
	//virtual int getLevel(){return Level;};
	virtual void setLevel(int rLevel){/*Level=rLevel;*/};
	virtual void DrawConnections(ApplicationManager*A);
	virtual void SaveComponent(int i,ApplicationManager *pManager);
	virtual CompInfo getCompSave();
	virtual string getComp_Type();
	bool getONOFF(){return ON;};
	void setONOFF(bool _ON){ON=_ON;}
	//virtual bool ConnectTo(InputPin*rInput){return false;};
	~Switch();
};

#endif