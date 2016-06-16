#ifndef _LED_H
#define _LED_H

#include "Component.h"
#include "InputPin.h"
//#include "ApplicationManager.h"
class ApplicationManager;
class Led:public Component
{
	InputPin m_InputPin;
public:
	Led(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	
	virtual void Draw(ApplicationManager *pManager);	
	virtual OutputPin *getOutputPin(){return NULL;};
	virtual InputPin * getInputPin(){return &m_InputPin;};
	virtual int getInputs(){return 1;};
	virtual void change_graphic(int x,int y);
	virtual GraphicsInfo getgraphicsinfo(){return m_GfxInfo;};
	virtual void setLevel(int rLevel){Level=rLevel;};
	virtual void DrawConnections(ApplicationManager*A){};
	virtual void SaveComponent(int i,ApplicationManager *pManager);
	virtual CompInfo getCompSave();
	virtual string getComp_Type();
	virtual void setONOFF(bool){};
	virtual bool getONOFF(){return false;};
	~Led();
};

#endif