#include <cimage.h>
#include <cwidget.h>
#include <dicom3dtexture.h>
#include <dicom3DTextureManager.h>
#include <settings.h>
#include <cimageexplorer.h>
void CImage::setImageFromFile(QString filename){
	iImage = new QImage(filename);
}
void CImage::SetParentWorkspace(CWorkspace *workspace)
{
	iParentWorkspace=workspace;
}

QImage* CImage::getImage(){
	return iImage;
}

CImage::CImage(CObject *parentWindow,QString &file, QPointF& position, QPointF &size ):CObject(parentWindow,position,size)
{	
	if(!C3DTextureManager::GetInstance())
	{
//TODO		throw TextureNotCreatedException(); 
	}
	iTexture = NULL;
	iTexture= C3DTextureManager::GetInstance()->LoadTexture(file);
	if(!iTexture)
	{
		//TODO throw TextureNotCreatedException(); 
	}
	Init(parentWindow, position, size);
	iImageWindow = iTexture->GetWindowDefaults();
	/* //TODO if(!InitSliceTexture())
	{
		int err=1;
	}*/
	iImageWindow.center=int((iImageWindow.center )/CDicomFrames::iWindowMultiplyFactor);
	iImageWindow.width=int((iImageWindow.width )/CDicomFrames::iWindowMultiplyFactor);
	//PrepareActualTexture();

	quint8* qi = (quint8*)iTexture->iFrames->GetImageData();
	uchar * qu = (uchar*)qi;
	QImage img = QImage(qu, iTexture->iFrames->GetWidth(), iTexture->iFrames->GetHeight(), iTexture->iFrames->GetWidth(), QImage::Format_Indexed8);	
	iImage = new QImage(img.convertToFormat(QImage::Format_RGB32)); 

}

CImage::CImage(CObject *parentWindow,CDicom3DTexture *texture, QPointF& position, QPointF &size ):CObject(parentWindow,position,size)
{	
	if(!texture)
	{
//TODO		throw DicomFramesException();
	}
	iTexture= texture;
	if(!iTexture)
	{
		//TODO throw TextureNotCreatedException(); 
	}
	Init(parentWindow, position, size);
	iImageWindow = iTexture->GetWindowDefaults();
	/* //TODO if(!InitSliceTexture())
	{
		int err=1;
	}*/
	iImageWindow.center=int((iImageWindow.center )/CDicomFrames::iWindowMultiplyFactor);
	iImageWindow.width=int((iImageWindow.width )/CDicomFrames::iWindowMultiplyFactor);
	//PrepareActualTexture();

	quint8* qi = (quint8*)iTexture->iFrames->GetImageData();
	uchar * qu = (uchar*)qi;
	iImage = new QImage(qu, iTexture->iFrames->GetWidth(), iTexture->iFrames->GetHeight(), iTexture->iFrames->GetWidth(), QImage::Format_Indexed8);
}

void CImage::SetGeometry(float x, float y, float width, float height)
{
	QPointF oldPos=iPosition;
	QPointF oldSize=iPosition;
	iPosition.setX(x);
	iPosition.setY(y);
	//recompute image center coord to guarantee that image center will be kept
	float oldWidth=iSize.x();
	float oldHeight = iSize.y();
	QPointF oldCenter = iImageCenter;
	float oldCenterX = oldCenter.x()*oldWidth;
	float oldCenterY = oldCenter.y()*oldHeight;
	float oldDifX = oldCenterX-(float)oldWidth/2;
	float oldDifY = oldCenterY-(float)oldHeight/2;
	float newDifX = oldDifX /** (float)(oldWidth/width);*/;
	float newDifY = oldDifY /** (float)(oldHeight/height)*/;
	iImageCenter.setX((float)((float)width/2.+newDifX) / (float)width);
	iImageCenter.setY((float)((float)height/2.+newDifY)/(float)height);
	iSize.setX (width);
	iSize.setY (height);

	/*//TODO //slider
	iFrameSlider.position.setX( 10);

	iFrameSlider.size.setY(15);
	iFrameSlider.size.setX(iSize.x() - iFrameSlider.position.x() - 25); //iSize.x() - size.x()
	iFrameSlider.position.setY(iSize.y() - iFrameSlider.size.y()-2);
	*/
	if(iParentWorkspace)
	{
		//TODO iParentWorkspace->UpdateTexture();
	}
	resizeObject();
}

void CImage::DrawImage(){
	int width=iSize.x()-GetBorders().right-GetBorders().left;
	int height=iSize.y()-GetBorders().bottom-GetBorders().top;
	int xcenter = iImageCenter.x()*width;
	int ycenter = iImageCenter.y()*height;
	float xgapbefore = (xcenter - (((float)iTexture->GetWidth()/2)*iZoomFactor));
	float ygapbefore = (ycenter - (((float)iTexture->GetHeight()/2)*iZoomFactor));
	float xgapafter = (((float)iTexture->GetWidth()/2)*iZoomFactor)-(width-xcenter);
	float ygapafter = (((float)iTexture->GetHeight()/2)*iZoomFactor)-(height-ycenter);
	QPointF leftTopTex (
		-xgapbefore/(iTexture->GetWidth() * iZoomFactor),
		-ygapbefore/(iTexture->GetHeight() * iZoomFactor)
		);
	QPointF rightBottomTex (
		1.- (xgapafter/(iTexture->GetWidth()*iZoomFactor)),
		1.- (ygapafter/(iTexture->GetHeight()*iZoomFactor))
		);
	QPointF leftTop (GetBorders().left,iSize.y()-GetBorders().top);
	QPointF rightBottom (iSize.x()-GetBorders().right,GetBorders().bottom);
}

void CImage::Init(CObject *parentWindow, QPointF& position, QPointF &size )
{
	iLastAxialPosition = 0;
	iLastSagittalPosition = 0;
	iLastCoronalPosition = 0;
	iParentWorkspace = NULL;
//TODO	iAnimation = NULL;
	iName = new QString();
//TODO	SetOrientation(EImageOrientationAxial);
	QString name;
	name.clear();
	name.append("image");
//TODO	SetName(name);
	iManipulated = EManipNone;
//TODO	CWidget::GetInstance()->makeCurrent();
//TODO	iOwner = NULL;
	iParentWorkspace=NULL;
	iScale = 1.0;
	iBias = 0.3;
	iParentWindow = parentWindow;
	iPosition=position;
	iSize=size;
	//slider
//TODO	iFrameSlider.position.setX( 10);
//TODO	iFrameSlider.size.setY(15);
//TODO	iFrameSlider.size.setX(iSize.x() - iFrameSlider.position.x() - 25); //iSize.x() - size.x()
//TODO	iFrameSlider.position.setY(iSize.y() - iFrameSlider.size.y()-2);
//TODO	iFrameSlider.data=0;
	//	iFrames = NULL;
	iZoomFactor=1.0;
	iImageCenter = QPointF(0.5,0.5);
	iImageWindow.center = 1<<11;
	iImageWindow.width = 1<<11;
	iActualTextureCoords.bottomLeft = CPoint3Df(0,0,0);
	iActualTextureCoords.bottomRight = CPoint3Df(1,0,0);
	iActualTextureCoords.topRight = CPoint3Df(1,1,0);
	iActualTextureCoords.topLeft = CPoint3Df(0,1,0);
	SetMoveability(true);
	SetResizeability(true);
	SetClosability(true);
//TODO	SetOpenGLInterpolation(true);
	SetBorders(Settings::GetBordersConstant(EImageBorders));
	SetBorderColor(Settings::GetColorConstant(EImageBorderColor));
	SetInnerColor(Settings::GetColorConstant(EImageInnerColor));
	iDisplayTextSettings = 0;
//TODO	SetTextDisplay(EDisplayTextOrientation, false);
//TODO	SetTextDisplay(EDisplayTextZoom, true);
//TODO	SetTextDisplay(EDisplayTextWindow, false);
//TODO	SetTextDisplay(EDisplayTextOrientation, true);
//TODO	SetTextDisplay(EDisplayTextWindow, true);
//TODO	SetTextDisplay(EDisplayTextZoom, false);
}

void CImage::SetZoom(float zoom)
{
	iZoomFactor=zoom;
	if(iParentWorkspace)
	{
		//iLayout->PrepareImageToMove(iActiveImage);
		//TODO iParentWorkspace->UpdateTexture();
	}
	//TODO CWidget::GetInstance()->paint();
}

CDicom3DTexture *CImage::GetTexture()
{
	return iTexture;
}

void CImage::SetManipulated(TManipulationState manipulated)
{

	iManipulated=manipulated;
}

void CImage::mousePressEvent(QMouseEvent *event)
{
	//iSkipMouseMovement = false;
	iMouseState = EMouseStateNone;
	//locked states
	iLockedGlobalMousePosition = event->globalPos();
	//Save previous object state
	iLockedSize = iSize;
	iLockedPosition = iPosition;
	iLockedImageCenter = iImageCenter;
	iLockedZoom=iZoomFactor;
	int x=event->x() - iPosition.x();
	int y = event->y()- iPosition.y();
	iPreviousMousePosition = QPoint(x, y);	


	if(IsOnResizeIcon(x, y))
	{
		iMouseState=EMouseStateObjectResizing;
		if(iParentWorkspace)
		{
			iParentWorkspace->GetLayout().PrepareImageToResize(this);
		}
		iManipulated=EManipAllowed;

		return;		
	}
	if(IsOnMoveIcon(x, y))
	{
		iMouseState=EMouseStateObjectMoving;
		if(iParentWorkspace)
		{
			iParentWorkspace->GetLayout().PrepareImageToMove(this);
		}

		//iManipulated=true;

		return;

	}

	if(IsOnCloseIcon(x, y))
	{
		CloseMe();
		delete this;
		return;

	}
	/* //TODO 
	if(IsOnFrameSliderIcon(x, y))
	{
		iMouseState=EMouseStateFrameSliderChanging;
		return;		
	}
*/
	/*if(event->button() == Qt::LeftButton )
	{
		iMouseState = EMouseStateImageMoving;
		return;
	}

	if(event->button() == Qt::MidButton )
	{
		iMouseState = EMouseStateImageZooming;
	}*/
	if(event->button() == Qt::RightButton  )
	{
		iMouseState = EMouseStateImageWindowLeveling;
	}

}

void CImage::SetImageWindow(TImageWindow window)
{
	iImageWindow = window;
	//PrepareActualTexture();
	if(iParentWorkspace)
	{
		//iParentWorkspace->UpdateTexture();
		std::cout << iImageWindow.center;
	}
	CWidget::GetInstance()->paint();
}

TImageWindow CImage::GetImageWindow()
{
	return iImageWindow;
}

void CImage::mouseMoveEvent(QMouseEvent *event)
{
	int x=event->x() - iPosition.x();
	int y = event->y()- iPosition.y();
	int dx = x-iPreviousMousePosition.x();
	int dy = y-iPreviousMousePosition.y();

	if(EMouseStateImageWindowLeveling==iMouseState)
	{
		QCursor::setPos(iLockedGlobalMousePosition);
		iImageWindow.center+=4*dy;
		if(iImageWindow.center>65596)
			iImageWindow.center = 65096;
		iImageWindow.width+=4*dx;
		if(iImageWindow.width>65096)
			iImageWindow.width = 65096;
		if(iImageWindow.width<1)
			iImageWindow.width = 1;
		SetImageWindow(iImageWindow);
		return;
	}
	/*
	else if(iMouseState == EMouseStateFrameSliderChanging )
	{
		QCursor::setPos(event->globalPos().x(),iLockedGlobalMousePosition.y());
		IsOnFrameSliderIcon (x,y);

		return;
	}
	else if(iMouseState == EMouseStateImageZooming)
	{
		QCursor::setPos(iLockedGlobalMousePosition);
		SetZoom(iZoomFactor*(1.-(float)dy/100.));
		iImageCenter.setX((x-(x-iLockedImageCenter.x()*iSize.x())*(iZoomFactor/iLockedZoom))/iSize.x());
		iImageCenter.setY((y-(y-iLockedImageCenter.y()*iSize.y())*(iZoomFactor/iLockedZoom))/iSize.y());
		
		return;
	}
	else 
	
	if(iMouseState == EMouseStateImageMoving)
	{
		iImageCenter.setX(iImageCenter.x()+(float)dx/iSize.x());
		iImageCenter.setY(iImageCenter.y()+(float)dy/iSize.y());
		if(iParentWorkspace)
		{
			//iParentWorkspace->UpdateTexture();
		}
		//CGLWidget::GetInstance()->updateGL ();
		//return;
	}
	//TODO
	
	else */
	if(iMouseState == EMouseStateObjectMoving)
	{
		dx=event->globalPos().x()-iLockedGlobalMousePosition.x();
		dy=event->globalPos().y()-iLockedGlobalMousePosition.y();

		SetGeometry(iLockedPosition.x()+dx,
			iLockedPosition.y()+dy ,
			iSize.x(),
			iSize.y());
		if(iParentWorkspace)
		{
			iParentWorkspace->GetLayout().ImageMoved(this);
		}
		//TODO CGLWidget::GetInstance()->updateGL ();
		//return; //to avoid updating of previous mouse position
	}
	else if(iMouseState == EMouseStateObjectResizing)
	{

		dx=event->globalPos().x()-iLockedGlobalMousePosition.x();
		dy=event->globalPos().y()-iLockedGlobalMousePosition.y();
		SetGeometry(iPosition.x(),iPosition.y(),
			iLockedSize.x()+dx,
			iLockedSize.y()+dy);
		//iPreviousMousePosition = QPoint(iSize.x(), iSize.y());
		if(iParentWorkspace)
		{
			iParentWorkspace->GetLayout().ImageResized(this);
		}
		//CGLWidget::GetInstance()->updateGL ();
		//return;

	}/*
	iPreviousMousePosition = QPoint(x, y);	
	//iPreviousGlobalMousePosition = event->globalPos();
	*/
	CWidget::GetInstance()->paint();
}

CImage* CImage::CreateDerivedImage(/*TImageAxisOrientation orientation*/)
{
/*TODO	if(!CWorkspaceManager::GetInstance()->GetActiveWorkspace())
	{
		QMessageBox msgBox(QMessageBox::Warning, QObject::tr("QMessageBox::warning()"),
		QString("No active workspace to add image to"), 0, MainWindow::iSelfS);
		msgBox.addButton(QObject::tr("&Continue"), QMessageBox::RejectRole);
		msgBox.exec();
		return NULL;
	}*/
	QPointF pos(2,2);
	QPointF size(iSize.x(), iSize.y());
	CImage *newImage;
//	try
//	{
		newImage = new CImage(NULL/*CWorkspaceManager::GetInstance()->GetActiveWorkspace()*/,
			C3DTextureManager::GetInstance()->GetTexture(this->GetTexture()->GetIdentificationString()),pos,size);
//	}
/*TODO	catch(DicomFramesException &e)
	{
		QMessageBox msgBox(QMessageBox::Warning, QObject::tr("QMessageBox::warning()"),
			QString("Could not allocate texture"), 0, MainWindow::iSelfS);
		msgBox.addButton(QObject::tr("&Continue"), QMessageBox::RejectRole);
		msgBox.exec();
		ImLog.write("End: *CGLImage::CreateDerivedImage");
		return NULL;

	}*/
	CWidget::GetInstance()->paint();
	newImage->SetOwner(this);
	QString name("Im:");
	//TODOname.append(QString::number(iDerivedImages.count()));
	//newImage->SetName(name);
	//iDerivedImages.append(newImage);
	//newImage->SetOrientation(orientation);
	return newImage;
}

CImage *CImage::GetOwner(){
	return iOwner;
}

void CImage::SetOwner(CImage *owner){
	iOwner=owner;
}

void CImage::CloseMe()
{
/*	if(CAnimationManager::GetInstance())
	{
		//removes the animation if exists
		CAnimationManager::GetInstance()->RemoveAnimation(this);

	}
	if(CInfoPanel::GetInstance())
	{
		if(CInfoPanel::GetInstance()->GetSourceImage() == this)
		{
			CInfoPanel::GetInstance()->SetSourceImage(NULL);
		}
	}*/
	iMouseState=EMouseStateNone;
	if(iParentWorkspace)
	{
		if(GetOwner())
		{
			GetOwner()->RemoveDerivedImage(this);
		}
		iParentWorkspace->RemoveImage(this);

	}
	if(CImageExplorer::GetInstance())
	{
		CImageExplorer::GetInstance()->CloseImage(this);
	}
	QListIterator<CImage*> derivedImages(iDerivedImages);
	while(derivedImages.hasNext())
	{
		CImage* im=derivedImages.next();
		im->SetOwner(NULL);
		im->CloseMe();
		delete im;
	}
	iDerivedImages.clear();
}

void CImage::RemoveDerivedImage(CImage* image)
{
	if(iDerivedImages.contains(image))
	{
		iDerivedImages.removeOne(image);
	}
}

void CImage::paint(QPainter* painter){
	QImage img = getImage()->convertToFormat(QImage::Format_RGB32);
	//QImage img = *iImage;
	//img->
	painter->drawImage(QRect(QPoint(GetPosition().x(),GetPosition().y()),QPoint(GetPosition().x()+GetSize().x(),GetPosition().y()+GetSize().y())),img);
	DrawInnerRect(painter);
	DrawIcons(painter);
}