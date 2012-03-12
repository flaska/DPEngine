#ifndef C3DTextureManager_H_asdasd456
#define C3DTextureManager_H_asdasd456
//#include <GL/glew.h>
#include <QtOpenGL/QtOpenGL>
#include "dicom3DTexture.h"
//#include <Cg/cg.h>
//#include <Cg/cgGL.h>

/**
* manages all open dicom studies to provide that each study is loaded only once
*/
class C3DTextureManager
{
	private:
	C3DTextureManager();
	~C3DTextureManager();
	
public:
	static C3DTextureManager* InitInstance();
	static C3DTextureManager* GetInstance();
private:
	static C3DTextureManager *instance;	
public:
	void ReleaseTexture(CDicom3DTexture *texture);
	CDicom3DTexture *LoadTexture(QString &fileName);
	CDicom3DTexture *GetTexture(QString &identificationString);
private:

	QMap<QString,int> iHandleCounts;
	QMap<QString,CDicom3DTexture*> iTextures;
};
#endif

