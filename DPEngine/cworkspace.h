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
	//void setImageFromFile(QString filename);
	void addImage(CImage* im);
	QList<CImage*>& GetImages();
	void paint();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	MWorkspaceLayout &GetLayout();
//private:
	QImage* iWorkspaceImage;
	QList<CImage*> iImages;
	MWorkspaceLayout *iLayout;
	CImage *iActiveImage;
};
#endif