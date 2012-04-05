#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <cworkspace.h>
#include <cimage.h>
#include <freelayout.h>
#include <growinggridlayout.h>
#include <settings.h>
#include <cobject.h>
#include <cimageexplorer.h>
#include <cwidget.h>
CWorkspace::CWorkspace(CObject *parent, const QPointF &position, const QPointF &size):CObject(parent, position, size){
	iWorkspaceImage = new QImage(size.x(),size.y(),QImage::Format_RGB32);
	iWorkspaceImage->fill(Qt::yellow);
	SetSize(QPointF(size.x(),size.y()));
	iLayout = new CGrowingGridLayout(this,EGrowinGridLayoutHorizontal);
	TBorders b;
	b.bottom=0;
	b.left=0;
	b.right=0;
	b.top=0;
	this->SetBorders(b);
}

void CWorkspace::addImage(CImage *image)
{
	image->SetParentWorkspace(this);
	iImages.append(image);
	iLayout->PrepareNewImageGeometry(image);
	//UpdateTexture();
	//if(CGLWidget::GetInstance())
	//{
	//	CGLWidget::GetInstance()->updateGL();
	//}

	/// temporary
}

QList<CImage*>& CWorkspace::GetImages()
{
	return iImages;
}

void CWorkspace::paint(QPainter* painter, QRect position){
	iWorkspaceImage->fill(Qt::black);
	QListIterator<CImage*> images(iImages);
	while (images.hasNext()){
		CImage *cimage = images.next();
		QPainter *qpainter = new QPainter();
		qpainter->begin((QPaintDevice*)iWorkspaceImage); std::cout << "CWorkspace\n\n\n";
		cimage->paint(qpainter);
		qpainter->end();
	}
	painter->drawImage(position,*iWorkspaceImage);
}

void CWorkspace::mousePressEvent(QMouseEvent *event){
	iActiveImage = NULL;
	QListIterator<CImage*> images(iImages);
	images.toBack ();
	while (images.hasPrevious())
	{
		CImage* obj = images.previous();
		if(obj->IsPointOnObject(event->x(),event->y()))
		{
			iActiveImage = obj;
			iImages.move(iImages.indexOf(obj),iImages.count()-1);
			obj->mousePressEvent(event);
			SelectImage(obj);
			//UpdateTexture();
			//updateGL ();
			break;
		}
	}
//TODO	CInfoPanel::GetInstance()->SetWorkspaceInfoView();
}

MWorkspaceLayout &CWorkspace::GetLayout()
{
	return *iLayout;
}

void CWorkspace::mouseMoveEvent(QMouseEvent *event)
{
	if(iActiveImage)
	{
		iLayout->PrepareImageToMove(iActiveImage);
		iActiveImage->mouseMoveEvent(event);
		//UpdateTexture();
		//iLayout->ImageMoved(iActiveImage);
	}
}

void CWorkspace::SelectImage(CImage *image){
	if(iImages.contains(image)){
		CImageExplorer::GetInstance()->SelectImage(image->GetOwner());
		//TODO CInfoPanel::GetInstance()->SelectDerivedImage(image);
		iActiveImage = image;
		//UpdateTexture();
	}
	else{
		int usererr=1;
	}
}

void CWorkspace::RemoveImage(CImage *image)
{
	if(iImages.contains(image))
	{
		iImages.removeOne(image);
	}
	if(image==iActiveImage)
	{
		iActiveImage=NULL;
	}
	iLayout->RemoveImage(image);
	//UpdateTexture();
	if(CWidget::GetInstance())
	{
		CWidget::GetInstance()->paint();
	}
}