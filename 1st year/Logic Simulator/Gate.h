#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"
#include <utility>
class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the component
	OutputPin m_OutputPin;	//The component output pin
	int m_Inputs;		//No. of input pins of that component.

public:
	Gate(int r_Inputs, int r_FanOut,pair<int,int>out,pair<int,int>in1,pair<int,int>in2=pair<int,int>(0,0),pair<int,int>in3=pair<int,int>(0,0));
	virtual OutputPin* getOutputPin(){return &m_OutputPin;};
	virtual InputPin * getInputPin(){return m_InputPins;};
	virtual int getInputs(){return m_Inputs;};
	bool ConnectTo(InputPin *r_InputPin){return m_OutputPin.ConnectTo(r_InputPin);};
	virtual void setONOFF(bool){};
	virtual bool getONOFF(){return false;};
	virtual ~Gate();
};

#endif
