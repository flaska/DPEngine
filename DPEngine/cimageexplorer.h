#ifndef GLIMAGEEXPLORER_H_AWDS
#define GLIMAGEEXPLORER_H_AWDS
#include <Qt/qobject.h>
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtGui/QScrollBar>
#include <dicomSerieData.h>
#include <dicom3DTexture.h>
#include <CObject.h>

//forward
class CWidget;
class CImage;
class CWidget;
class CImageExplorer: public QObject, public CObject
{
	//Q_OBJECT
private:
	CImageExplorer(CWidget *parentWindow, QPointF &position, QPointF &size);
public:
	void wheelEvent(QWheelEvent *event);
	CImage* GetSelectedImage();
	virtual ~CImageExplorer();
	static CImageExplorer* GetInstance();
	static CImageExplorer* InitInstance(CWidget *parent, QPointF& position, QPointF &size );
	void OpenImage(QString &fileName);
	void CloseImage(CImage *image);
	void SelectImage(CImage *image);
//	void initializeGL();
	void DrawIcons();
	void DrawTexts();
	void SetGeometry(int x, int y, int width, int height);
//TODO	void paintGL();
/*	void SetGeometry(int x, int y, int width, int height);
	void mouseReleaseEvent(QMouseEvent *event);
	bool IsOnMoveIcon(int x, int y);;
	bool IsOnResizeIcon(int x, int y);;
	void wheelEvent(QWheelEvent *event);	
	void mouseDoubleClickEvent(QMouseEvent *event);
*/
	void mousePressEvent(QMouseEvent *event);	
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
/*
	public slots:
	void Scrolled(int value);ja 
*/
	void paint(QPainter*);
//private:
	static CImageExplorer* instance;
	QList<CImage*> iImages;
	CImage *iActiveImage;
	QScrollBar *iScrollBar;
	QPoint iPreviousMousePosition;
	QPoint iLockedGlobalMousePosition;	
	TMouseState iMouseState;
	TGLIcon iMoveIcon;
	TGLIcon iResizeIcon;
};
#endif
