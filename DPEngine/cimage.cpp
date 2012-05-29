#include <cimage.h>
#include <cwidget.h>
#include <dicom3dtexture.h>
#include <dicom3DTextureManager.h>
#include <settings.h>
#include <cimageexplorer.h>
#include <workspacemanager.h>
#include <infopanel.h>


void CImage::setImageFromFile(QString filename){
	iActualSliceCompleteImage = new QImage(filename);
}
void CImage::SetParentWorkspace(CWorkspace *workspace)
{
	iParentWorkspace=workspace;
}

QImage* CImage::getCompleteImage(){
	return iActualSliceCompleteImage;
}

QImage* CImage::getCropImage(){
	return iActualSliceCropImage;
}

CImage::CImage(CObject *parentWindow,QString &file, QPointF& position, QPointF &size ):CObject(parentWindow,position,size)
{	
	iActualSliceCompleteImage = NULL;
	iActualSliceCropImage = NULL;
	iImageAxisOrientation=EImageOrientationAxial;
	Init(parentWindow, position, size);
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
	PrepareSlice();
}

CImage::CImage(CObject *parentWindow,CDicom3DTexture *texture, QPointF& position, QPointF &size ):CObject(parentWindow,position,size)
{	
	iImageAxisOrientation = EImageOrientationAxial;
	iActualSliceCompleteImage = NULL;
	iActualSliceCropImage = NULL;
	Init(parentWindow, position, size);
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


	iSize=size;
	iFrameSlider.position.setX( 10);
	iFrameSlider.size.setY(15);
	iFrameSlider.size.setX(iSize.x() - iFrameSlider.position.x() - 25); //iSize.x() - size.x()
	iFrameSlider.position.setY(iSize.y() - iFrameSlider.size.y()-2);
	iFrameSlider.data=0;


	PrepareSlice();
}

void CImage::PrepareSlice(){
	int y = 20*iActualTextureCoords.bottomLeft.GetZ();
	quint8* dicomrawdata8bit = (quint8*)iTexture->iFrames->GetImageData();
	dicomrawdata8bit = dicomrawdata8bit+(iTexture->iFrames->GetImagesInfo().frameQuintsCount*y) ;
	uchar * dicomrawdata16bit = (uchar*)dicomrawdata8bit;
	int dicomrawdatawidth = iTexture->iFrames->GetWidth();
	int dicomrawdataheight = iTexture->iFrames->GetHeight();
	int dicomrawdatabytesperline = iTexture->iFrames->GetWidth();
	QImage img = QImage(dicomrawdata16bit, dicomrawdatawidth, dicomrawdataheight, dicomrawdatabytesperline, QImage::Format_Indexed8);
	img = img.convertToFormat(QImage::Format_RGB32);
	if (img.isNull()) return;
	float bias = iBias*255.0;
	for (int y=0; y<dicomrawdataheight; y++){
		QRgb* imageLine=(QRgb*)img.scanLine(y);
		for (int x=0; x<dicomrawdatawidth; x++) {
			float originalintensity = (float)qRed(imageLine[x]);
			int newintensity = (int)(originalintensity*iScale+bias);
			if(newintensity>254) newintensity=254;
			if(newintensity<1) newintensity=1;
			imageLine[x]=qRgb(newintensity,newintensity,newintensity);
		}
	}
	if (iActualSliceCompleteImage)
		delete iActualSliceCompleteImage;
	iActualSliceCompleteImage = new QImage(img);
}

void CImage::PrepareImageCrop(){
	int width=iSize.x()-GetBorders().right-GetBorders().left;
	int height=iSize.y()-GetBorders().bottom-GetBorders().top;
	int xcenter = iImageCenter.x()*width;
	int ycenter = iImageCenter.y()*height;
	float xgapbefore = (xcenter - (((float)iTexture->GetWidth()/2)*iZoomFactor));
	float ygapbefore = (ycenter - (((float)iTexture->GetHeight()/2)*iZoomFactor));

	float xgapafter = (((float)iTexture->GetWidth()/2)*iZoomFactor)-(width-xcenter);
	float ygapafter = (((float)iTexture->GetHeight()/2)*iZoomFactor)-(height-ycenter);

	QPointF leftTopScaled (
		-xgapbefore/(iTexture->GetWidth() * iZoomFactor),
		-ygapbefore/(iTexture->GetHeight() * iZoomFactor)
	);
	QPointF rightBottomScaled (
		1.- (xgapafter/(iTexture->GetWidth()*iZoomFactor)),
		1.- (ygapafter/(iTexture->GetHeight()*iZoomFactor))
	);
	QPoint leftTopReal (
		leftTopScaled.x()*iActualSliceCompleteImage->width(),
		leftTopScaled.y()*iActualSliceCompleteImage->height()
	);
	QPoint rightBottomReal (
		rightBottomScaled.x()*iActualSliceCompleteImage->width(),
		rightBottomScaled.y()*iActualSliceCompleteImage->height()
	);
	if (iActualSliceCropImage)
		delete iActualSliceCropImage;
	iActualSliceCropImage = new QImage(getCompleteImage()->copy(QRect(leftTopReal,rightBottomReal)));
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
	float newDifX = oldDifX;
	float newDifY = oldDifY;
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
	//SetOrientation(EImageOrientationAxial);
	QString name;
	name.clear();
	name.append("image");
	SetName(name);
	iManipulated = EManipNone;
	iOwner = NULL;
	iParentWorkspace=NULL;
	iScale = 1.0;
	iBias = 0.3;
	iParentWindow = parentWindow;
	iPosition=position;
	iSize=size;
	//slider
	iFrameSlider.position.setX( 10);
	iFrameSlider.size.setY(15);
	iFrameSlider.size.setX(iSize.x() - iFrameSlider.position.x() - 25); //iSize.x() - size.x()
	iFrameSlider.position.setY(iSize.y() - iFrameSlider.size.y()-2);
	iFrameSlider.data=0;
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
	CWidget::GetInstance()->paint();
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
	if(event->button() == Qt::LeftButton )
	{
		iMouseState = EMouseStateImageMoving;
		return;
	}

	if(event->button() == Qt::MidButton )
	{
		iMouseState = EMouseStateImageZooming;
	}
	if(event->button() == Qt::RightButton  )
	{
		iMouseState = EMouseStateImageWindowLeveling;
	}

}

void CImage::mouseReleaseEvent(QMouseEvent *event)
{
	if(iMouseState==EMouseStateObjectMoving && iParentWorkspace)
	{
		iParentWorkspace->GetLayout().ImageMoveFinished(this);
	}
	iManipulated=EManipNone;
	CWidget::GetInstance()->paint();
	if(CInfoPanel::GetInstance())
	{
		if(CInfoPanel::GetInstance()->GetSourceImage() == this)
		{
			CInfoPanel::GetInstance()->SetSourceImage(this);
		}
	}
}

void CImage::SetImageWindow(TImageWindow window)
{
	iImageWindow = window;
	std::cout << "imagewindow width " << iImageWindow.width << std::endl;
	std::cout << "imagewindow center " << iImageWindow.center << std::endl;

	float cd= iTexture->GetWindowDefaults().center;
	float wd =iTexture->GetWindowDefaults().width;
	float bias;
	float c = (iImageWindow.center - (cd -wd/2.)) / wd;
	float w1  = ((iImageWindow.center-iImageWindow.width/2) - (cd -wd/2.)) / wd;
	float w2 = ((iImageWindow.center+iImageWindow.width/2) - (cd -wd/2.)) / wd;
	float w = w2-w1;
	w = iImageWindow.width/wd ;
	float scale = 1./w;
	bias =- (c-w/2)*scale;
	//if (scale>0.0 && scale<100.0) iScale = scale;
	//if (bias>0.0 && bias<100.0) iBias = bias;
	iScale = scale;
	iBias = bias;

	std::cout << "SetImageWindow Bias " << iBias << std::endl;
	std::cout << "SetImageWindow Scale " << iScale << std::endl;

	PrepareSlice();
	if(iParentWorkspace)
	{
		//iParentWorkspace->UpdateTexture();
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
		dx = dx * Settings::imageWindowingWidthSensitivity;
		dy = dy * Settings::imageWindowingCenterSensitivity;
		QCursor::setPos(iLockedGlobalMousePosition);
		iImageWindow.center+=dy;
		if(iImageWindow.center>65596)
			iImageWindow.center = 65096;
		//if(iImageWindow.center<0)
		//	iImageWindow.center = 0;
		iImageWindow.width+=dx;
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
	}*/
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
		PrepareImageCrop();
		//CGLWidget::GetInstance()->updateGL ();
		//return;
	}
	//TODO
	/*
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
	iPreviousMousePosition = QPoint(x, y);	
	CWidget::GetInstance()->paint();
}

void CImage::wheelEvent(QWheelEvent *event){
	if(event->delta() > 0 )
	{
		MoveToFrame(iFrameSlider.data+1);
	}
	else if(event->delta() < 0 )
	{
		MoveToFrame(iFrameSlider.data-1);
	}
	if(CInfoPanel::GetInstance())
	{
		if(CInfoPanel::GetInstance()->GetSourceImage() == this)
		{
			CInfoPanel::GetInstance()->SetSourceImage(this);
		}
	}
}

void CImage::MoveToFrame(int frame){
	float move = 0;
	int depth = GetActualTextureDepth();
	iFrameSlider.data=frame;
	if(iFrameSlider.data <= 0)
	{
		iFrameSlider.data = 0;
	}
	if(iFrameSlider.data >= depth)
	{
		iFrameSlider.data = depth-1;
	}
	if((depth-1)!=0)
	{
	move=(float)iFrameSlider.data/(depth-1);
	}
	else
	{
		move = 0;
	}
	MoveToDepth(move);
}

void CImage::MoveToDepth(float inDepthPosition)
{
	switch(iImageAxisOrientation)
	{
	case EImageOrientationAxial:
		{

			iActualTextureCoords.bottomLeft.SetZ(inDepthPosition);
			iActualTextureCoords.bottomRight.SetZ(inDepthPosition);
			iActualTextureCoords.topLeft.SetZ(inDepthPosition);
			iActualTextureCoords.topRight.SetZ(inDepthPosition);
		}
		break;
	case EImageOrientationSagittal:
		{

			iActualTextureCoords.bottomLeft.SetX(inDepthPosition);
			iActualTextureCoords.bottomRight.SetX(inDepthPosition);
			iActualTextureCoords.topLeft.SetX(inDepthPosition);
			iActualTextureCoords.topRight.SetX(inDepthPosition);
		}
		break;
	case EImageOrientationCoronal: //zezadu dopredu
		{

			iActualTextureCoords.bottomLeft.SetY(inDepthPosition);
			iActualTextureCoords.bottomRight.SetY(inDepthPosition);
			iActualTextureCoords.topLeft.SetY(inDepthPosition);
			iActualTextureCoords.topRight.SetY(inDepthPosition);
		}
		break;
	default:
		break;
	}
	iFrameSlider.data=(float)(inDepthPosition*(GetActualTextureDepth()));
	if(iFrameSlider.data>= GetActualTextureDepth())
	{
		iFrameSlider.data = GetActualTextureDepth()-1;
	}
	PrepareSlice();
	//if(iParentWorkspace)
	//{
	//	iParentWorkspace->UpdateTexture();
	//}
	CWidget::GetInstance()->paint();
}

float CImage::GetActualTextureDepth()
{
	//TODO compute it better ??
	switch(iImageAxisOrientation)
	{
	case EImageOrientationAxial:
		{
			return iTexture->GetDepth();
		}
		break;
	case EImageOrientationSagittal:
		{
			return iTexture->GetWidth();
		}
		break;
	case EImageOrientationCoronal:
		{
			return iTexture->GetHeight();
		}
		break;
	default:
		{
			return iTexture->GetDepth();
		}
	}
}

TImageAxisOrientation CImage::GetOrientation()
{
	//return iImageAxisOrientation;
	return EImageOrientationAxial;
}

QList<CImage *>& CImage::GetDerivedImages()
{
	return iDerivedImages;
}

CWorkspace * CImage::GetParentWorkspace()
{
	return iParentWorkspace;
}

QString& CImage::GetName()
{
	return *iName;
}

void CImage::SetName(const QString& name)
{
	iName->clear();
	iName->append(name);
}

CImage* CImage::CreateDerivedImage(TImageAxisOrientation orientation)
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
		newImage = new CImage(CWorkspaceManager::GetInstance()->GetActiveWorkspace(),
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
	iDerivedImages.append(newImage);
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
	PrepareImageCrop();
	QImage img = getCropImage()->copy();
	if (img.isNull()) return;
	painter->drawImage(QRect(QPoint(GetPosition().x()+GetBorders().left,GetPosition().y()+GetBorders().top),QPoint(GetPosition().x()+GetSize().x()-GetBorders().right,GetPosition().y()+GetSize().y()-GetBorders().bottom)),img);
	DrawBorderRect(painter);
	DrawIcons(painter);
}

float CImage::GetZoom()
{
	return iZoomFactor;
}

int CImage::GetActualFrameNr()
{
	return iFrameSlider.data;
}