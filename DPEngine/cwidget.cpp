#include <cwidget.h>
#include <cworkspace.h>
#include <workspacemanager.h>
#include <cimageexplorer.h>

CWidget *CWidget::instance = NULL;

CWidget::CWidget(QWidget *parent){
	iPixmap = NULL;
	resize(500,500);
	SetGeometry(0,0,500,500);
	//iPixmap = new QPixmap(this->width(),this->height());
	//setPixmap(*iPixmap);
	
	CWorkspace *workspace = new CWorkspace(this,QPointF(0,0),QPointF(this->width()*4/5,this->height()*4/5));
	CWorkspaceManager::InitInstance();
	CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);

	QPointF imageExplorerPos(this->width()*4/5,0);
	QPointF imageExplorerSize(this->width()*1/5,this->height()*4/5);
	CImageExplorer::InitInstance(this, imageExplorerPos,imageExplorerSize);
	iImageExplorer = CImageExplorer::GetInstance();

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
 	if (iPixmap) delete iPixmap;
	iPixmap = new QPixmap(w,h);
	setPixmap(*iPixmap);

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

	QPoint imageExplorerPos(this->width()*4/5,0);
	QPoint imageExplorerSize(this->width()-imageExplorerPos.x(),this->height()*4/5);
	iImageExplorer->SetGeometry(imageExplorerPos.x(),imageExplorerPos.y(),imageExplorerSize.x(),imageExplorerSize.y());

	//QPoint workspaceExplorerPos(0,this->height()*4/5);
	//QPoint workspaceExplorerSize(this->width(),this->height()-workspaceExplorerPos.y());

	//iWorkspaceExplorer->SetGeometry(workspaceExplorerPos.x(),workspaceExplorerPos.y(),workspaceExplorerSize.x(),workspaceExplorerSize.y());;

	QPoint workspacePos(0,0);
	QPoint workspaceSize(this->width()*4/5,this->height()*4/5);

	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->SetGeometry(workspacePos.x(),workspacePos.y(),
		workspaceSize.x(),workspaceSize.y());
	/*QListIterator<CWorkspace*> workspaces((CWorkspaceManager::GetInstance()->GetWorkspaces()));
	workspaces.toFront();
	while(workspaces.hasNext())
	{
		CWorkspace* ws = workspaces.next();
		ws->SetGeometry(workspacePos.x(),workspacePos.y(),
		workspaceSize.x(),workspaceSize.y());
	}
	CGLObject::resizeGL();*/
	paint();
}



void CWidget::mousePressEvent(QMouseEvent *event)
{
	std::cout << "Mouse X " << event->x() << "Mouse Y " << event->y() << std::endl;
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
/*
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
}*/

void CWidget::paint(){
	QImage *iWidgetImage = new QImage(this->width(),this->height(),QImage::Format_RGB32);
	iWidgetImage->fill(0);
	QPainter *qpainter=new QPainter();
	qpainter->begin(iWidgetImage);
	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint(qpainter,QRect(QPoint(0,0),QPoint(this->width()*4/5,this->height()*4/5)));
	CImageExplorer::GetInstance()->paint(qpainter); // pridat qrect
	qpainter->end();
	iPixmap->convertFromImage(*iWidgetImage);
	setPixmap(*iPixmap);
	repaint();
	delete qpainter;
	delete iWidgetImage;
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