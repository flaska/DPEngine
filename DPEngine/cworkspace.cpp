#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <cworkspace.h>
#include <cimage.h>
#include <freelayout.h>
#include <growinggridlayout.h>
#include <settings.h>
CWorkspace::CWorkspace(){
	iWorkspaceImage = new QImage(800,800,QImage::Format_RGB32);
	iWorkspaceImage->fill(Qt::yellow);
	SetSize(QPointF(800,800));
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

void CWorkspace::paint(){
	iWorkspaceImage->fill(Qt::black);
	QListIterator<CImage*> images(iImages);
	while (images.hasNext()){
		CImage *im = images.next();
		QPainter painter((QPaintDevice*)iWorkspaceImage);
		QImage img(im->getImage()->convertToFormat(QImage::Format_RGB32));
		//painter.drawImage(QRect(QPoint(im->GetPosition().x(),im->GetPosition().y()),QPoint(im->GetPosition().x()+im->GetSize().x(),im->GetPosition().y()+im->GetSize().y())),img);	
		painter.drawImage(QRect(QPoint(im->GetPosition().x(),im->GetPosition().y()),QPoint(im->GetPosition().x()+im->GetSize().x(),im->GetPosition().y()+im->GetSize().y())),img);
	}
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
//TODO		SelectImage(obj);
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
		//iLayout->PrepareImageToMove(iActiveImage);
		iActiveImage->mouseMoveEvent(event);
		//UpdateTexture();
		//iLayout->ImageMoved(iActiveImage);
	}
}