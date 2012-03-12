//#include <GL/glew.h>
#include <dicom3DTextureManager.h>
#include <QtCore/QString>
#include <QtCore/QList>
//TODO remove
#include <cobject.h>

C3DTextureManager* C3DTextureManager::instance = NULL;
C3DTextureManager::C3DTextureManager()
{
}
C3DTextureManager::~C3DTextureManager()
{
	instance = NULL;
}
void C3DTextureManager::ReleaseTexture(CDicom3DTexture *texture)
{
	iHandleCounts[texture->GetIdentificationString()]--;
	if(iHandleCounts[texture->GetIdentificationString()]==0)
	{
		iHandleCounts.remove(texture->GetIdentificationString());
		iTextures.remove(texture->GetIdentificationString());
		delete texture;
		texture = NULL;

	}
	
}

/*
get singleton instance
*/
C3DTextureManager* C3DTextureManager::InitInstance()
{
	if(!instance)
	{
		instance  = new C3DTextureManager ();
	}
	return instance;
}

C3DTextureManager* C3DTextureManager::GetInstance()
{
	if(!instance)
	instance  = new C3DTextureManager ();
	return instance;
}

CDicom3DTexture *C3DTextureManager::GetTexture(QString &identificationString)
{
	if(!iTextures.contains(identificationString))
	{
return NULL;
	}
	else
	{//texture available
	}
	iHandleCounts[identificationString]++;
	return iTextures[identificationString];
}
/*
return NULL on error
*/
CDicom3DTexture *C3DTextureManager::LoadTexture(QString &fileName)
{
	CDicomHeader header;
	if(!header.LoadFromFile(fileName.toAscii().data()))
	{
		return NULL;
	}
	QString seriesUIDstr(header.GetSeriesInfo().GetSeriesInstanceUID ());

	if(!iTextures.contains(seriesUIDstr))
	{
		
		CDicom3DTexture *texture= new CDicom3DTexture (fileName);
		
		texture->SetIdentificationString (seriesUIDstr);
		iHandleCounts[seriesUIDstr]++;
		iTextures[seriesUIDstr]= texture;	
	}
	else
	{//texture already created
	}
	iHandleCounts[seriesUIDstr]++;
	return iTextures[seriesUIDstr];
	//return NULL;
}
