#include "Move.h"
#include "Component.h"
#include "ApplicationManager.h"

void Move::ReadActionParameters(ApplicationManager *pManager)
{
	pManager->PrintMessage("You have selected Move Tool , select the Component you wish to move (right click to exit)");
	int x,y;
	do
	{
		k = pManager->GetMouseInput(x,y);
		pComp1=pManager->FindComp(x,y);
	}
	while(pComp1==NULL &&  k!= RIGHT_CLICK);
	if(k == RIGHT_CLICK) return;
	Before=pComp1->getgraphicsinfo();
	pManager->ClearStatesBar();

}

void Move::Execute(ApplicationManager *pManager)
{

	ReadActionParameters(pManager);
	if(k == RIGHT_CLICK) return;
	pManager->FlushMouseQueue();
	pManager->FlushKeyQueue(); 
	pManager->SetBuffering(true);   
	int RectULX = pComp1->getgraphicsinfo().x1; 
	int RectULY =pComp1->getgraphicsinfo().y1 ;
	int RectWidth = pComp1->getgraphicsinfo().x2-pComp1->getgraphicsinfo().x1;
	int  iX;
	int  iY ;
	bool bDragging = false;
	int iXOld = 0;
	int iYOld = 0;
	bool mark=true;
	while(1)
	{
		pManager->Clearwindow();        
		if(bDragging == false) {
			if(pManager->GetButtonState(LEFT_BUTTON, iX, iY)== BUTTON_DOWN) {
				if(((iX > RectULX) && (iX < (RectULX + RectWidth))) && ((iY > RectULY) && (iY < (RectULY + RectWidth)))) {
					bDragging = true;
					mark=true;
					iXOld = iX; iYOld = iY;
				}
			}
		} else {
			if(pManager->GetButtonState(LEFT_BUTTON, iX, iY)==BUTTON_UP) {
				mark=false;
				bDragging = false;
				break;
			} else {
				if(iX != iXOld) {
					RectULX = RectULX + (iX - iXOld);
					iXOld = iX;
				}
				if(iY != iYOld) {
					RectULY = RectULY + (iY - iYOld);
					iYOld = iY;
				}
			}
		}
		pComp1->change_graphic(RectULX,RectULY);
		pManager->UpdateInterface(1);
		pManager->PrintMessage("move your component");
		pManager->UpdateBuffer();
	}
	pManager->SetBuffering(false);
	pManager->ClearStatesBar();
	pManager->FlushMouseQueue();
	After=pComp1->getgraphicsinfo();
}
void Move::Undo(ApplicationManager *pManager)
{
	if(k == RIGHT_CLICK) return;
	pComp1->change_graphic(Before.x1,Before.y1);
}
void Move::Redo(ApplicationManager *pManager)
{
	if(k == RIGHT_CLICK) return;
	pComp1->change_graphic(After.x1,After.y1);
}
