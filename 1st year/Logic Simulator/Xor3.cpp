#include "Xor3.h"
#include "ApplicationManager.h"
#include <utility>

Xor3::Xor3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut,pair<int,int>(59,15),
	pair<int,int>(0,8),pair<int,int>(0,14),pair<int,int>(0,22))
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_GfxInfo.IMG = r_GfxInfo.IMG;
	m_GfxInfo.IMGsel=r_GfxInfo.IMGsel;
	Level = -1;
}

void Xor3::Operate()
{
	if((m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == LOW && m_InputPins[2].getStatus() == LOW) 
		|| (m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == HIGH && m_InputPins[2].getStatus() == HIGH)
		|| (m_InputPins[0].getStatus() == HIGH && m_InputPins[1].getStatus() == LOW && m_InputPins[2].getStatus() == HIGH)
		|| (m_InputPins[0].getStatus() == HIGH && m_InputPins[1].getStatus() == HIGH && m_InputPins[2].getStatus() == LOW))
		m_OutputPin.setStatus(LOW);
	else m_OutputPin.setStatus(HIGH);
}

void Xor3::Draw(ApplicationManager* pManager)
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

void Xor3::change_graphic(int x,int y)
{
	m_GfxInfo.x1 =x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x+m_GfxInfo.IMG->GetWidth();
	m_GfxInfo.y2 =y+m_GfxInfo.IMG->GetHeight();
}

void Xor3::DrawConnections(ApplicationManager*A)
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

void Xor3::SaveComponent(int i,ApplicationManager *pManager)
{
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

CompInfo Xor3::getCompSave()
{
	return COMPS;
}

string Xor3::getComp_Type()
 {
	/* COMPS.compType;*/
	 return "XOR3";
}