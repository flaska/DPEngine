#ifndef _GLDICOM3DTEXTURE_d47as6
#define _GLDICOM3DTEXTURE_d47as6
//forward declaration
//#include <GL/glew.h>
//#include <QtOpenGL/QtOpenGL>
#include <QtCore/QString>
#include <QtCore/QPoint>
//#include <Cg/cg.h>
//#include <Cg/cgGL.h>

#include <dicomSerieData.h>
//class CDicomFrames;
class CGLImage;
/*
typedef enum
{
	EOrientationAxial = 0,
	EOrientationSagital = 0
}TOrientation;*/

class CDicom3DTexture
{
public:
	~CDicom3DTexture();
	CDicom3DTexture(QString &fileName);
	//GLuint GetTextureID();
	TImageWindow GetWindowDefaults();
	int GetDepth();
	int GetWidth();
	int GetHeight();
	CDicomHeader& GetDicomHeader(int frame);
	void SetIdentificationString(QString &str);
	QString &GetIdentificationString();
	QString &GetFileName();
	

//TODO private:
	//CDicomHeader* iDicomHeader;
//TODO private:
	CDicomFrames *iFrames;
	QString* iFileName;
	int iMaxColorValue;
	int iMinColorValue;
	int iWidth;
	int iHeight;
	int iDepth;
	int iColorsCount;
	int iBitsPerPixel;
	DicomImage* iDicomImage;
//	GLuint iTextureID;
	TImageWindow iWindowDefaults;
	QString iIdentificationString;
};
#endif
