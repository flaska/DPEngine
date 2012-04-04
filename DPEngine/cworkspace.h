#ifndef CWORKSPACE
#define CWORKSPACE
#include <QtGui/QImage>
#include <cimage.h>
#include <cobject.h>
#include <workspacelayout.h>

class CImage;
class MWorkspaceLayout;
class CWorkspace : public CObject {
public:
	CWorkspace();
	CWorkspace(CObject *parent, const QPointF &position, const QPointF &size);
	//void setImageFromFile(QString filename);
	void addImage(CImage* im);
	QList<CImage*>& GetImages();
	void paint();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	MWorkspaceLayout &GetLayout();
	void SelectImage(CImage *image);
	void RemoveImage(CImage *image);
//private:
	MWorkspaceLayout *iLayout;
	QImage* iWorkspaceImage;
	QList<CImage*> iImages;
	CImage *iActiveImage;
};
#endif