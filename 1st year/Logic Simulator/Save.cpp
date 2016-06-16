#include <fstream>
#include <string>
#include "Save.h"
#include "ApplicationManager.h"
#include "Level.h"
#include <algorithm>
//#include "AND2.h"
Save::Save(void)
{
}

Save::~Save(void)
{
}

void Save::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("Enter the file name you want to save");
	S = pManager->GetString();
	S = "Saved Files\\"+ S +".txt";
	pManager->ClearStatesBar();
}

void Save::Execute(ApplicationManager *pManager)
{
	while(1)
	{
		ReadActionParameters(pManager);
		if(!pManager->CheckSavedFile(S))
		{
			pManager->UpdateSavedFilesList(S);
			//int /*Number_of_Circuit_Levels,*/Number_of_Level_Components[20];
			Levels=pManager->getLevel();
			Number_of_Circuit_Levels=Levels->getMaxLevels();
			if(Number_of_Circuit_Levels != 0 && Number_of_Circuit_Levels != 1 && Number_of_Circuit_Levels != 2)
			{
			for ( int i =0 ; i <pManager->GetCompCount();i++)
			{
				Component* C;
				pManager->getCompNo(C,i);
				C->SaveComponent(i,pManager);
			}
			/*Levels->Update(pManager);
			Levels->UpdateList(pManager);*/
			ofstream yourfile;
			yourfile.open(S);
			yourfile<<Number_of_Circuit_Levels<<endl;
			unsigned int x=0;
			for(int i=0;i<Number_of_Circuit_Levels;i++)
			{
				/*Number_of_Level_Components[i]=0;
				for(int j=0;j<pManager->GetCompCount();j++)
				{
					if(pManager->getComponentList()[j]->SaveComponent(i,pManager)==true)
					Number_of_Level_Components[i]++;
				}*/
				yourfile<</*Number_of_Level_Components*/Levels->getLevels()[i]<<endl;	
				while(x<Levels->ComponentSorted.size()&&Levels->ComponentSorted[x]->getLevel() == i)
				{
					yourfile<<Levels->ComponentSorted[x]->getCompSave().compType<<"\t"<<Levels->ComponentSorted[x]->getCompSave().id
							<<"\t"<<Levels->ComponentSorted[x]->getCompSave().compName
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().x1+Levels->ComponentSorted[x]->getgraphicsinfo().x2)/2
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().y1+Levels->ComponentSorted[x]->getgraphicsinfo().y2)/2<<endl;
					x++;
				}
				/*for(int j=0;j<Number_of_Level_Components[i];j++)
				{
					for(int y=0;y<pManager->GetCompCount();y++)
					{
						if(pManager->getComponentList()[y]->SaveComponent(i,pManager)==true)
						{
							yourfile<<pManager->getComponentList()[j]->getCompSave().compType<<"\t"<<pManager->getComponentList()[j]->getCompSave().id<<"\t";
							yourfile<<pManager->getComponentList()[j]->getCompSave().compName<<"\t"<<pManager->getComponentList()[j]->getCompSave().x<<"\t";
							yourfile<<pManager->getComponentList()[j]->getCompSave().y<<endl;
						}
					}
				}*/
			}
			yourfile<<"Connections"<<endl;
			/*for(int i=0;i<Number_of_Circuit_Levels;i++)
			{
				for(int j=0;j<pManager->GetCompCount();j++)
				{
					if(pManager->getComponentList()[j]->SaveComponent(i,pManager)==true)
					{
						yourfile<<pManager->getComponentList()[j]->getCompSave().id<<"\t"<<pManager->getComponentList()[j]->getCompSave().id2<<"\t";
						yourfile<<pManager->getComponentList()[j]->getCompSave().pin_id<<endl;
					}
				}
			}*/
			for(int i=0;i<Number_of_Circuit_Levels;i++)
			{
				for(int j=0;j<pManager->GetCompCount();j++)
				{
					Component * C;
					pManager->getCompNo(C,j);
					if(C->getLevel()==i&& C->getOutputPin()!=NULL)
					{
						for (int count =0 ; count<C->getOutputPin()->ConnectedNo();count++)
						{
							yourfile<<C->getCompSave().id<<'\t' <<pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getCompSave().id<<'\t';
							int pinNo=-1;
							for (int y=0 ; y < pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputs();y++)
								if(C->getOutputPin()->getInputPins()[count]==&pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputPin()[y])
								{pinNo=y;y=pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputs();}
							yourfile<<pinNo+1<<endl;
						}
					}
					/*pManager->getComponentList()[j]->SaveComponent(j,pManager);
					if(pManager->getComponentList()[j]->getLevel()==i)
					{
						for(int z=0 ;z <pManager->getComponentList()[j]->getOutputPin()->ConnectedNo();z++)
						yourfile<<pManager->getComponentList()[j]->getCompSave().id<<"\t"<<pManager->getComponentList()[j]->getCompSave().id2<<"\t"<<pManager->getComponentList()[j]->getCompSave().pin_id<<endl;
					}*/
				}
			}
			yourfile<<"-1";
			//else 
			//{
			//	for (unsigned int i  = 0 ; i < Levels->ComponentSorted.size() ; i++)
			//	{
			//		yourfile<<Levels->ComponentSorted[x]->getCompSave().compType<<"\t"<<Levels->ComponentSorted[x]->getCompSave().id<<"\t";
			//		yourfile<<Levels->ComponentSorted[x]->getCompSave().compName<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().x1+Levels->ComponentSorted[x]->getgraphicsinfo().x2)/2/*Levels->ComponentSorted[x]->getCompSave().x*/<<"\t";
			//		yourfile<<(Levels->ComponentSorted[x]->getgraphicsinfo().y1+Levels->ComponentSorted[x]->getgraphicsinfo().y2)/2<<endl;
			//	}
			//}
			MessageBox(NULL,"Your circuit is saved","Saved",MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
			return;
			}
			else
			{
				Number_of_Circuit_Levels = 2;
				vector<Component*> vec;
			for ( int i =0 ; i <pManager->GetCompCount();i++)
			{
				Component* C ;
				pManager->getCompNo(C,i);
				C->SaveComponent(i,pManager);
			}
			ofstream yourfile;
			yourfile.open(S);
			yourfile<<Number_of_Circuit_Levels<<endl;
			unsigned int x=0;
			/*for(int i=0;i<Number_of_Circuit_Levels;i++)
			{*/
				//yourfile<</*Number_of_Level_Components*/Levels->getLevels()[i]<<endl;	
				for(unsigned int j =0 ; j<pManager->getLevel()->ComponentSorted.size();j++)
				{
					if(pManager->getLevel()->ComponentSorted[j]->getLevel()==0)
					{
						if(!vec.empty())
							vec.insert(vec.begin(),pManager->getLevel()->ComponentSorted[j]);
						else vec.push_back(pManager->getLevel()->ComponentSorted[j]);
						
						/*yourfile<<Levels->ComponentSorted[x]->getCompSave().compType<<"\t"<<Levels->ComponentSorted[x]->getCompSave().id
							<<"\t"<<Levels->ComponentSorted[x]->getCompSave().compName
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().x1+Levels->ComponentSorted[x]->getgraphicsinfo().x2)/2
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().y1+Levels->ComponentSorted[x]->getgraphicsinfo().y2)/2<<endl;
						x++;*/
					}
					else
					{
						vec.push_back(pManager->getLevel()->ComponentSorted[j]);
					}
				}
				//}
				
				/*while(Levels->getLevels()[i] == 0)
				{
					yourfile<<Levels->ComponentSorted[x]->getCompSave().compType<<"\t"<<Levels->ComponentSorted[x]->getCompSave().id
							<<"\t"<<Levels->ComponentSorted[x]->getCompSave().compName
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().x1+Levels->ComponentSorted[x]->getgraphicsinfo().x2)/2
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().y1+Levels->ComponentSorted[x]->getgraphicsinfo().y2)/2<<endl;
					x++;
				}
				while(Levels->getLevels()[i] == 1)
				{
					
					yourfile<<Levels->ComponentSorted[x]->getCompSave().compType<<"\t"<<Levels->ComponentSorted[x]->getCompSave().id
							<<"\t"<<Levels->ComponentSorted[x]->getCompSave().compName
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().x1+Levels->ComponentSorted[x]->getgraphicsinfo().x2)/2
							<<"\t"<<(Levels->ComponentSorted[x]->getgraphicsinfo().y1+Levels->ComponentSorted[x]->getgraphicsinfo().y2)/2<<endl;
					x++;
				}*/
				//}
				int count=0;
				for(unsigned int i = 0 ; i < vec.size();i++)
				{
					if(vec[i]->getLevel()==0)
						count++;
					else break;
				}
				int components = vec.size()-count;
				yourfile<<count<<endl;	
				for(int i = 0 ; i <count ; i++)
				{
						yourfile<<vec[i]->getCompSave().compType<<"\t"<<vec[i]->getCompSave().id
							<<"\t"<<vec[i]->getCompSave().compName
							<<"\t"<<(vec[i]->getgraphicsinfo().x1+vec[i]->getgraphicsinfo().x2)/2
							<<"\t"<<(vec[i]->getgraphicsinfo().y1+vec[i]->getgraphicsinfo().y2)/2<<endl;
				}
				yourfile<<components<<endl;	
				for(int i = count ; i <components+count ; i++)
				{
						yourfile<<vec[i]->getCompSave().compType<<"\t"<<vec[i]->getCompSave().id
							<<"\t"<<vec[i]->getCompSave().compName
							<<"\t"<<(vec[i]->getgraphicsinfo().x1+vec[i]->getgraphicsinfo().x2)/2
							<<"\t"<<(vec[i]->getgraphicsinfo().y1+vec[i]->getgraphicsinfo().y2)/2<<endl;
				}

			yourfile<<"Connections"<<endl;
			for(int i=0;i<Number_of_Circuit_Levels;i++)
			{
				for(int j=0;j<pManager->GetCompCount();j++)
				{
					Component * C;
					pManager->getCompNo(C,j);
					if(C->getLevel()==i&& C->getOutputPin()!=NULL)
					{
						for (int count =0 ; count<C->getOutputPin()->ConnectedNo();count++)
						{
							yourfile<<C->getCompSave().id<<'\t' <<pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getCompSave().id<<'\t';
							int pinNo=-1;
							for (int y=0 ; y < pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputs();y++)
								if(C->getOutputPin()->getInputPins()[count]==&pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputPin()[y])
								{pinNo=y;y=pManager->getComponent(C->getOutputPin()->getInputPins()[count])->getInputs();}
							yourfile<<pinNo+1<<endl;
						}
					}
				}
			}
			yourfile<<"-1";
			MessageBox(NULL,"Your circuit is saved","Saved",MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
			return;
			}
		}
		else if(pManager->CheckSavedFile(S))
		{
			int button;
			button = MessageBox(NULL,"There is file with this name""\n""Do you want to write anothor name?","Saved",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
			switch(button)
			{
			case(6):
				break;
			case(7):
				return;
			}
		}
	}
}
void Save::Undo(ApplicationManager *pManager){}
void Save::Redo(ApplicationManager *pManager){}