#ifndef GLPLANARWORKSPACE_H_AWDS
#define GLPLANARWORKSPACE_H_AWDS
#include <cObject.h>
#include <cImage.h>
#include <workspaceLayout.h>
#include <QtCore/QString>
#include <QtCore/QList>

typedef struct
{
	float x;
	float y;
	float z;
}TPlanarCrossPosition;

typedef enum
{
	x,
	y,
	z
}SliceOrientation;

class CWorkspaceSnapshot;

class CPlanarWorkspace:public QWidget, public CObject
{
	//Q_OBJECT
public:
	void SetGeometry(float x, float y, float width, float height);
	void SetName( const QString &name);
	void UpdateTexture();
	QString& GetName();
	CPlanarWorkspace(CObject *parent, const QPointF &position, const QPointF &size);
	~CPlanarWorkspace();
	void initializeGL();
	void paint(QPainter*, QRect);
	void DrawToTexture();
	void DrawFromTexture();
	void SaveSnapshot(QString& fileName);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);	
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void SelectImage(CImage *image);

	QList<CImage*>& GetImages();
	MWorkspaceLayout &GetLayout();
	void SetLayout(TLayoutType type);
	CWorkspaceSnapshot& GetSnapshot();

	int GetSaveSnapshotWidth();
	int GetSaveSnapshotHeight();
	void SetSaveSnapshotWidth(int width);
	void SetSaveSnapshotHeight(int height);
	void UseImage(CImage *image);
private:
	float iLastInnerHeight;
	float iLastInnerWidth;
	CImage *iImage1;
	CImage *iImage2;
	CImage *iImage3;
	/**
	* @Save the texture  to the file
	* is performed when the actual texture is drawn
	*/
	void SaveTexture(QString& fileName);
	bool iSaveSnapshot;
	QString* iSaveSnapshotFileName;
	int iSaveSnapshotHeight;//\current set height, which will be used as height of the image when saving snapshot
	int iSaveSnapshotWidth;//\current set width, which will be used as width of the image when saving snapshot
	bool iWorkspaceChanged ;
	//GLuint iFBO;
	
//    QGLFramebufferObject *iActualTextureFBO;
//	GLuint iActualTexture;
	TSliceInfo iActualTextureInfo;
	QString iIdentification;
	MWorkspaceLayout *iLayout;
	CImage *iImage;

	CWorkspaceSnapshot *iWorkspaceSnapshot;
	QString *iName;

	TPlanarCrossPosition iPlanarCrossPosition;
	void DrawBorders();
	QPoint *iCursorHistory;
	QPoint *iEventHistory;
	SliceOrientation UserManipulatingSlice;
	int iSensitivity;
};
#endif
