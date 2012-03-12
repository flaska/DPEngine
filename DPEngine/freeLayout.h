#ifndef CFreeLayout_H_asdasd456
#define CFreeLayout_H_asdasd456

//#include <GL/glew.h>
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtGui/QScrollBar>
#include <dicomSerieData.h>
#include <dicom3DTexture.h>

//#include <cobject.h>
#include <cimage.h>
#include <workspaceLayout.h>

//forward
class CImage;
class CWorkspace;
class MWorkspaceLayout;


class CFreeLayout:public MWorkspaceLayout
{
public:
	CFreeLayout(CWorkspace *parentWorkspace);

	virtual ~CFreeLayout();
public:
	void Do();
	//void AddImage(CGLImage *image);	
	virtual bool PrepareNewImageGeometry(CImage *image);
	virtual void RemoveImage(CImage *image);
	virtual void PrepareImageToMove(CImage *image);
	virtual void ImageMoveFinished(CImage *image);
	virtual void ImageMoved(CImage *image);
	virtual void PrepareImageToResize(CImage *image);
	virtual void ImageResized(CImage *image);
	
	virtual TLayoutType GetType();
//	QList<CGLImage*>& GetImages();
	
protected:
};
#endif
