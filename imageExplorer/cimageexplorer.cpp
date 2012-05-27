#include <cimageexplorer.h>
#include <cwidget.h>
#include <cimage.h>
//TODO #include <infoPanel.h>
#include <workspaceManager.h>
//TODO #include <mainWindow.h>
#include <settings.h>


CImageExplorer* CImageExplorer::instance = NULL;

CImageExplorer::~CImageExplorer()
{
	instance = NULL;
	if(iScrollBar)
		delete iScrollBar;
	QListIterator<CImage*> images(iImages);
	images.toBack ();
	while (images.hasPrevious())
	{
		CImage* obj = images.previous();
		if(obj)
		{
			delete obj;
			obj = NULL;
		}
	}

}
/*
void CImageExplorer::Scrolled(int value)
{
	QListIterator<CImage*> images(iImages);
	images.toFront ();
	int relativeY=0;
	while (images.hasNext())
	{
		CImage* obj = images.next();
		if(obj)
		{
			obj->SetPosition(QPoint(obj->GetPosition().x(),relativeY-value));
			relativeY+=obj->GetSize().y();
		}
	}
	if(CGLWidget::GetInstance())
	{
		CGLWidget::GetInstance()->updateGL();
	}
}
*/
CImageExplorer* CImageExplorer::InitInstance(CGLWidget *parent, QPointF& position, QPointF &size )
{
	if(!instance)
	{
		instance = new CImageExplorer(parent, position, size);
	}
	return instance;
}


CImage* CImageExplorer::GetSelectedImage()
{
	return iActiveImage;
}

CImageExplorer* CImageExplorer::GetInstance()
{
	return instance;
}

CImageExplorer::CImageExplorer(CGLWidget *parentWindow, QPointF& position, QPointF &size ):CGLObject (parentWindow, position, size)
{	
	iActiveImage = NULL;
	iScrollBar = new QScrollBar(Qt::Vertical,parentWindow);

	iScrollBar->setMinimum(0);
	iScrollBar->setMaximum(0);
	iScrollBar->setValue(0);
	QObject::connect(iScrollBar , SIGNAL(valueChanged(int)), 
		this, SLOT(Scrolled(int))); 
	SetBorders(Settings::GetBordersConstant(EImageExplorerBorders));
	SetBorderColor(Settings::GetColorConstant(EImageExplorerBorderColor));
	SetInnerColor(Settings::GetColorConstant(EImageExplorerInnerColor));
}
/*
void CImageExplorer::CloseImage(CImage *image)
{
	if(!(iImages.contains(image)))
	{
		return;
	}
	QListIterator<CImage*> images(iImages);
	bool bRemoved=false;
	int posy=0;
	while(images.hasNext())
	{
		CImage* im=images.next();
		if(im==image)
		{
			bRemoved=true;
			posy=im->GetPosition().y();

		}
		else if(bRemoved)
		{
			int lastpos = im->GetPosition().y();
			im->SetPosition(QPoint(im->GetPosition().x(),posy));
			posy=lastpos;
		}
	}
	if(iImages.contains(image))
	{
		iImages.removeOne(image);
	}
	if(CInfoPanel::GetInstance())
	{
		CInfoPanel::GetInstance()->SetImageExplorerInfoView();
	}
}
*/
void CImageExplorer::SelectImage(CImage *image)
{
	if(iImages.contains(image))
	{
		iActiveImage = image;
	}
}

void CImageExplorer::OpenImage(QString &fileName)
{
	QPointF pos(GetBorders().left,GetBorders().top);
	if(!iImages.isEmpty())
	{
		CImage *lastImage = iImages.back();
		pos.setY (lastImage->GetPosition().y() + lastImage->GetSize().y());
	}
	pos+=iPosition;
	int width = iSize.x()-GetBorders().right-GetBorders().left-iScrollBar->size().width();
	QPointF size(width,width);
	CImage *newImage;
	if(fileName.isEmpty()){
		return;
	}
	try
	{
		newImage = new CImage(iParentWindow,fileName,pos,size);
	}
	catch(TextureNotCreatedException &e)
	{
		QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
		QString("Could not allocate texture - TextureNotCreatedException"), 0, MainWindow::iSelfS);
		msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
		msgBox.exec();
		return;

	}
	catch(DicomFramesException &e)
	{
		QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
		QString("Could not load the image - bad format"), 0, MainWindow::iSelfS);
		msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
		msgBox.exec();
		return;
	}


	newImage->SetMoveability (false);
	newImage->SetResizeability (false);
	newImage->SetTextDisplay(EDisplayTextAll, false);

	iImages.append (newImage);
	SelectImage(newImage);
	GLenum err = glGetErr();
	if(CGLWidget::GetInstance())
	{
		CGLWidget::GetInstance()->updateGL();
	}
	err = glGetErr();
	if(CInfoPanel::GetInstance())
	{
		CInfoPanel::GetInstance()->SetImageExplorerInfoView();
	}
	err = glGetErr();
	//CImage *im = new CImage(iParentWindow,fileName,pos,size);
}




/*
void CImageExplorer::DrawIcons()
{
}

void CImageExplorer::DrawTexts()
{
	TColor color= Settings::GetColorConstant(EImageExplorerTextColor);
	glColor4f(color.r, color.g, color.b, color.a);
	int fontSize = 15;
	CGLWidget::GetInstance()->renderText  (5,iSize.y()-fontSize-3,
	QString("Image Explorer: "),fontSize);
}

void CImageExplorer::initializeGL()
{

}
void CImageExplorer::paintGL()
{
	GLenum err = glGetErr();
	if(CGLWidget::GetInstance())
	{
		CGLWidget::GetInstance()->resetGLView();
	}
	Translate();
	DrawBorderRect();	
	DrawInnerRect();


	QListIterator<CImage*> images(iImages);
	int imageHeightSum = 0;

	while (images.hasNext())
	{
		CImage *im = images.next();
		imageHeightSum += im->GetSize().y();
		if(im->GetPosition().y()+im->GetSize().y()>0 
			&& im->GetPosition().y()<=iSize.y())
		{
			im->paintGL();
		}
	}

	if(iActiveImage)
	{
		iActiveImage->Translate();
		iActiveImage->DrawSelection();
	}
	iScrollBar->setVisible(true);
	if(imageHeightSum >iSize.y())
	{
		iScrollBar->setMaximum(imageHeightSum-iSize.y());
		iScrollBar->setPageStep(iSize.y());
	}
	else
	{
		iScrollBar->setMaximum(0);
	}
	if(CGLWidget::GetInstance())
	{
		CGLWidget::GetInstance()->resetGLView();
	}
	Translate();
	DrawTexts();
	return;
}


bool CImageExplorer::IsOnMoveIcon(int x, int y)
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

bool CImageExplorer::IsOnResizeIcon(int x, int y)
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

void CImageExplorer::SetGeometry(int x, int y, int width, int height)
{
	QPointF oldPos = iPosition;
	QPointF oldSize = iSize;
	CGLObject::SetGeometry(x,y,width,height);
	iScrollBar->setGeometry (
		iPosition.x()+iSize.x()-15-GetBorders().right,
		iPosition.y()+GetBorders().top,
		15,
		iPosition.y()+iSize.y()-GetBorders().top-GetBorders().bottom
		);
	QListIterator<CImage*> images(iImages);
	int posy;
	if(images.hasNext())
	{
		posy=images.next()->GetPosition().y();
	}
	images.toFront();
	while(images.hasNext())
	{
		CImage* im = images.next();
		int width = iSize.x()-GetBorders().right-GetBorders().left-iScrollBar->size().width();
		QPoint size(width,width);
		int posx=iPosition.x()+GetBorders().left;

		im->SetGeometry(posx,posy, size.x(),size.y());
		posy+=size.y();

	}
}


void CImageExplorer::wheelEvent(QWheelEvent *event)
{

}
void CImageExplorer::mouseReleaseEvent(QMouseEvent *event)
{
	if(iActiveImage)
	{
		iActiveImage->mouseReleaseEvent(event);
	}
}
void CImageExplorer::mouseDoubleClickEvent ( QMouseEvent * event )
{

	if(MainWindow::iSelfS)
	{
		MainWindow::iSelfS->OpenFile();
	}
}

void CImageExplorer::mouseMoveEvent(QMouseEvent *event)
{
	if(iActiveImage)
	{
		iActiveImage->mouseMoveEvent(event);
	}

}

void CImageExplorer::mousePressEvent(QMouseEvent *event)
{
	iActiveImage = NULL;
	QListIterator<CImage*> images(iImages);
	images.toBack ();
	while (images.hasPrevious())
	{
		CImage* obj = images.previous();
		if(obj->IsPointOnObject(event->x(),event->y()))
		{
			obj->mousePressEvent(event);
			SelectImage(obj);
			break;
		}
	}
	if(CInfoPanel::GetInstance())
	{

		CInfoPanel::GetInstance()->SetImageExplorerInfoView();
	}
}
*/