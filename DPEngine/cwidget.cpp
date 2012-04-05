#include <cwidget.h>
#include <cworkspace.h>
#include <workspacemanager.h>
#include <cimageexplorer.h>

CWidget *CWidget::instance = NULL;

CWidget::CWidget(QWidget *parent){
	setFixedSize(900,900);
	iPixmap = new QPixmap(this->width(),this->height());
	setPixmap(*iPixmap);
	
	CWorkspace *workspace = new CWorkspace(this,QPointF(0,0),QPointF(this->width()*4/5,this->height()*4/5));
	CWorkspaceManager::InitInstance();
	CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);

	QPointF imageExplorerPos(this->width()*4/5,0);
	QPointF imageExplorerSize(this->width()*1/5,this->height()*4/5);
	CImageExplorer::InitInstance(this, imageExplorerPos,imageExplorerSize);
	iImageExplorer = CImageExplorer::GetInstance();

}

void CWidget::mousePressEvent(QMouseEvent *event)
{
	iActiveObject = NULL;
	//TODO 
	if(CImageExplorer::GetInstance()){
		if(CImageExplorer::GetInstance()->IsPointOnObject(event->x(),event->y())){
			iActiveObject  = iImageExplorer;
			iImageExplorer->mousePressEvent(event);
			paint();
			return;
		}
	}/*
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
	QImage activeworkspaceimage = *(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->iWorkspaceImage);
	QImage *iWidgetImage = new QImage(this->width(),this->height(),QImage::Format_RGB32);
	iWidgetImage->fill(0);
	QPainter *qpainter=new QPainter();
	qpainter->begin(iWidgetImage);
	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint();
	qpainter->drawImage(QRect(QPoint(0,0),QPoint(this->width()*4/5,this->height()*4/5)),activeworkspaceimage);
	CImageExplorer::GetInstance()->paint(qpainter);
	qpainter->end();
	iPixmap->convertFromImage(*iWidgetImage);
	setPixmap(*iPixmap);
	repaint();
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

//QPixmap* CWidget::getWidgetImage(){
//	return iWidgetImage;
//}

const int CWidget::height() {	
	return QLabel::height();
}
const int CWidget::width() {
	return QLabel::width();
}