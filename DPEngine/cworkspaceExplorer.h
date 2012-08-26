#ifndef GLWORKSPACEEXPLORER_H_AWDS
#define GLWORKSPACEEXPLORER_H_AWDS
#include <Qt/qobject.h>
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtGui/QScrollBar>
#include <dicomSerieData.h>
#include <dicom3DTexture.h>
#include <cobject.h>

class CWidget;
class CWorkspace;
class CWidget;
class CPlanarWorkspace;

class CWorkspaceExplorer:public QObject, public CObject
{
//	Q_OBJECT
private:
	CWorkspaceExplorer(CWidget *parentWindow, QPointF &position, QPointF &size);
public:
	void AddNewWorkspace();
	void CreateNewPlanarWorkspace();
	virtual ~CWorkspaceExplorer();
	static CWorkspaceExplorer* GetInstance();
	static CWorkspaceExplorer* InitInstance(CWidget *parent, QPointF& position, QPointF &size );
	void SelectWorkspace(CWorkspace *workspace);
	void SelectPlanarWorkspace();
	QPoint GetDefaultWorkspaceSnapshotPos();
		QPoint GetDefaultWorkspaceSnapshotSize();
	void initializeGL();
	void DrawSelection();
	void DrawIcons();
	void DrawTexts();
	void paint(QPainter*);
	void SetGeometry(int x, int y, int width, int height);
	void mouseMoveEvent(QMouseEvent *event);
	bool IsOnMoveIcon(int x, int y);;
	bool IsOnResizeIcon(int x, int y);;
	void wheelEvent(QWheelEvent *event);	
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	CPlanarWorkspace* iPlanarWorkspace;
public slots:
	void Scrolled(int value);
private:
	static CWorkspaceExplorer* instance;
	QScrollBar *iScrollBar;
	QPoint iPreviousMousePosition;
	QPoint iLockedGlobalMousePosition;
	TMouseState iMouseState;
	TGLIcon iMoveIcon;
	TGLIcon iResizeIcon;


};
#endif
