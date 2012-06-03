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

typedef enum
{
	EDisplayTextZoom = 1,
	EDisplayTextOrientation = 2,
	EDisplayTextWindow = 4,
	EDisplayTextFrameData = 8,
	EDisplayTextAll = 1073741823
}TDiplayText;

class CWorkspace;
class CImage : public CObject{
public:
	CImage(CObject *parentWindow,QString &file, QPointF &position, QPointF &size);
	CImage(CObject *parentWindow,CDicom3DTexture *texture, QPointF& position, QPointF &size );
	void Init(CObject *parentWindow, QPointF& position, QPointF &size);
	void setImageFromFile(QString filename);
	void SetParentWorkspace(CWorkspace *workspace);
	QImage* getCompleteImage();
	QImage* getCropImage();
	void SetGeometry(float x, float y, float width, float height);
	void DrawImage();
	CDicom3DTexture *GetTexture();
	void SetZoom(float zoom);
	void SetManipulated(TManipulationState manipulated);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	CImage* CreateDerivedImage(TImageAxisOrientation orientation);
	CImage *GetOwner();
	void SetOwner(CImage *owner);
	void CloseMe();
	void RemoveDerivedImage(CImage* image);
	TImageWindow GetImageWindow();
	void SetImageWindow(TImageWindow window);
	void paint(QPainter*);
	void wheelEvent(QWheelEvent *event);
	float GetActualTextureDepth();
	float GetZoom();
	int GetActualFrameNr();
	void MoveToFrame(int frame);
	TImageAxisOrientation GetOrientation();
	QList<CImage *>& GetDerivedImages();
	CWorkspace* GetParentWorkspace();
	QString& GetName();
	void SetName(const QString& name);
	void DrawManipulation(QPainter* painter);
	void DrawTexts(QPainter* painter);
	bool GetTextDisplay(TDiplayText displayText);
	void SetTextDisplay(TDiplayText displayText, bool on);
	void save(QString& filename);
	void SetOrientation(TImageAxisOrientation orientation);
	quint8* dicomrawdata8bitCopy;
	quint8* dicomrawdata8bitCopy2;

private:
	void MoveToDepth(float inDepthPosition);
	QImage* iActualSliceCompleteImage;
	QImage* iActualSliceCropImage;
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
	QList<CImage *> iDerivedImages;
	CImage *iOwner;
	void PrepareSlice();
	void PrepareImageCrop();
	TGLIcon iFrameSlider;
};
#endif