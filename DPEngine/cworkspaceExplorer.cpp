#include <cworkspaceExplorer.h>
#include <cwidget.h>
#include <cimage.h>
#include <infoPanel.h>
#include <workspaceManager.h>
//#include <glObjects/workspaces/glWorkspaceSnapshot.h>
// #include <glObjects/workspaces/glPlanarWorkspace.h>

CWorkspaceExplorer* CWorkspaceExplorer::instance = NULL;
const int KScrollbarHeight = 15;
CWorkspaceExplorer::~CWorkspaceExplorer()
{
	instance = NULL;
	if(iScrollBar)
		delete iScrollBar;
}
/* TODO
void CWorkspaceExplorer::Scrolled(int value)
{
	if(!CWidget::GetInstance())
		return;
	QListIterator<CWorkspace*> workspaces(CWorkspaceManager::GetInstance()->GetWorkspaces());

	workspaces.toFront ();
	int relativeX=0;
	while (workspaces.hasNext())
	{
		CWorkspace* obj = workspaces.next();
		if(obj)
		{
			obj->GetSnapshot().SetPosition(QPoint(relativeX-value,obj->GetSnapshot().GetPosition().y()));
			relativeX+=obj->GetSnapshot().GetSize().x();
		}
	}
	if(CGLWidget::GetInstance())
	{
		CGLWidget::GetInstance()->updateGL();
	}
} */

CWorkspaceExplorer* CWorkspaceExplorer::InitInstance(CWidget *parent, QPointF& position, QPointF &size )
{
	if(!instance)
	{
		instance = new CWorkspaceExplorer(parent, position, size);
	}
	return instance;
}
QPoint CWorkspaceExplorer::GetDefaultWorkspaceSnapshotPos()
{
	return QPoint(GetPosition().x()+GetBorders().left,GetPosition().y()+GetBorders().top);

}
QPoint CWorkspaceExplorer::GetDefaultWorkspaceSnapshotSize()
{
	if(!CWidget::GetInstance())
		return QPoint(0,0);
	int height=GetSize().y()-iScrollBar->height()-+GetBorders().bottom-+GetBorders().top;
	int width=height*CWidget::GetInstance()->GetDefaultWorkspaceSize().x()/CWidget::GetInstance()->GetDefaultWorkspaceSize().y();
	return QPoint(width,height);
}
/*
get singleton instance
*/
CWorkspaceExplorer* CWorkspaceExplorer::GetInstance()
{
	return instance;
}

CWorkspaceExplorer::CWorkspaceExplorer(CWidget *parentWindow, QPointF& position, QPointF &size ):CObject (parentWindow, position, size)
{	
	iScrollBar = new QScrollBar(Qt::Horizontal,parentWindow);
	iScrollBar->setMinimum(0);
	iScrollBar->setMaximum(0);
	iScrollBar->setValue(0);
	iScrollBar->setGeometry (iPosition.x()+GetBorders().left,
		iPosition.y()+iSize.y()-KScrollbarHeight-GetBorders().bottom,
		iSize.x()-GetBorders().left-GetBorders().right,
		KScrollbarHeight);
	QObject::connect(iScrollBar , SIGNAL(valueChanged(int)), 
		this, SLOT(Scrolled(int))); 
	SetBorders(Settings::GetBordersConstant(EWorkspaceExplorerBorders));
	SetBorderColor(Settings::GetColorConstant(EWorkspaceExplorerBorderColor));
	SetInnerColor(Settings::GetColorConstant(EWorkspaceExplorerInnerColor));
}

void CWorkspaceExplorer::SelectWorkspace(CWorkspace *workspace)
{
	if(!CWidget::GetInstance())
		return;
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
	{
//TODO		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->StopAnimations();
	}
	CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);
	if(workspace)
	{
//TODO		workspace->StartAnimations();	
	}
	//TODO	if(CInfoPanel::GetInstance())
	CInfoPanel::GetInstance()->SetWorkspaceExplorerInfoView();
}

void CWorkspaceExplorer::SelectPlanarWorkspace()
{
	if(!CWidget::GetInstance())
		return;
//TODO	if(!CWorkspaceManager::GetInstance()->PlanarWorkspaceExists())
//TODO		return;
	SelectWorkspace(NULL);
	//CWidget::GetInstance()->updateGL();
}

void CWorkspaceExplorer::DrawSelection()
{
	if(!CWorkspaceManager::GetInstance())
		return;
	if(!CWorkspaceManager::GetInstance()->GetActiveWorkspace())
		return;
//TODO	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->GetSnapshot().Translate();
//	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->GetSnapshot().DrawSelection();
}
void CWorkspaceExplorer::DrawIcons()
{
	/*glEnable(GL_BLEND);
	float opaq = 0.5;
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	// nahrat jednotkovou matici
	Translate();//glTranslatef(0.0f, 0.0f, -50.0f);  
	glDisable( GL_TEXTURE_2D );

	//Move icon
	glColor4f(1.0, 1.0, 1.0,opaq); 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,iParentWindow->GetMoveIconTexture ());
	glBegin(GL_QUADS);
	glTexCoord2d(0,0); 
	glVertex2d(iMoveIcon.position.x(),iSize.y()-iMoveIcon.position.y()-iMoveIcon.size.y());

	glTexCoord2d(1,0);
	glVertex2d(iMoveIcon.position.x()+iMoveIcon.size.x() ,iSize.y()-iMoveIcon.position.y()-iMoveIcon.size.y());

	glTexCoord2d(1,1);
	glVertex2d(iMoveIcon.position.x()+iMoveIcon.size.x(),iSize.y()-iMoveIcon.position.y());

	glTexCoord2d(0,1);
	glVertex2d(iMoveIcon.position.x(),iSize.y()-iMoveIcon.position.y());
	glEnd();

	//Resize icon
	glBindTexture(GL_TEXTURE_2D,iParentWindow->GetResizeIconTexture ());
	glBegin(GL_QUADS);
	glTexCoord2d(0,0); 
	glVertex2d(iResizeIcon.position.x(),iSize.y() - iResizeIcon.position.y() - iResizeIcon.size.y());

	glTexCoord2d(1,0);
	glVertex2d(iResizeIcon.position.x()+iResizeIcon.size.x() ,iSize.y() - iResizeIcon.position.y() - iResizeIcon.size.y());

	glTexCoord2d(1,1);
	glVertex2d(iResizeIcon.position.x()+iResizeIcon.size.x(),iSize.y() - iResizeIcon.position.y());

	glTexCoord2d(0,1);
	glVertex2d(iResizeIcon.position.x(),iSize.y() - iResizeIcon.position.y());
	glEnd();

	glDisable(GL_TEXTURE_2D);
	// glPopMatrix();

	//slider - framecount
	glColor4f(0.8, 0.0, 1.0,opaq); 
	glRectf(iFrameSlider.position.x(),iSize.y()-iFrameSlider.position.y()-iFrameSlider.size.y(),iFrameSlider.position.x()+iFrameSlider.size.x(),iSize.y()-iFrameSlider.position.y());
	//draw slider
	glColor4f(0.8, 0.8, 1.0,0.8); 
	float sliderlength = iFrameSlider.size.x();
	float sliderposition = sliderlength * iFrameSlider.data / (iTexture->GetDepth());
	float sliderhandlelenth = (float)sliderlength  / (iTexture->GetDepth());
	glRectf(iFrameSlider.position.x() + sliderposition,iSize.y()-iFrameSlider.position.y()-iFrameSlider.size.y(),iFrameSlider.position.x() + sliderposition+sliderhandlelenth,iSize.y()-iFrameSlider.position.y());

	glDisable (GL_BLEND);*/

}

void CWorkspaceExplorer::DrawTexts()
{
	TColor color= Settings::GetColorConstant(EWorkspaceExplorerTextColor);
	//glColor4f(color.r, color.g, color.b, color.a);
	int fontSize =15;
		//CWidget::GetInstance()->renderText  (5,iSize.y()-fontSize-3,
//			QString("Workspace Explorer: "),fontSize);
		//glColor4f(1,1,1,1);
}

/*void CWorkspaceExplorer::initializeGL()
{

}*/

void CWorkspaceExplorer::paint(QPainter* painter)
{
	if(!CWidget::GetInstance())
		return;
	//CWidget::GetInstance()->resetGLView();
	//Translate();
	
	DrawInnerRect(painter);
	DrawBorderRect(painter);

	int snapWidthSum = 0;
	//glDisable(GL_BLEND);
	//CGLWidget::GetInstance()->resetGLView();
	QListIterator<CWorkspace*> workspaces(CWorkspaceManager::GetInstance()->GetWorkspaces());
	while (workspaces.hasNext())
	{
		CWorkspaceSnapshot &snap = workspaces.next()->GetSnapshot();
		snapWidthSum += snap.GetSize().x();
		if(snap.GetPosition().x()+snap.GetSize().x()>0 
			&& snap.GetPosition().x()<=iSize.x())
		{
			snap.paint(painter);
		}
	}
	//CGLWidget::GetInstance()->resetGLView();
	//DrawSelection(painter);
	
	iScrollBar->setVisible(true);
	if(snapWidthSum >iSize.x())
	{
		iScrollBar->setMaximum(snapWidthSum-iSize.x());
		iScrollBar->setPageStep(iSize.x());
	}
	else
	{
		iScrollBar->setMaximum(0);
	}

	//CGLWidget::GetInstance()->resetGLView();
	//Translate();
	//DrawTexts();
	return;
}

bool CWorkspaceExplorer::IsOnMoveIcon(int x, int y)
{
	if(x<iMoveIcon.position.x())
		return false;
	if(y<iMoveIcon.position.y())
		return false;
	if(x>(iMoveIcon.position.x()+iMoveIcon.size.x()))
		return false;
	if(y>(iMoveIcon.position.y()+iMoveIcon.size.y()))
		return false;
	return true;
}

bool CWorkspaceExplorer::IsOnResizeIcon(int x, int y)
{

	if(x<iResizeIcon.position.x())
		return false;
	if(y<iResizeIcon.position.y())
		return false;
	if(x>(iResizeIcon.position.x()+iResizeIcon.size.x()))
		return false;
	if(y>(iResizeIcon.position.y()+iResizeIcon.size.y()))
		return false;
	return true;
}

void CWorkspaceExplorer::SetGeometry(int x, int y, int width, int height)
{
	if(!CWorkspaceManager::GetInstance()){
		return;
	}
	QPointF oldPos = iPosition;
	QPointF oldSize = iSize;
	CObject::SetGeometry(x,y,width,height);
	iScrollBar->setGeometry (iPosition.x()+GetBorders().left,
		iPosition.y()+iSize.y()-KScrollbarHeight-GetBorders().bottom,
		iSize.x()-GetBorders().left-GetBorders().right,
		KScrollbarHeight);

	QListIterator<CWorkspace*> workspaces((CWorkspaceManager::GetInstance()->GetWorkspaces()));
	int posx;
	if(workspaces.hasNext())
	{
		posx=workspaces.next()->GetSnapshot().GetPosition().x();
	}
	workspaces.toFront();
	while(workspaces.hasNext())
	{
		CWorkspace* ws = workspaces.next();

		QPoint size=GetDefaultWorkspaceSnapshotSize();
		QPoint pos = GetDefaultWorkspaceSnapshotPos();

		ws->GetSnapshot().SetGeometry(posx,pos.y(), size.x(),size.y());
		posx+=size.x();

	}
}

void CWorkspaceExplorer::wheelEvent(QWheelEvent *event)
{
	/*float framm=(float)iActualTextureCoords.bottomLeft.GetZ() * (iTexture->GetDepth ());
	int dpt = (float)(iActualTextureCoords.bottomLeft.GetZ() * (iTexture->GetDepth ()+0.5f));


	if(event->delta() > 0 )
	{
	dpt++;
	}
	else
	{
	dpt--;
	}
	if(dpt>=iTexture->GetDepth ())
	{
	dpt=iTexture->GetDepth ()-1;
	}
	if(dpt<0)
	{
	dpt=0;
	}
	//TODO kouknout na framy srovnat s originalem (Nearest neigbour - aby to neinterpolovalo mezi slices)
	iFrameSlider.data =dpt;
	float z=(float)dpt/(iTexture->GetDepth ());
	//set z coords of texture
	iActualTextureCoords.bottomLeft.SetZ(z);
	iActualTextureCoords.bottomRight.SetZ(z);
	iActualTextureCoords.topLeft.SetZ(z);
	iActualTextureCoords.topRight.SetZ(z);
	PrepareActualTexture();
	iParentWindow->updateGL();
	*/
}
void CWorkspaceExplorer::mouseReleaseEvent(QMouseEvent *event)
{
	if(!CWorkspaceManager::GetInstance())
		return;
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace()){
//		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->GetSnapshot().mouseReleaseEvent(event);
	}
}
void CWorkspaceExplorer::AddNewWorkspace()
{
	if(!CWidget::GetInstance())
		return;
	CWidget* cwidget =CWidget::GetInstance();

	CWorkspace *newWorkspace = new CWorkspace(cwidget,cwidget->GetDefaultWorkspacePosition(),cwidget->GetDefaultWorkspaceSize());
	CWorkspaceManager::GetInstance()->AddWorkspace(newWorkspace);
	SelectWorkspace(newWorkspace);
	cwidget->paint();	
}/*
void CGLWorkspaceExplorer::CreateNewPlanarWorkspace()
{
	if(!CWidget::GetIntance())
		return;
	CWidget* glwidget = CWidget::GetInstance();
	try
	{
		CPlanarWorkspace *newWorkspace = new CPlanarWorkspace(glwidget,glwidget->GetDefaultWorkspacePosition(),glwidget->GetDefaultWorkspaceSize());
		CWorkspaceManager::GetInstance()->CreatePlanarWorkspace(newWorkspace);
		//SelectWorkspace(NULL);
		SelectPlanarWorkspace();
	}
	catch (TextureNotCreatedException &e)
	{
		//workspace not created
	}
}*/
void CWorkspaceExplorer::mouseDoubleClickEvent(QMouseEvent *event)
{
	AddNewWorkspace();
}
void CWorkspaceExplorer::mouseMoveEvent(QMouseEvent *event)
{
	if(!CWorkspaceManager::GetInstance())
		return;
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
	{
//		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->GetSnapshot().mouseMoveEvent(event);
	}
	/*int x=event->x() - iPosition.x();
	int y = event->y()- iPosition.y();
	int dx = x-iPreviousMousePosition.x();
	int dy = y-iPreviousMousePosition.y();
	if(EMouseStateImageWindowLeveling==iMouseState)
	{
	QCursor::setPos(iLockedGlobalMousePosition);
	//iScale *=(1.+(float)dx/50.);
	//iBias *=(1.+(float)dy/100.);
	iImageWindow.center+=4*dy;
	if(iImageWindow.center>65596)
	iImageWindow.center = 65096;
	//if(iImageWindow.center<0)
	//	iImageWindow.center = 0;
	iImageWindow.width+=4*dx;
	if(iImageWindow.width>65096)
	iImageWindow.width = 65096;
	if(iImageWindow.width<1)
	iImageWindow.width = 1;
	//update slice texture
	PrepareActualTexture();
	iParentWindow->updateGL ();
	return;
	}
	else if(iMouseState == EMouseStateFrameSliderChanging )
	{
	QCursor::setPos(event->globalPos().x(),iLockedGlobalMousePosition.y());
	IsOnFrameSliderIcon (x,y);

	return;
	}
	else if(iMouseState == EMouseStateImageMoving)
	{
	iImageCenter.setX(iImageCenter.x()+(float)dx/iSize.x());
	iImageCenter.setY(iImageCenter.y()+(float)dy/iSize.y());
	iParentWindow->updateGL ();
	//return;
	}
	else if(iMouseState == EMouseStateImageZooming)
	{
	QCursor::setPos(iLockedGlobalMousePosition);
	iZoomFactor*=(1.-(float)dy/100.);
	iImageCenter.setX((x-(x-iLockedImageCenter.x()*iSize.x())*(iZoomFactor/iLockedZoom))/iSize.x());
	iImageCenter.setY((y-(y-iLockedImageCenter.y()*iSize.y())*(iZoomFactor/iLockedZoom))/iSize.y());
	iParentWindow->updateGL ();
	return;
	}
	else if(iMouseState == EMouseStateObjectMoving)
	{
	SetGeometry(dx + iPosition.x(),dy + iPosition.y(),iSize.x(),iSize.y());
	iParentWindow->updateGL ();
	return; //to avoid updating of previous mouse position
	}
	else if(iMouseState == EMouseStateObjectResizing)
	{
	SetGeometry(iPosition.x(),iPosition.y(),iSize.x()+dx,iSize.y()+dy);
	iParentWindow->updateGL ();

	}
	iPreviousMousePosition = QPoint(x, y);	
	//iPreviousGlobalMousePosition = event->globalPos();
	*/
}
void CWorkspaceExplorer::mousePressEvent(QMouseEvent *event)
{
	if(!CWorkspaceManager::GetInstance())
		return;
//	if(!CInfoPanel::GetInstance())
//		return;
	CInfoPanel::GetInstance()->SetWorkspaceExplorerInfoView();
	QListIterator<CWorkspace*> workspaces(CWorkspaceManager::GetInstance()->GetWorkspaces());
	workspaces.toBack ();
	while (workspaces.hasPrevious())
	{
		CWorkspace* obj = workspaces.previous();
		if(obj->GetSnapshot().IsPointOnObject(event->x(),event->y()))
		{
			obj->GetSnapshot().mousePressEvent(event);
			return;
		}
	}
	
}
