#include "OutputPin.h"

OutputPin::OutputPin(int r_FanOut,const PinInfo &rPInfo):Pin(rPInfo)
{
	m_ConnInputs = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_PINS ? MAX_PINS: r_FanOut;	//set the fan out of the pin.

}
OutputPin::OutputPin() : Pin(PinInfo(0,0))
{
	m_ConnInputs = 0;
	m_FanOut=5;
}
//Functionn ConnectTo:
//Connects the ouput pin the the passed input pin if the fan out permits
//if the no. of connected pin is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(InputPin *r_InputPin)
{
	if(m_ConnInputs < m_FanOut)
	{
		m_InputPins[m_ConnInputs] = r_InputPin;	//add a new pin the the array of pins
		m_ConnInputs++;		//increase no. of connected pins
		r_InputPin->setConnected(true);
		return true;
	}
	
	return false;	//can't connect to any more input pins
}

void OutputPin::sync()
{
	for(int i =0 ; i<m_ConnInputs ; i++)
	{
		m_InputPins[i]->setStatus(getStatus());
	}
}

bool OutputPin::Disconnect(InputPin* r_InputPin)
{
	for (int i = 0 ; i < m_ConnInputs ; i++)
	{
		if (m_InputPins[i] == r_InputPin)
		{
			m_InputPins[i] = m_InputPins[--m_ConnInputs];
			m_InputPins[m_ConnInputs] = NULL;
			r_InputPin->setConnected(false);
			return true;
		}
	}
	return false;
}

bool OutputPin::IsConnected(InputPin* Pin)
{
	for (int i =0;i<m_ConnInputs;i++)
		if(Pin==m_InputPins[i])
			return true;
	return false;
}