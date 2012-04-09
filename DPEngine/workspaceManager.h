#ifndef CWORKSPACEMANGER_H_asdasd456
#define CWORKSPACEMANGER_H_asdasd456
#include <cimage.h>
#include <cworkspace.h>
//#include <glObjects/workspaces/glPlanarWorkspace.h>



/**
* manages all open dicom studies to provide that each study is loaded only once
*/
class CWorkspaceManager
{
public:
	//~CWorkspaceManager();
private:
	//CWorkspaceManager(CGLObject *parent);
	CWorkspaceManager();
	
public:
	//static CWorkspaceManager* InitInstance(CGLObject *parent = NULL);
	//static CWorkspaceManager* GetInstance(CGLObject *parent = NULL);
	static CWorkspaceManager* InitInstance();
	static CWorkspaceManager* GetInstance();
private:
	static CWorkspaceManager *instance;	
public:
	//void AddImageToActiveWorkspace(CGLImage *image);
	CWorkspace *GetActiveWorkspace();
	//CGLPlanarWorkspace *GetPlanarWorkspace();
	void SetActiveWorkspace(CWorkspace *workspace);
	//void AddWorkspace(CGLWorkspace *workspace);
	//void CreatePlanarWorkspace(CGLPlanarWorkspace *workspace);
	void RemoveWorkspace(CWorkspace*workspace);
	QList<CWorkspace*> &GetWorkspaces();
	//bool PlanarWorkspaceExists();
	void AddWorkspace(CWorkspace *workspace);
private:
	CWorkspace *iActiveWorkspace;
	QList<CWorkspace*> iWorkspaces;
	//static CGLObject *iParent;
	//CGLPlanarWorkspace *iPlanarWorkspace;
};
#endif
