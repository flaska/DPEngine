#include <cWorkspaceSnapshot.h>
#include <cWidget.h>
#include <workspaceManager.h>
#include <cworkspaceexplorer.h>
#include <settings.h>

//workspace snapshot
CWorkspaceSnapshot::CWorkspaceSnapshot(CObject *parentWindow,CWorkspace *workspace, const QPointF &pos, const QPointF &size):CObject(parentWindow,pos,size)
{
	iWorkspace=workspace;
	SetBorderColor(Settings::GetColorConstant(EWorkspaceSnapshotBorderColor));
	SetInnerColor(Settings::GetColorConstant(EWorkspaceSnapshotInnerColor));
	SetBorders(Settings::GetBordersConstant(EWorkspaceSnapshotBorders));
	SetMoveability(false);
	SetResizeability(false);
	SetClosability(true);
}
CWorkspaceSnapshot::~CWorkspaceSnapshot()
{
}
void CWorkspaceSnapshot::SetWorkspace(CWorkspace *workspace)
{
	iWorkspace=workspace;
}
CWorkspace& CWorkspaceSnapshot::GetWorkspace()
{
	return *iWorkspace;
}
void CWorkspaceSnapshot::initialize()
{
}

void CWorkspaceSnapshot::paint(QPainter* painter)
{ 
	DrawBorderRect(painter);
	DrawInnerRect(painter);
	int ypos= CWidget::GetInstance()->GetSize().y()-iSize.y()-iPosition.y()+GetBorders().bottom;
	QRect snapshotPosition(iPosition.x()+GetBorders().left, /*-ypos*/ iPosition.y(), iSize.x()-GetBorders().left-GetBorders().right, iSize.y()-GetBorders().top-GetBorders().bottom);
	iWorkspace->paint(painter,snapshotPosition);
	DrawIcons(painter); //*/
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace()==iWorkspace) DrawSelection(painter);

}
void CWorkspaceSnapshot::mouseMoveEvent(QMouseEvent *event)
{
}
void CWorkspaceSnapshot::wheelEvent(QWheelEvent *event)
{
}
void  CWorkspaceSnapshot::CloseMe()
{
	if(iWorkspace)
	{
	CWorkspaceManager::GetInstance()->RemoveWorkspace(iWorkspace);
	}
}
void CWorkspaceSnapshot::mousePressEvent(QMouseEvent *event)
{
	int x=event->x() - iPosition.x();
	int y = event->y()- iPosition.y();
	if(IsOnCloseIcon(x, y))
	{
		CloseMe();
		return;

	}
	CWorkspaceExplorer::GetInstance()->SelectWorkspace(&this->GetWorkspace());
//	SelectWorkspace(obj);
}
void CWorkspaceSnapshot::mouseReleaseEvent(QMouseEvent *e)
{
}
void CWorkspaceSnapshot::mouseDoubleClickEvent(QMouseEvent *event)
{
}
