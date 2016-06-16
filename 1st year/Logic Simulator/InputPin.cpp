#include "InputPin.h"

InputPin::InputPin(const PinInfo &rPInfo):Pin(rPInfo)
{
	Connected = false;
}
InputPin::InputPin():Pin(PinInfo(0,0))
{
	Connected=false;
}
bool InputPin::getConnected()
{
	return Connected;
}
void InputPin::setConnected(bool rConnected)
{
	Connected = rConnected;
}