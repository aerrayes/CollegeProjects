#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

/*class OutputPin 
  ---------------
 An output obtains a value as a result of calculating the outputs of
 a component. The output pin propagates its value immediately to the
*/

#include "InputPin.h"

class OutputPin: public Pin	//inherited from class Pin
{
private:
	//Array of Input Pins (poniters) to be connected to that OutputPin
	//For simplicity, we consider it a constant length
	InputPin* m_InputPins[MAX_PINS];	
	
	int m_FanOut;	//Maximum No. of input pins connected to that output pin (depends on the component)
	int m_ConnInputs;		//Actual No. of input pins connected to that output pin
public:
	OutputPin(int r_FanOut,const PinInfo &P);	
	OutputPin();
	void sync();
	bool ConnectTo(InputPin* r_InputPin);	//connect to a new input pin
	bool Disconnect(InputPin* r_InputPin);
	int ConnectedNo(){return m_ConnInputs;};
	InputPin** getInputPins(){return m_InputPins;};
	bool IsConnected(InputPin* Pin);
};

#endif