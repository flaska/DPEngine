#include <workspaceManager.h>
#include <cworkspaceexplorer.h>
#include <cwidget.h>
//#include <glWorkspaceSnapshot.h>
CWorkspaceManager* CWorkspaceManager::instance = NULL;

//CObject* CWorkspaceManager::iParent = NULL;
CWorkspaceManager::CWorkspaceManager(/*CObject *parent*/)
{
	iActiveWorkspace = NULL;
	//iPlanarWorkspace = NULL;
}
/*
CWorkspaceManager::~CWorkspaceManager()
{
	instance = NULL;
}

void CWorkspaceManager::AddImageToActiveWorkspace(CGLImage *image)
{
	iActiveWorkspace->AddImage(image);
}

CGLPlanarWorkspace *CWorkspaceManager::GetPlanarWorkspace()
{
	return iPlanarWorkspace;
}
*/
QList<CWorkspace*>& CWorkspaceManager::GetWorkspaces()
{
	return iWorkspaces;
}/*
void CWorkspaceManager::RemoveWorkspace(CGLWorkspace*workspace)
{
	if (iWorkspaces.contains(workspace))
	{

		iWorkspaces.removeOne(workspace);
		if(iActiveWorkspace==workspace)
		{
			if(iWorkspaces.count()>0)
			{
			iActiveWorkspace=iWorkspaces.at(0);
			}
			else
			{
				iActiveWorkspace=NULL;
			}
		}
		delete workspace;
		workspace=NULL;
	}
	//rearange workspace snapshots
	QListIterator<CGLWorkspace*> workspaces(iWorkspaces);
	workspaces.toFront();
	

	QPoint pos=CGLWorkspaceExplorer::GetInstance()->GetDefaultWorkspaceSnapshotPos();
	QPoint size=CGLWorkspaceExplorer::GetInstance()->GetDefaultWorkspaceSnapshotSize();
	int lastx = pos.x();
	while(workspaces.hasNext())
	{
		
		CGLWorkspace* ws = workspaces.next();
		pos.setX(lastx);
		lastx=pos.x()+size.x();
		ws->GetSnapshot().SetSize(size);
		ws->GetSnapshot().SetPosition(pos);
	}
	
}
*/
void CWorkspaceManager::AddWorkspace(CWorkspace *workspace){
	if(!CWorkspaceExplorer::GetInstance())
	return;
	QString jk;
	QListIterator<CWorkspace*> workspaces(iWorkspaces);
	workspaces.toBack();
	CWorkspace *lastWorkspace = NULL;
	if(workspaces.hasPrevious())
	{
		lastWorkspace= workspaces.previous();
	}

	QPointF pos=CWorkspaceExplorer::GetInstance()->GetDefaultWorkspaceSnapshotPos();
	QPointF size=CWorkspaceExplorer::GetInstance()->GetDefaultWorkspaceSnapshotSize();
	if(lastWorkspace)
	{
		pos=lastWorkspace->GetSnapshot().GetPosition();
		pos.setX(pos.x()+lastWorkspace->GetSnapshot().GetSize().x());
		size=lastWorkspace->GetSnapshot().GetSize();
	}
	iWorkspaces.append(workspace);
	workspace->GetSnapshot().SetSize(size);  //fail
	workspace->GetSnapshot().SetPosition(pos); //fail

	if(iActiveWorkspace==NULL)
	{
		iActiveWorkspace = workspace;
	}
}
/*
void CWorkspaceManager::CreatePlanarWorkspace(CGLPlanarWorkspace *workspace){
	if(!CGLWorkspaceExplorer::GetInstance())
	return;
	iPlanarWorkspace = workspace;
}


bool CWorkspaceManager::PlanarWorkspaceExists(){
	if(iPlanarWorkspace==NULL)
		return false;
	if(iPlanarWorkspace!=NULL)
		return true;
}

*/
CWorkspaceManager* CWorkspaceManager::GetInstance()
{
	return instance;
}

CWorkspaceManager* CWorkspaceManager::InitInstance()
{
	if(!instance)
	{
/*		if(parent)
		{
			iParent = parent;
		}
		else
		{
			return NULL;
		}*/
		instance = new CWorkspaceManager(/*parent*/);
	}
	return instance;
}

void CWorkspaceManager::SetActiveWorkspace(CWorkspace *workspace)
{
	iActiveWorkspace = workspace;
}

CWorkspace *CWorkspaceManager::GetActiveWorkspace()
{
	return iActiveWorkspace;
}