#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"

class InputPin: public Pin	//inherited from class Pin
{
	bool Connected;
public:
	InputPin(const PinInfo &PInfo);
	InputPin();
	bool getConnected();
	void setConnected(bool);
	void setPinInfo(const PinInfo &rPInfo){PInfo=rPInfo;};
};

#endif