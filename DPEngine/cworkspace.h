#ifndef CWORKSPACE
#define CWORKSPACE
#include <QtGui/QImage>
#include <cimage.h>
#include <cobject.h>
#include <workspacelayout.h>
#include <cworkspacesnapshot.h>

class CImage;
class MWorkspaceLayout;
class CWorkspaceSnapshot;
class CWorkspace : public CObject {
public:
	CWorkspace();
	CWorkspace(CObject *parent, const QPointF &position, const QPointF &size);
	//void setImageFromFile(QString filename);
	void wheelEvent(QWheelEvent *event);
	void addImage(CImage* im);
	QList<CImage*>& GetImages();
	void paint(QPainter*, QRect);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	MWorkspaceLayout &GetLayout();
	void SelectImage(CImage *image);
	void RemoveImage(CImage *image);
	void SetGeometry(float x, float y, float w, float h);
	CWorkspaceSnapshot& GetSnapshot();
	CImage* GetActiveImage();
	QString& GetName();
//private:
	QString* iName;
	MWorkspaceLayout *iLayout;
	QImage* iWorkspaceImage;
	QList<CImage*> iImages;
	CImage *iActiveImage;
	void resizeEvent(QSize size);
	float iLastInnerHeight;
	float iLastInnerWidth;
	CWorkspaceSnapshot* iWorkspaceSnapshot;
};
#endif