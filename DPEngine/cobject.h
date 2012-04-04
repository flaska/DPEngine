#ifndef GLOBJECT_H_AWDS
#define GLOBJECT_H_AWDS
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <QtGui/QtGui>
#include <dicomSerieData.h>
#include <dicom3DTexture.h>
#include <settings.h>

const int KGLObjectBorder=5;
class CWidget;


typedef enum
{
	EMouseStateNone =0,
	EMouseStateObjectMoving,
	EMouseStateObjectResizing,
	EMouseStateFrameSliderChanging,
	EMouseStateImageMoving,
	EMouseStateImageZooming,
	EMouseStateImageWindowLeveling
}TMouseState;


//forward
typedef struct
{
	QPoint position;
	QPoint size;
	int data;
}TGLIcon;

typedef struct
{
	int width;
	int height;
}TSliceInfo;


class CPoint3Df
{
public:
	CPoint3Df()
	{
		x=0;
		y=0;
		z=0;
	}
	CPoint3Df(float aX,float aY,float aZ)
	{
		x=aX;
		y=aY;
		z=aZ;
	}
public:
	float GetX()
	{
		return x;
	};
	float GetY(){
		return y;
	};
	float GetZ(){
		return z;
	};
	void SetX(float aX)
	{
		x=aX;
	};
	void SetY(float aY){
		y=aY;
	};
	void SetZ(float aZ){
		z=aZ;
	};
private:
	float x,y,z;
};
typedef struct
{
	CPoint3Df bottomLeft;
	CPoint3Df bottomRight;
	CPoint3Df topRight;
	CPoint3Df topLeft;
}TTextureCoordinates;


/**
* @class CGLObject
* @brief Abstract class for object that can be drawn onto glWidget
*/
class CObject
{
public:
	CObject();
	CObject(CObject *parentWindow, const QPointF &position, const QPointF &size );
	//TODO: virtual ~CObject();
	//TODO: virtual void initializeGL()=0;
	//TODO: virtual void resizeGL ();
	//TODO: virtual void paintGL()=0;
	void Translate();
	bool IsPointOnObject(int x, int y);
	const QPointF &GetPosition();
	const QPointF &GetSize();
	const QRect GetInnerRect();
	virtual void SetGeometry(float x, float y, float width, float height);
	const int height();
	const int width();
	void SetBorders(TBorders borders);
	void SetMoveability(bool on = true);
	void SetResizeability(bool on = true);
	void SetClosability(bool on = true);

	TBorders GetBorders()
	{
		return iBorders;
	};
	void DrawSelection();
	/* TODO: 
	virtual void mouseMoveEvent(QMouseEvent *event)=0;
	virtual void wheelEvent(QWheelEvent *event)=0;	
	virtual void mousePressEvent(QMouseEvent *event)=0;
	virtual void mouseDoubleClickEvent(QMouseEvent *event)=0;
	virtual void mouseReleaseEvent(QMouseEvent *event)=0;
	*/
	virtual void mousePressEvent(QMouseEvent *event)=0;
	virtual void mouseMoveEvent(QMouseEvent *event)=0;
	void SetBorderColor(float r, float g, float b, float alpha);
	void SetBorderColor(TColor color);
	TColor GetBorderColor();
	void DrawBorderRect();
	void DrawInnerRect(QPainter*);
	void DrawIcons(QPainter*);
	void SetInnerColor(float r, float g, float b, float alpha);
	void SetInnerColor(TColor color);
	TColor GetInnerColor();
	bool IsOnMoveIcon(int x, int y);;
	bool IsOnResizeIcon(int x, int y);;
	bool IsOnCloseIcon(int x, int y);;
	void SetSize(const QPointF &size);
	void SetPosition(const QPointF &position);
	void resizeObject();
protected:
	bool iMoveAbility;
	bool iResizeAbility;
	bool iCloseAbility;

	TGLIcon iMoveIcon;
	TGLIcon iResizeIcon;
	TGLIcon iCloseIcon;
	TColor iBorderColor;
	TColor iInnerColor;
	TBorders iBorders;
	CObject* iParentWindow;
	QPointF iPosition;
	QPointF iSize;

};
#endif
