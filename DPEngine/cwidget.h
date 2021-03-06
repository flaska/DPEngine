#ifndef _CWIDGET_H
#define _CWIDGET_H

#include <QtGui/QtGui>
#include <cobject.h>
#include <cworkspaceexplorer.h>

class CImageExplorer;
typedef enum
{
	CloseIcon,
	MoveIcon,
	ResizeIcon
}TIconType;
class CWidget : public QLabel, public CObject {
//	Q_OBJECT 
public:
	CWidget(QWidget *parent);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paint();
	static CWidget *GetInstance();
	static CWidget* InitInstance(QWidget *parent);
	const int width();
	const int height();
	void SetGeometry(int x, int y, int w, int h);
	QPixmap* getWidgetImage();
	QPointF GetDefaultWorkspaceSize();
	QPointF GetDefaultWorkspacePosition();
//private:
	static CWidget *instance;
	CObject *iActiveObject;
	CImageExplorer* iImageExplorer;
	QImage* getIcon(TIconType type);
private:
	void resizeEvent(QResizeEvent*);
	QImage *iImageMoveIcon;
	QImage *iImageResizeIcon;
	QImage *iImageCloseIcon;
	void LoadIcons();
	CWorkspaceExplorer *iWorkspaceExplorer;
};

#endif
