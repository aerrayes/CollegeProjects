#ifndef _PIN_H
#define _PIN_H

#include "Defs.h"

class Pin
{
protected:
	STATUS m_Status;	//Status of the Pin
	PinInfo PInfo;
public:
	Pin(const PinInfo&rPInfo);
	void setStatus(STATUS r_Status);
	STATUS getStatus();
	PinInfo getPinInfo(){return PInfo;};
};

#endif