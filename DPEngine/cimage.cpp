#include <cimage.h>
#include <cwidget.h>
#include <dicom3dtexture.h>
#include <dicom3DTextureManager.h>
#include <settings.h>
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
	//TODO: prekreslit snimek v workspace kemo
	
	
	//iImage = new QImage("im.pgm");
	//iImage = new QImage((uchar*)iTexture->iFrames->GetImageData(),iTexture->iFrames->GetWidth(),iTexture->iFrames->GetHeight(),/*16,*/QImage::Format_ARGB32);

quint16* qi = (quint16*)iTexture->iFrames->GetImageData();
uchar * qu = (uchar*)qi;
QImage *img = new QImage(qu, iTexture->iFrames->GetWidth(), iTexture->iFrames->GetHeight(), 2*iTexture->iFrames->GetWidth(), QImage::Format_Indexed8);
QLabel *l = new QLabel();
QPixmap *pix = new QPixmap(2,2);
pix->convertFromImage(*img);
l->setPixmap(*pix); 
l->show();


/*uchar pixDataRGB[] = {255, 0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0};
QImage *img = new QImage(pixDataRGB, 2, 2, 6, QImage::Format_RGB888);
QImage scaled = img->scaled(100, 100);
QLabel *l = new QLabel();
QPixmap *pix = new QPixmap(2,2);
pix->convertFromImage(scaled);
l->setPixmap(*pix); 
l->show();*/


	
	
		/*uchar * data = new uchar();
		for (int y=0;y<10;y++)
			for (int x; x<10; x++)
				data[y*10+x]=x+y;
		iImage = new QImage(data,10,10,10,QImage::Format_ARGB32);
		QLabel *l;
		QPixmap *pix;
		pix->convertFromImage(*iImage);
		l->setPixmap(*pix);
		l->show();*/
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
	//resizeGL();
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
//TODO	iManipulated = EManipNone;
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