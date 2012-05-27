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
class CImageExplorer: public QObject, public CGLObject
{
	Q_OBJECT
private:
	CImageExplorer(CGLWidget *parentWindow, QPointF &position, QPointF &size);
public:
	virtual ~CImageExplorer();
	static CImageExplorer* GetInstance();
	static CImageExplorer* InitInstance(CGLWidget *parent, QPointF& position, QPointF &size );
	void OpenImage(QString &fileName);
	void CloseImage(CImage *image);
	void SelectImage(CImage *image);
//	void initializeGL();
	void DrawIcons();
	void DrawTexts();
//TODO	void paintGL();
/*	void SetGeometry(int x, int y, int width, int height);
	void mouseMoveEvent(QMouseEvent *event);
	bool IsOnMoveIcon(int x, int y);;
	bool IsOnResizeIcon(int x, int y);;
	void wheelEvent(QWheelEvent *event);	
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);		
	void mouseReleaseEvent(QMouseEvent *event);
CImage* GetSelectedImage();
	public slots:
	void Scrolled(int value);
*/
private:
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
