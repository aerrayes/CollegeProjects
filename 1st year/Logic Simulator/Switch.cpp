#include "Switch.h"
#include "ApplicationManager.h"
Switch::Switch(const GraphicsInfo &r_GfxInfo):m_OutputPin(SWITCH_FANOUT,PinInfo(r_GfxInfo.IMG->GetWidth(),r_GfxInfo.IMG->GetHeight()/2))
{
	ON=false;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_GfxInfo.IMG = r_GfxInfo.IMG;
	m_GfxInfo.IMGsel=r_GfxInfo.IMGsel;
	Level=0;
	m_Label = "-";
}
void Switch::change_graphic(int x,int y)
{
	m_GfxInfo.x1 =x;
	m_GfxInfo.y1 = y;
	m_GfxInfo.x2 = x+m_GfxInfo.IMG->GetWidth();
	m_GfxInfo.y2 =y+m_GfxInfo.IMG->GetHeight();
}
Switch::~Switch()
{
}

void Switch::Operate()
{
	if(!ON)
	{
		m_OutputPin.setStatus(LOW);
	}
	else if(ON)
	{
		m_OutputPin.setStatus(HIGH);
	}
}

void Switch::Draw(ApplicationManager *pManager)
{
	if(!ON)
	{
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMG);
	}
	else
	{
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMGsel);
	}
	DrawConnections(pManager);
}/*
void Switch::change_image(int x,int y)
{
	if(ON==false)
	{
		delete m_GfxInfo.IMG;
		m_GfxInfo.IMG =new image("images\\Switch ON.jpg");
		int Len = m_GfxInfo.IMG->GetWidth(), Wdth =m_GfxInfo.IMG->GetHeight();
		m_GfxInfo.x1 = x - Len/2;
		m_GfxInfo.x2 = x + Len/2;
		m_GfxInfo.y1 = y - Wdth/2;
		m_GfxInfo.y2 = y + Wdth/2;
		ON=true;
	}
	else
	{
		delete m_GfxInfo.IMG;
		m_GfxInfo.IMG =new image("images\\Switch OFF.jpg");
		int Len = m_GfxInfo.IMG->GetWidth(), Wdth =m_GfxInfo.IMG->GetHeight();
		m_GfxInfo.x1 = x - Len/2;
		m_GfxInfo.x2 = x + Len/2;
		m_GfxInfo.y1 = y - Wdth/2;
		m_GfxInfo.y2 = y + Wdth/2;
		ON=false;
	}
}*/

void Switch::DrawConnections(ApplicationManager*A)
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


void Switch::SaveComponent(int i,ApplicationManager *pManager)
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

CompInfo Switch::getCompSave()
{
	return COMPS;
}

string Switch::getComp_Type()
 {
	/* COMPS.compType="Switch";*/
	 return "SWITCH";
}