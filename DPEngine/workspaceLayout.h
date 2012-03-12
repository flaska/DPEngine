#ifndef MWORKSPACELAYOUT_H_asdasd456
#define MWORKSPACELAYOUT_H_asdasd456

#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtGui/QScrollBar>
#include <cimage.h>
#include <cworkspace.h>
#include <dicomSerieData.h>
#include <dicom3DTexture.h>
//#include <glObjects/glImage.h>


//forward
class CWorkspace;
class CImage;

//types of layouts
typedef enum
{
ELayoutGrowingGridVertical = 0,
ELayoutGrowingGridHorizontal = 1,
ELayoutFree =2
}
TLayoutType;

class MWorkspaceLayout
{
public:

	virtual ~MWorkspaceLayout() =0;
public:
	//void AddImage(CGLImage *image);	
	virtual bool PrepareNewImageGeometry(CImage *image) = 0;
	virtual void RemoveImage(CImage *image) = 0;
	virtual void PrepareImageToMove(CImage *image) = 0;
	virtual void ImageMoveFinished(CImage *image) = 0;
	virtual void ImageMoved(CImage *image) = 0;
	virtual void PrepareImageToResize(CImage *image) = 0;
	virtual void ImageResized(CImage *image) = 0;
	virtual void ImageMovedAlignToWorkspace(CImage *image);
	virtual void ImageMovedAlignToOtherImages(CImage *image);
	
	virtual void ImageResizedAlignToWorkspace(CImage *image);
	virtual void ImageResizedAlignToOtherImages(CImage *image);
	
	virtual TLayoutType GetType() = 0;
	virtual bool IsInRange(int a, int b, int tolerance);
	virtual void Do()=0;//redo layou
//	QList<CGLImage*>& GetImages();
	
protected:
	CWorkspace *iParentWorkspace;
	CImage *iCurrentImage;//being moved resized
	QPointF iImageLastPosition;
	QPointF iImageLastSize;
};
#endif
