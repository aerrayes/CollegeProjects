
#include "action.h"
#include"Component.h"
#include"Switch.h"
#include"Led.h"
#include"ApplicationManager.h"

class TruthTable :
	public Action
{
	int Cx,Cy;
	int No_of_combinations;
	int No_of_switches;
	int No_of_leds;
	string **table_inputs;
	string **table_out;
	Component *l[5];//used to make array of leds
	ApplicationManager *A;
	Level *Levels;
	STATUS m_Status[5];
public:
	void ReadActionParameters(ApplicationManager *pManager);
	/*
	get number of switches & get number of leds then generate the combinations based on no of switches
	and no of leds then  assign values of table_inputs to switches
	*/
	void Execute(ApplicationManager *pManager);
	virtual void Undo(ApplicationManager *pManager){};
	virtual void Redo(ApplicationManager *pManager){};
	TruthTable(void);
	~TruthTable(void);
	//void Assign_values();
	//void Generate_input_Combinations(int);
	//int No_switches(Component**);
	//int No_leds(Component**);

};
