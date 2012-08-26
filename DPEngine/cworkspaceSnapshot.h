#ifndef CWORKSPACESNAPSHOT_H_sdaczx
#define CWORKSPACESNAPSHOT_H_sdaczx
#include <cimage.h>
#include <cworkspace.h>

class CWorkspace;
class CObject;
class CWorkspaceSnapshot:public QWidget, public CObject
{
public:
	CWorkspaceSnapshot(CObject *parentWindow,CWorkspace* workspace, const QPointF &pos, const QPointF &size );
	~CWorkspaceSnapshot();
	void SetWorkspace(CWorkspace *workspace);
	CWorkspace& GetWorkspace();
	void initialize();
	void paint(QPainter*);
	void paintMPR(QPainter*);
	void mouseMoveEvent(QMouseEvent *event);
	void CloseMe();
	void wheelEvent(QWheelEvent *event);	
	void mousePressEvent(QMouseEvent *event);
	void mousePressEventMPR(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *event);
private:
	CWorkspace *iWorkspace;
};
#endif
