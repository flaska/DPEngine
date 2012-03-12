#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <cworkspace.h>
#include <cimage.h>
#include <freelayout.h>
#include <growinggridlayout.h>
#include <settings.h>
CWorkspace::CWorkspace(){
	iWorkspaceImage = new QImage(1024,768,QImage::Format_RGB16);
	SetSize(QPointF(1024,768));
	iLayout = new CGrowingGridLayout(this,EGrowinGridLayoutHorizontal);
	TBorders b;
	b.bottom=0;
	b.left=0;
	b.right=0;
	b.top=0;
	this->SetBorders(b);
}

/*
void CWorkspace::setImageFromFile(QString filename){
	iWorkspaceImage->load(filename);
}*/

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
	QListIterator<CImage*> images(iImages);
	while (images.hasNext()){
		CImage *im = images.next();
		QPainter painter((QPaintDevice*)iWorkspaceImage);
		painter.drawImage(QRect(QPoint(im->GetPosition().x(),im->GetPosition().y()),QPoint(im->GetPosition().x()+im->GetSize().x(),im->GetPosition().y()+im->GetSize().y())),*(im->getImage()));
	}
}