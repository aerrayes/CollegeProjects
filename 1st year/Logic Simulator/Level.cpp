#include "Level.h"
#include "ApplicationManager.h"
#include "InputPin.h"
Level::Level(void)
{
	for (int i=0;i<MaxLevels;i++)
	{
		Levels[i]=0;
	}
}


Level::~Level(void)
{
}

void Level::Update(ApplicationManager* rA)
{
	
	int i=0;
	Component *C;
	for (int x = 0 ; x<rA->GetCompCount();x++)
	{
		rA->getCompNo(C,x);
		if(C->getLevel()!=0) C->setLevel(-1);
	}
	rA->getCompNo(C,i);
	while(C!=NULL)
	{
		if(C->getLevel()==0)
		{
			int Level=0;
			Component* Switch = C;
			recursion(++Level,Switch,i,rA);
			
		}
		i++;
		rA->getCompNo(C,i);
	}
	UpdateList(rA);
	
}
void Level::recursion(int Level,Component* Left,int i,ApplicationManager *rA)
{
	if(Left==NULL)
		return;
	if (Left->getOutputPin()==NULL)
	{
		//if(/*Conn!=NULL &&*/ Left->getLevel()<Level)
		//	Left->setLevel(Level);
		return;
	}
	for (int j = 0; j<Left->getOutputPin()->ConnectedNo();j++)
	{
		Component* Conn=rA->getComponent((Left->getOutputPin()->getInputPins()[j]));
		if(Conn!=NULL && Conn->getLevel()<Level)
			Conn->setLevel(Level);
		recursion(Level+1,Conn,j,rA);
	}
}

void Level::UpdateList(ApplicationManager*rA)
{
	int i=0;
	for(int x = 0 ; x<MaxLevels; x++)
			Levels[x]=0;
	ComponentSorted.clear();
	while (rA->getComponentList()[i]!=NULL)
	{
		Component*Comp;
		rA->getCompNo(Comp,i);
		Levels[Comp->getLevel()]++;
		
		
		if (Comp->getLevel()==0)
		{
			if(ComponentSorted.size()==0)
				ComponentSorted.push_back(Comp);
			else
				ComponentSorted.insert(ComponentSorted.begin()/*+Levels[Comp->getLevel()]-1*/,Comp);
		}
		else
		{
			int sum=0;
			for(int j=0;j<Comp->getLevel();j++)
			{
				sum+=Levels[j];
				
			}
			ComponentSorted.insert(ComponentSorted.begin()+sum,Comp);

		}
		i++;
	}
	if(ComponentSorted.size()!=0 && ComponentSorted[0]->getLevel()!=0)
	{
		for(int x = 0 ; x<MaxLevels; x++)
			Levels[x]=0;
		ComponentSorted.clear();
		for(int i = 0 ; i<rA->GetCompCount(); i++)
		{
			ComponentSorted.push_back(rA->getComponentList()[i]);
			if(ComponentSorted[i]->getInputPin() == NULL)
				Levels[0]++;
			else
				Levels[1]++;

		}
	}
} 
int Level::getMaxLevels()
{
	int Max=0;
	for (int i = 0 ; i<MaxLevels ; i++)
	{
		if(Levels[i]!=0)
			Max++;
	}
	return Max;
}