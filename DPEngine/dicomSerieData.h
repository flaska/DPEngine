#ifndef _DICOMLOADER_H_
#define _DICOMLOADER_H_
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <dicomHeader.h>
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmjpeg/djdecode.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmimage/diregist.h>
#include <exception>
#define _DICOM_FRAMES_QT_PROGRESS 1//to use progress dialog of loading frames
//forward 
/*
class DicomFramesException: public exception
{
public:
  virtual const char* what() const throw()
  {
    return "File could not be loaded";
  };
};*/

typedef struct 
{
	float center;
	float width;
}TImageWindow;

typedef struct
{
	int width, height, framesCount,frameQuintsCount, bps, colorsCount,mainFrameIndex,
		frameSize, maxColorValue, minColorValue;
	TImageWindow window;
}TDicomImagesInfo;
/**
* @brief class to load dicom files, after loading it should be deleted
*/
class CDicomFrames
{
public:
        CDicomFrames(char *fileName);
	virtual ~CDicomFrames();
	bool LoadFromFile(char *fileName);
	const void* GetImageData();
	int GetWidth();
	int GetFramesCount();
	int GetHeight();
	int GetColorCount();
	int GetBitsPerSampleCount();
	int GetMinColorValue();
	int GetMaxColorValue();
	CDicomHeader &GetHeader(int frame);
	/**
	after calling this function, it is assumed that another object will perform destruction of the 
	iDicomHeader member, ie. CDicom3DTexture
	*/
	//CDicomHeader *TransferHeaderPointer();
	TImageWindow GetWindowDefaults();
	/**
	* do some operations on input data if required
	* e.g perform some transformations of test on data
	*/
	void PerformImageInputDataProcessing();
	/**
	* @brief Frees the memory allocated by the dicom images
	* It should be used immediately after the data are copied to external buffer
	*/
	void FreeData();
private:
	CDicomHeader* iMainHeader;
	bool iHeaderTransferred ;
	bool LoadFrames(char *fileName);
	QList<QString*>* iFramesFileNames;
	bool LoadDicomImage(char *fileName, bool isFirst=false, int framesCount=0 );
	bool LoadHeader(const char *fileName); //load header of first frame
	//CDicomHeader *iDicomHeader;
	QVector<CDicomHeader*> iDicomHeaderVector;
	DicomImage *iDicomImage;
	TDicomImagesInfo iImagesInfo;
public:
	quint16* iData; 
public:
	static const float iWindowMultiplyFactor;
};
#endif
