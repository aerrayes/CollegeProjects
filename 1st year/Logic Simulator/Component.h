#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Defs.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "InputPin.h"
#include "OutputPin.h"
class ApplicationManager;
#include "Defs.H"
#include <string>
//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	//char* m_Label;
protected:
	bool simulation;
	CompInfo COMPS;
	string m_Label;
	GraphicsInfo m_GfxInfo;
	bool Mark;
		//The parameters required to draw a component
	int Level;
public:
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(ApplicationManager *A) = 0;	//for each component to Draw itself
	virtual  OutputPin *getOutputPin()=0;
	virtual  InputPin * getInputPin()=0;
	virtual int getInputs()=0;
	GraphicsInfo getgraphicsinfo(){return m_GfxInfo;};
	virtual void DrawConnections(ApplicationManager *)=0;
	int getLevel(){return Level;};
	virtual void setLevel(int)=0;
	void SetMark(bool rMark){Mark=rMark;};
	virtual void change_graphic(int x,int y)=0;
	void setString(string s){m_Label=s;};
	string getString () {return m_Label;};
	virtual void SaveComponent(int i,ApplicationManager *pManager)=0;
	virtual CompInfo getCompSave()=0;
	virtual string getComp_Type()=0;
	virtual void setONOFF(bool)=0;
	virtual bool getONOFF()=0;
	virtual void SetID(int ID){COMPS.id = ID;};
	void setSimulation(bool rSim){simulation=rSim;};
	bool getSimulation(){return simulation;};
	Component(){simulation=false;};	
	//virtual ~Component();
};

#endif
