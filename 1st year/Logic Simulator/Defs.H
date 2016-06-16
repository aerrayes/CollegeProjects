#ifndef CONST_H
#define CONST_H
#include "CMUgraphicsLib\image.h"
//#include "OutputPin.h"
//#include "InputPin.h"
class OutputPin;
class InputPin;
//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD_AND_GATE_2,	//Add 2-input AND gate
	ADD_AND_GATE_3,
	ADD_OR_GATE_2,
	ADD_XOR_GATE_2,
	ADD_XOR_GATE_3,
	ADD_BUFFER_GATE,
	ADD_NOT_GATE,
	ADD_NOR_GATE_2,
	ADD_NOR_GATE_3,
	ADD_NAND_GATE_2,
	ADD_XNOR_GATE_2,
	ADD_SWITCH,
	ADD_LED,
	CONNECT,
	MOVE,
	UNDO,
	REDO,
	EXIT,
	INVALID,
	SIMULATION,
	TRUTHTABLE,
	SAVE,
	LOAD,
	DEL,
	SELECT,
	LABEL,
	CANCEL
};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

//Maximum number of input pins that can be connected to any output pin
#define MAX_PINS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5,	//Fan out of 2-input AND gate
	OR2_FANOUT = 5,
	Xor3_FANOUT = 5,
	Xor2_FANOUT = 5,
	XNOR2_FANOUT = 5,
	Not_FANOUT = 5,
	Nor3_FANOUT = 5,
	Nor2_FANOUT = 5,
	NAND2_FANOUT = 5,
	Buffer_FANOUT = 5,
	AND3_FANOUT = 5,
	SWITCH_FANOUT =5
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1,y1, x2, y2;
	image* IMG;
	image* IMGsel;
};
//this structure contains the fixed point of a pin in the image of any component

struct PinInfo
{
	PinInfo(int rx=0,int ry=0){x=rx;y=ry;};
	int x,y;
};
struct CompInfo
{
	int id;
	string compType;
	string compName;
	int x;
	int y;
	int id2;
	int pin_id;
};
struct WireInfo
{
	WireInfo(int _x1 ,int _y1,int _x25,int _y2,OutputPin* rO,InputPin* rI)
	{
		x1=_x1;y1=_y1;x2=_x25;y2=_y2;
		O=rO;I=rI;
	};
	WireInfo(){};
	int x1,x2,y1,y2;
	int midx1,midx2,midy1,midy2;
	OutputPin* O;
	InputPin* I;
};
#endif