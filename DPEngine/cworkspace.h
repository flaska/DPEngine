#ifndef CWORKSPACE
#define CWORKSPACE
#include <QtGui/QImage>
#include <cimage.h>
#include <cobject.h>
#include <workspacelayout.h>
#include <cworkspacesnapshot.h>
//#include <workspacelayout.h>

class CImage;
class MWorkspaceLayout;
class CWorkspaceSnapshot;
class CWorkspace : public CObject {
public:
	CWorkspace();
	CWorkspace(CObject*, const QPointF&, const QPointF&);
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
	void SetName(const QString &name);
	void SetLayout(TLayoutType type);
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