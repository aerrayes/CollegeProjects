#include "Buffer.h"
#include "ApplicationManager.h"
#include <utility>

Buffer::Buffer(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut,pair<int,int>(59,18),pair<int,int>(0,18))
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_GfxInfo.IMG = r_GfxInfo.IMG;
	m_GfxInfo.IMGsel=r_GfxInfo.IMGsel;
	Level = -1;
}


void Buffer::Operate()
{
	m_OutputPin.setStatus(m_InputPins[0].getStatus());
}


// Function Draw
// Draws 2-input AND gate
// 
//Buffere:
//This class should Buffer deal with the window directly
//It must perform the drawing by calling the output class functions
void Buffer::Draw(ApplicationManager* pManager)
{
	if(!Mark)
	{
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMGsel);
		if(m_Label != "-")
		pManager->PrintMessage(m_Label);
	}
	else
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMG);
	DrawConnections(pManager);
}

void Buffer::change_graphic(int x,int y)
{
	m_GfxInfo.x1 =x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x+m_GfxInfo.IMG->GetWidth();
	m_GfxInfo.y2 =y+m_GfxInfo.IMG->GetHeight();
}

void Buffer::DrawConnections(ApplicationManager*A)
{
	
	int N=m_OutputPin.ConnectedNo() ;
	for (int i = 0; i<N; i++)
	{
		
		if(m_OutputPin.getInputPins()[i]->getConnected())
		{
			Component*pComp2=A->getComponent(m_OutputPin.getInputPins()[i]);
			//A->DrawConnection(this,pComp2);
			GraphicsInfo G1,G2;
			G1=this->getgraphicsinfo();
			G2=pComp2->getgraphicsinfo();
			for (int j=0;j<pComp2->getInputs();j++)
			{
				if (m_OutputPin.getInputPins()[i]==&pComp2->getInputPin()[j])
				{
					if(!simulation)
					A->DrawLine(G1.x2,G1.y1+getOutputPin()->getPinInfo().y,
					G2.x1,G2.y1+pComp2->getInputPin()[j].getPinInfo().y);	
				else
				{
					if(m_OutputPin.getStatus()==LOW)
					{
						A->DrawLine(G1.x2,G1.y1+getOutputPin()->getPinInfo().y,
					G2.x1,G2.y1+pComp2->getInputPin()[j].getPinInfo().y,RED);	
					}
					else
						A->DrawLine(G1.x2,G1.y1+getOutputPin()->getPinInfo().y,
					G2.x1,G2.y1+pComp2->getInputPin()[j].getPinInfo().y,BLUE);	
				}
				}
			}
		}
	}
}

void Buffer::SaveComponent(int i,ApplicationManager *pManager)
{
	///*if (this->getLevel()==i+1)
	//{*/
	//	COMPS.compType=this->getComp_Type();
	//	/*COMPS.id=this->get_id();*/
	//	COMPS.compName=this->getString();
	//	COMPS.x=this->getgraphicsinfo().x1;
	//	COMPS.y=this->getgraphicsinfo().y1;
	//	//COMPS.id1=id;
	//	int input=this->getOutputPin()->ConnectedNo();
	//	for(int i=0;i<input;i++)
	//	{
	//		COMPS.id2=pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getCompSave().id;
	//		for(int y=0;y<pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getInputs();y++)
	//		{
	//			if(this->getOutputPin()->getInputPins()[i]==&pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getInputPin()[y])
	//				COMPS.pin_id=y;
	//		}
	//	}
	//	return true;
	///*}
	//else
	//	return false;*/
	COMPS.compType=this->getComp_Type();
		COMPS.id=i+1;
		COMPS.compName=this->getString();
		COMPS.x=this->getgraphicsinfo().x1;
		COMPS.y=this->getgraphicsinfo().y1;
		//COMPS.id1=id;
		int input=this->getOutputPin()->ConnectedNo();
		if (input!=0)
		{
		for(int i=0;i<input;i++)
		{
			pManager->getComponent(this->getOutputPin()->getInputPins()[i]);//getCompSave().id;
			int y=pManager->degreeComponent(pManager->getComponent(this->getOutputPin()->getInputPins()[i]));
			pManager->getComponent(this->getOutputPin()->getInputPins()[i])->SaveComponent(y,pManager);
			COMPS.id2=pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getCompSave().id;
			for(int y=0;y<pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getInputs();y++)
			{
				if(this->getOutputPin()->getInputPins()[i]==&pManager->getComponent(this->getOutputPin()->getInputPins()[i])->getInputPin()[y])
					COMPS.pin_id=y;
			}
		}
		}
}

CompInfo Buffer::getCompSave()
{
	return COMPS;
}

string Buffer::getComp_Type()
 {
	/* COMPS.compType;*/
	 return "BUFFER";
}
