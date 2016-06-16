#include "Led.h"
#include "ApplicationManager.h"
Led::Led(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_GfxInfo.IMG = r_GfxInfo.IMG;
	m_GfxInfo.IMGsel=r_GfxInfo.IMGsel;
	m_InputPin.setPinInfo(PinInfo(0,18));
	Level =-1;
	m_Label ="-";
}
void Led::change_graphic(int x,int y)
{
m_GfxInfo.x1 =x;
	m_GfxInfo.y1 = y;
m_GfxInfo.x2 = x+m_GfxInfo.IMG->GetWidth();
	m_GfxInfo.y2 =y+m_GfxInfo.IMG->GetHeight();
}
Led::~Led(){}

void Led::Operate()
{
	/*if(m_InputPin.getStatus()==HIGH)
	{
	}
	else m_GfxInfo.IMG=m_GfxInfo.IMG;*/
}
//void Led::change_image(int x,int y)
//{	
//	m_GfxInfo.x1 =x;
//	m_GfxInfo.y1 = y;
//	m_GfxInfo.x2 = x+m_GfxInfo.IMG->GetWidth();
//	m_GfxInfo.y2 =y+m_GfxInfo.IMG->GetHeight();
//}
void Led::Draw(ApplicationManager *pManager)
{
	if(m_InputPin.getStatus()==LOW)
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMG);
	else
		pManager->DrawComp(m_GfxInfo.x1, m_GfxInfo.y1,m_GfxInfo.IMGsel);
}


void Led::SaveComponent(int i,ApplicationManager *pManager)
{
	
			COMPS.compType=this->getComp_Type();
		COMPS.id=i+1;
		COMPS.compName=this->getString();
		COMPS.x=this->getgraphicsinfo().x1;
		COMPS.y=this->getgraphicsinfo().y1;
		//COMPS.id1=id;
		int input=0;
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

CompInfo Led::getCompSave()
{
	return COMPS;
}

string Led::getComp_Type()
 {
	 //COMPS.compType;
	 return "LED";
}