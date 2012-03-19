#ifndef CIMAGE
#define CIMAGE
#include <QtGui/QImage>
#include <cworkspace.h>
#include <cobject.h>

typedef enum
{
	EImageOrientationAxial = 0, //shora dolu
	EImageOrientationSagittal = 1, //zezadu dopredu
	EImageOrientationCoronal = 2//zleva doprava
}TImageAxisOrientation;

typedef enum{
	EManipNone,
	EManipAllowed,
	EManipDissalowed
}
TManipulationState;

class CWorkspace;
class CImage : public CObject{
public:
	CImage(CObject *parentWindow,QString &file, QPointF &position, QPointF &size);
	void setImageFromFile(QString filename);
	void SetParentWorkspace(CWorkspace *workspace);
	QImage* getImage();
	void SetGeometry(float x, float y, float width, float height);
	void DrawImage();
	void Init(CObject *parentWindow, QPointF& position, QPointF &size);
	CDicom3DTexture *GetTexture();
	void SetZoom(float zoom);
	void SetManipulated(TManipulationState manipulated);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	QImage* iImage;
	CWorkspace* iParentWorkspace;
	CDicom3DTexture *iTexture;
	QPointF iImageCenter;
	float iZoomFactor;
	TImageWindow iImageWindow;
	unsigned int iDisplayTextSettings;
	int iLastAxialPosition;
	int  iLastSagittalPosition;
	int iLastCoronalPosition;
	TImageAxisOrientation iImageAxisOrientation;
	QString *iName;
	//TODO CAnimation* iAnimation;
	TTextureCoordinates iActualTextureCoords;
	TSliceInfo iActualSliceTextureInfo;
	int iSum;
	float iScale;
	float iBias;
	QPointF iLockedImageCenter;
	float iLockedZoom;
	QPoint iPreviousMousePosition;
	QPoint iLockedGlobalMousePosition;
	QPointF iLockedSize ;
	QPointF iLockedPosition ;
	TManipulationState iManipulated;
	TMouseState iMouseState;
};
#endif