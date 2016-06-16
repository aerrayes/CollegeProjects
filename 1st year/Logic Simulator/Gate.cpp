#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut,pair<int,int>out,pair<int,int>in1,pair<int,int>in2,pair<int,int>in3):m_OutputPin(r_FanOut,PinInfo(out.first,out.second))
{

	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	for(int i = 0 ; i <r_Inputs ; i++)
	{
		switch(i)
		{
			case 0: m_InputPins[i].setPinInfo(PinInfo(in1.first,in1.second)); break;
			case 1: m_InputPins[i].setPinInfo(PinInfo(in2.first,in2.second)); break;
			case 2: m_InputPins[i].setPinInfo(PinInfo(in3.first,in3.second)); break;
		}
	}
				m_Inputs = r_Inputs;	//set no. of inputs of that gate
				m_Label="-";
}

Gate::~Gate()
{
	delete [] m_InputPins;
}