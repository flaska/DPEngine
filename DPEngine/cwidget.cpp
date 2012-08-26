#include <cwidget.h>
#include <cworkspace.h>
#include <workspacemanager.h>
#include <cimageexplorer.h>
#include <cworkspaceexplorer.h>
#include <settings.h>

CWidget *CWidget::instance = NULL;

CWidget::CWidget(QWidget *parent){
	resize(500,500);
	SetGeometry(0,0,500,500);
	QPointF workspaceExplorerPos(0,this->height()-Settings::imageExplorerSize);
	QPointF workspaceExplorerSize(this->width(),Settings::imageExplorerSize);
	iWorkspaceExplorer = CWorkspaceExplorer::InitInstance(this, workspaceExplorerPos,workspaceExplorerSize);
	
	CWorkspaceManager::InitInstance(this);
	CWorkspace *workspace = new CWorkspace(this,QPointF(0,0),QPointF(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize));
	//CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);
	CWorkspaceManager::GetInstance()->AddWorkspace(workspace);

	QPointF imageExplorerPos(this->width()-Settings::imageExplorerSize,0);
	QPointF imageExplorerSize(150,this->height()-Settings::imageExplorerSize);
	CImageExplorer::InitInstance(this, imageExplorerPos,imageExplorerSize);
	iImageExplorer = CImageExplorer::GetInstance();
	LoadIcons();
	iActiveObject=NULL;

}

void CWidget::wheelEvent(QWheelEvent *event)
{

	//what object is mouse on
	if(iActiveObject)
	{
		iActiveObject->wheelEvent(event);
	}
}

void CWidget::resizeEvent(QResizeEvent * event){/*
	if (iPixmap) delete iPixmap;
	iPixmap = new QPixmap(event->size().width(),event->size().height());
	setPixmap(*iPixmap);

	if (CWorkspaceManager::GetInstance()) CWorkspaceManager::GetInstance()->GetActiveWorkspace()->resizeEvent(QSize(event->size().width()*4/5,event->size().height()*4/5));
*//*
	QPointF imageExplorerPos(this->width()*4/5,0);
	QPointF imageExplorerSize(this->width()*1/5,this->height()*4/5);
	paint();
*/
	SetGeometry(0,0,event->size().width(),event->size().height());
}

void CWidget::SetGeometry(int x, int y, int w, int h)
{
	if(!CWorkspaceManager::GetInstance()) {
		return;
	}
	iSize.setX(w);
	iSize.setY(h);
	int height = h;
	int width =w;
	if (height==0)								// Prevent A Divide By Zero By
	{
		height=1;
	}					

	QPoint imageExplorerPos(this->width()-Settings::imageExplorerSize,0);
	QPoint imageExplorerSize(this->width()-imageExplorerPos.x(),this->height()-Settings::imageExplorerSize);
	iImageExplorer->SetGeometry(imageExplorerPos.x(),imageExplorerPos.y(),imageExplorerSize.x(),imageExplorerSize.y());

	QPoint workspaceExplorerPos(0,this->height()-Settings::imageExplorerSize);
	QPoint workspaceExplorerSize(this->width(),this->height()-workspaceExplorerPos.y());
	iWorkspaceExplorer->SetGeometry(workspaceExplorerPos.x(),workspaceExplorerPos.y(),workspaceExplorerSize.x(),workspaceExplorerSize.y());

	QPoint workspacePos(0,0);
	QPoint workspaceSize(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize);

	if (CWorkspaceManager::GetInstance()->GetActiveWorkspace())
		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->SetGeometry(workspacePos.x(),workspacePos.y(),
		workspaceSize.x(),workspaceSize.y());
	else if (CWorkspaceManager::GetInstance()->GetPlanarWorkspace())
		CWorkspaceManager::GetInstance()->GetPlanarWorkspace()->SetGeometry(workspacePos.x(),workspacePos.y(),
		workspaceSize.x(),workspaceSize.y());
	QListIterator<CWorkspace*> workspaces((CWorkspaceManager::GetInstance()->GetWorkspaces()));
	workspaces.toFront();
	while(workspaces.hasNext())
	{
		CWorkspace* ws = workspaces.next();
		ws->SetGeometry(workspacePos.x(),workspacePos.y(),
		workspaceSize.x(),workspaceSize.y());
	}
	//CGLObject::resizeGL();
	paint();
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
	}
	if(CWorkspaceExplorer::GetInstance())
	{
		if(CWorkspaceExplorer::GetInstance()->IsPointOnObject(event->x(),event->y()))
		{
			iActiveObject  = iWorkspaceExplorer;
			iWorkspaceExplorer->mousePressEvent(event);
			paint();
			return;
		}
	}
	if(CWorkspaceManager::GetInstance())
	{
		if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
		{
			if(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->IsPointOnObject(event->x(),event->y()))
			{
				iActiveObject  = CWorkspaceManager::GetInstance()->GetActiveWorkspace();
				iActiveObject->mousePressEvent(event);
				paint();
				return;
			}
		}
		if(CWorkspaceManager::GetInstance()->GetPlanarWorkspace()->IsPointOnObject(event->x(),event->y())){
			iActiveObject  = CWorkspaceManager::GetInstance()->GetPlanarWorkspace();
			iActiveObject->mousePressEvent(event);
			paint();
			return;
		}
	}
}
/*
void CWidget::paint(){
	QImage *iWidgetImage = new QImage(this->width(),this->height(),QImage::Format_RGB32);
	iWidgetImage->fill(0);
	QPainter *qpainter=new QPainter();
	qpainter->begin(iWidgetImage);
	if (CWorkspaceManager::GetInstance()->GetActiveWorkspace()) {
		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint(qpainter,QRect(QPoint(0,0),QPoint(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize)));
	}
	CImageExplorer::GetInstance()->paint(qpainter); // pridat qrect
	CWorkspaceExplorer::GetInstance()->paint(qpainter);
	qpainter->end();
	iPixmap->convertFromImage(*iWidgetImage);
	setPixmap(*iPixmap);
	repaint();
	delete qpainter;
	delete iWidgetImage;
}
*/
void CWidget::paint(){
	QPixmap *pixmap = new QPixmap(this->width(),this->height());
	pixmap->fill(Qt::black);
	QPainter *qpainter=new QPainter();
	qpainter->begin(pixmap);
	if (CWorkspaceManager::GetInstance()->GetActiveWorkspace()) {
		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint(qpainter,QRect(QPoint(0,0),QPoint(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize)));
	}
	else if(CWorkspaceManager::GetInstance()->PlanarWorkspaceExists())
	{
		CWorkspaceManager::GetInstance()->GetPlanarWorkspace()->paint(qpainter,QRect(QPoint(0,0),QPoint(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize)));
	}

	CImageExplorer::GetInstance()->paint(qpainter);
	CWorkspaceExplorer::GetInstance()->paint(qpainter);

	if (iActiveObject){
		iActiveObject->DrawSelection(qpainter);
	}
	qpainter->end();
	setPixmap(*pixmap);
	repaint();
	delete qpainter;
	delete pixmap;
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

void CWidget::LoadIcons()
{
	iImageMoveIcon = new QImage(Settings::MoveIconFileName);
	iImageResizeIcon = new QImage(Settings::ResizeIconFileName);
	iImageCloseIcon = new QImage(Settings::CloseIconFileName);
}

QImage* CWidget::getIcon(TIconType type)
{
	switch (type)
	{
		case TIconType::CloseIcon: return iImageCloseIcon;
			break;
		case TIconType::MoveIcon: return iImageMoveIcon;
			break;
		case TIconType::ResizeIcon: return iImageResizeIcon;
			break;
		default: ;
			break;
	}
}

QPointF CWidget::GetDefaultWorkspaceSize()
{
	return QPointF(this->width()-Settings::imageExplorerSize,this->height()-Settings::imageExplorerSize);
}

QPointF CWidget::GetDefaultWorkspacePosition()
{
	return QPointF(0,0);
}

void CWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	iActiveObject = NULL;
	if(iImageExplorer->IsPointOnObject(event->x(),event->y()))
	{
		iActiveObject  = iImageExplorer;
		//iImageExplorer->mouseDoubleClickEvent(event);
		paint ();
		return;
	}
	if(iWorkspaceExplorer->IsPointOnObject(event->x(),event->y()))
	{
		iActiveObject  = iWorkspaceExplorer;
		iWorkspaceExplorer->mouseDoubleClickEvent(event);
		paint();
		return;
	}
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
	{
		if(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->IsPointOnObject(event->x(),event->y()))
		{
			iActiveObject  = CWorkspaceManager::GetInstance()->GetActiveWorkspace();
			//iActiveObject->mouseDoubleClickEvent(event);
			paint();
			return;
		}
	}
}

void CWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(iActiveObject)
	{
		iActiveObject->mouseReleaseEvent(event);
	}
}