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
//private:
	QImage* iWorkspaceImage;
	QList<CImage*> iImages;
	MWorkspaceLayout *iLayout;
};
#endif