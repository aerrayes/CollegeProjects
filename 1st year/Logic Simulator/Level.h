#pragma once
class ApplicationManager;
#include "Component.h"
#include <vector>
class Level
{
	/*enum { MaxCompCount = 200 };
	Component* Comps[MaxCompCount];*/
	enum {MaxLevels = 20 };
	int Levels[MaxLevels];
	
	
public:
	Level(void);
	~Level(void);
	
	void Update(ApplicationManager* rA);
	void recursion(int Level,Component* Left,int i,ApplicationManager * rA);
	void UpdateList(ApplicationManager*A);
	//vector<Component*> GetCompSorted(){return ComponentSorted;};
	vector<Component*> ComponentSorted;
	int* getLevels(){return Levels;};
	int getMaxLevels();
};
