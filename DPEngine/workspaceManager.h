#ifndef CWORKSPACEMANGER_H_asdasd456
#define CWORKSPACEMANGER_H_asdasd456
#include <cimage.h>
#include <cworkspace.h>
#include <cPlanarWorkspace.h>



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
	static CWorkspaceManager* InitInstance(CObject *parent = NULL);
	static CWorkspaceManager* GetInstance();
private:
	static CWorkspaceManager *instance;	
public:
	//void AddImageToActiveWorkspace(CGLImage *image);
	CWorkspace *GetActiveWorkspace();
	CPlanarWorkspace *GetPlanarWorkspace();
	void SetActiveWorkspace(CWorkspace *workspace);
	//void AddWorkspace(CGLWorkspace *workspace);
	void CreatePlanarWorkspace(CPlanarWorkspace *workspace);
	void RemoveWorkspace(CWorkspace*workspace);
	QList<CWorkspace*> &GetWorkspaces();
	bool PlanarWorkspaceExists();
	void AddWorkspace(CWorkspace *workspace);
private:
	CWorkspace *iActiveWorkspace;
	QList<CWorkspace*> iWorkspaces;
	static CObject *iParent;
	//static CGLObject *iParent;
	CPlanarWorkspace *iPlanarWorkspace;
};
#endif
