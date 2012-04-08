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
	iLastInnerHeight = 0;
	iLastInnerWidth = 0;
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

void CWorkspace::resizeEvent(QSize size){
	if (iWorkspaceImage) delete iWorkspaceImage;
	iWorkspaceImage = new QImage(size.width(),size.height(),QImage::Format_RGB32);
	SetSize(QPointF(size.width(),size.height()));
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
		qpainter->begin((QPaintDevice*)iWorkspaceImage);
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


void CWorkspace::SetGeometry(float x, float y, float w, float h)
{
	if (iWorkspaceImage) delete iWorkspaceImage;
	iWorkspaceImage = new QImage(w,h,QImage::Format_RGB32);
	
	QPointF oldPos = iPosition;
	if(iLastInnerHeight ==0)
	{

		iLastInnerWidth = iSize.x()-GetBorders().left-GetBorders().right;
		iLastInnerHeight = iSize.y()-GetBorders().top-GetBorders().bottom;
	}
	int posxdif = x - oldPos.x();
	int posydif = y - oldPos.y();
	int innerWidth = w - GetBorders().left-GetBorders().right;
	int innerHeight = h- GetBorders().top-GetBorders().bottom;
	float sizeRatioX = (float)(innerWidth)/((float)iLastInnerWidth);
	float sizeRatioY = (float)(innerHeight)/((float)iLastInnerHeight);
	iLastInnerWidth = innerWidth;
	iLastInnerHeight = innerHeight;

	CObject::SetGeometry(x,y,w,h);

	QListIterator<CImage*> images(iImages);
	images.toFront();
	while(images.hasNext())
	{
		CImage* im = images.next();
		QPointF pos(im->GetPosition().x()-GetBorders().left,im->GetPosition().y()-GetBorders().top);
		QPointF size = im->GetSize();
		QPointF newPos;
		newPos.setX(GetBorders().left+pos.x()*sizeRatioX+posxdif*sizeRatioX);
		newPos.setY(GetBorders().top+pos.y()*sizeRatioY+posydif*sizeRatioY);
		QPointF newSize;
		newSize.setX(size.x()*sizeRatioX);
		newSize.setY(size.y()*sizeRatioY);
		im->SetGeometry(newPos.x(),newPos.y(), newSize.x(),newSize.y());
	}
	//UpdateTexture();
	
}