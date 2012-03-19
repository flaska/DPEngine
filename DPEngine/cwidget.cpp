#include <cwidget.h>
#include <cworkspace.h>
#include <workspacemanager.h>

CWidget *CWidget::instance = NULL;

CWidget::CWidget(QWidget *parent){
	iPixmap = new QPixmap(800,800);
	setPixmap(*iPixmap);
}
void CWidget::mousePressEvent(QMouseEvent *event)
{
	/* DEMO */

	if(event->button() == Qt::RightButton  ) {
		CImage *im1 = new CImage(NULL, QString("im.dcm"), QPointF(10,10), QPointF(10,10));
		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->addImage(im1);
	}
	/* DEMO */
	iActiveObject = NULL;
	//TODO 
	/*if(CGLImageExplorer::GetInstance())
	{
		if(CGLImageExplorer::GetInstance()->IsPointOnObject(event->x(),event->y()))
		{
			iActiveObject  = iImageExplorer;
			iImageExplorer->mousePressEvent(event);
			updateGL ();
			return;
		}
	}
	if(CGLWorkspaceExplorer::GetInstance())
	{
		if(CGLWorkspaceExplorer::GetInstance()->IsPointOnObject(event->x(),event->y()))
		{
			iActiveObject  = iWorkspaceExplorer;
			iWorkspaceExplorer->mousePressEvent(event);
			updateGL ();
			return;
		}
	}*/
	if(CWorkspaceManager::GetInstance())
	{
		if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
		{
//TODO			if(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->IsPointOnObject(event->x(),event->y()))
			{
				iActiveObject  = CWorkspaceManager::GetInstance()->GetActiveWorkspace();
				iActiveObject->mousePressEvent(event);
				paint();
				return;
			}
		}/*
		if(CWorkspaceManager::GetInstance()->GetPlanarWorkspace()->IsPointOnObject(event->x(),event->y())){
			iActiveObject  = CWorkspaceManager::GetInstance()->GetPlanarWorkspace();
			iActiveObject->mousePressEvent(event);
			paint();
			return;
		}*/
	}
}

void CWidget::paint(){
	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint();
	QImage im = *(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->iWorkspaceImage);
	iPixmap->convertFromImage(im);
	setPixmap(*iPixmap);
}

CWidget *CWidget::GetInstance(){
	return instance;
}

CWidget* CWidget::InitInstance(QWidget *parent)
{
	if(!instance)
	{
		instance = new CWidget(parent);
	}
	return instance;
}

void CWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(iActiveObject)
	{
		iActiveObject->mouseMoveEvent(event);
	}
}