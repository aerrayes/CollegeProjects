#include "TruthTable.h"
#include<cmath>
#include<string>
#include <fstream>

TruthTable::TruthTable(void)
{
}


TruthTable::~TruthTable(void)
{
}

void TruthTable ::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("you click Truth Table button");
}

void TruthTable::Execute(ApplicationManager *pManager)
{

	pManager->getComponentList();
	int max=0;  // initial no of switches//
	int n=0; //counter
	for(int i=0;i<pManager->GetCompCount();i++)
	{
		if(pManager->getComponentList()[i]->getLevel()==0) // search for switches//
		{
			max++;
			m_Status[n]=pManager->getComponentList()[i]->getOutputPin()->getStatus();
			n++;
		}
	}
	No_of_switches=max;


	///////////////////////////////////////////////////////////////////////////////////////////////

	//leds searching
	int leds=0; // initial no of leds
	for(int j=0;j<pManager->GetCompCount();j++)
	{
		if(pManager->getComponentList()[j]->getOutputPin()==NULL) // check wether the component have output or nt //
		{
			l[leds]=pManager->getComponentList()[j];
			leds++;
		}
	}
	No_of_leds=leds;// creating array for leds only//

	///////////////////////////////////////////////////////////////////////////////////////////////

	//generating combinations
	int Z =(int)pow((double)2,(double)No_of_switches); // number of rows//
	No_of_combinations=Z;
	table_inputs=new string *[Z];// creating two -dimension dynamic array //
	for(int y=0;y<Z;y++)
	{
		table_inputs[y]= new string [No_of_switches];
		if(y==0)
		{
			for(int x=0;x<No_of_switches;x++)
				table_inputs[y][x]="L";
		}
	}
	int u=0;
	for(int x=0;x<No_of_switches;x++)
	{
		int m;
		u=0;
		if(x==0)
			m=0;
		else m=1;
		while(m<Z)
		{
			//if (x!=0)
			for(int y=0;y<(int)pow((double)2,(double)x)-1;y++)
			{
				if((m+1)!=u&&m!=0)
					table_inputs[m][x]=table_inputs[m-1][x];
				m++;
			}
			if(x==0)
			{
				if(table_inputs[m][x]=="L")
				{
					u=m+1;
					if(u<Z)
						table_inputs[m+1][x]="H";

				}
				else if(table_inputs[m][x]=="H")
				{
					u=m+1;

					if(u<Z)
						table_inputs[m+1][x]="L";
				}}
			else if(m%2!=1){
				m--;
				if(table_inputs[m][x]=="L")
				{
					u=m+1;

					if(u<Z)
						table_inputs[m+1][x]="H";
					m++;
				}
				else if(table_inputs[m][x]=="H")
				{
					u=m+1;
					if(u<Z)
						table_inputs[m+1][x]="L";
					m++;
				}
			}
			m++;

		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////

	// create table_out (array of output of leds)

	table_out=new string *[Z];
	//for(int r=0;r<leds;r++)
	for(int q=0;q<Z;q++)
	{
		table_out[q]=new string [No_of_leds];
	}

	// assign values to switches not complete 
	//ofstream yourfile;
	//yourfile.open("truthtable.txt");
	Levels=pManager->getLevel();
	for(int M=0;M<No_of_combinations;M++)
	{
		for(int u=0;u<No_of_switches;u++) 
		{
			if(table_inputs[M][u]=="L") // will set the switch values 
			{
				//s[u]->getOutputPin()->setStatus(LOW);
				Levels->ComponentSorted[u]->getOutputPin()->setStatus(LOW);
			}
			else
			{
				//s[u]->getOutputPin()->setStatus(HIGH);
				Levels->ComponentSorted[u]->getOutputPin()->setStatus(HIGH);
			}
		}
		for(unsigned int i=0;i<Levels->ComponentSorted.size();i++)
		{
			if(Levels->ComponentSorted[i]->getLevel()==0)
			{
				Levels->ComponentSorted[i]->getOutputPin()->sync();
			}
			else if(Levels->ComponentSorted[i]->getOutputPin()!=NULL)
			{
				Levels->ComponentSorted[i]->Operate();
				Levels->ComponentSorted[i]->getOutputPin()->sync();
			} 
			else
			{
				for(int i=0;i<leds;i++)
				{
					if(l[i]->getInputPin()->getStatus() == HIGH)
						table_out[M][i]="H";
					else 
						table_out[M][i]="L";
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	if(No_of_switches < 5)
	{
		pManager->Draw_TRUTH_TABLE(No_of_switches,leds);
		for(int M=0;M<No_of_combinations;M++)
		{
			for(int u=0;u<No_of_switches;u++)
			{
				if(M==0)
					pManager->print_msg_in_truthtable(M,u,Levels->ComponentSorted[u]->getComp_Type());
				pManager->print_msg_in_truthtable(M+1,u,table_inputs[M][u]);
			}
			for(int i=0;i<leds;i++)
			{
				if(M==0)
					pManager->print_msg_in_truthtable(M,No_of_switches+i,l[i]->getComp_Type());
				pManager->print_msg_in_truthtable(M+1,No_of_switches+i,table_out[M][i]);
			}
		}
	}
	else
	{
		ofstream out("Truth Tabel\\TruthTabel.txt");
		for(int u=0;u<No_of_switches;u++)
		{
			out<<Levels->ComponentSorted[u]->getComp_Type()<<"     ";
		}
		for(int i=0;i<leds;i++)
		{
			out<<l[i]->getComp_Type()<<"       ";
		}
		for(int M=0;M<No_of_combinations;M++)
		{
			out<<"\n";
			for(int u=0;u<No_of_switches;u++)
			{
				out<<table_inputs[M][u]<<"\t    ";
			}
			for(int i=0;i<leds;i++)
			{
				out<<table_out[M][i]<<"\t    ";
			}
		}
	}
	for(unsigned int i=0;i<pManager->getLevel()->ComponentSorted.size();i++)
	{
		if(pManager->getLevel()->ComponentSorted[i]->getInputPin() == NULL)
			pManager->getLevel()->ComponentSorted[i]->setONOFF(false);
		if(pManager->getLevel()->ComponentSorted[i]->getOutputPin() == NULL)
			pManager->getLevel()->ComponentSorted[i]->getInputPin()->setStatus(LOW);
	}
}
