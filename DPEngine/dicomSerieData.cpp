#include <stdio.h>
#include <QtCore/QDir>

#include <dicomSerieData.h>
#include <settings.h>

#ifdef _DICOM_FRAMES_QT_PROGRESS
//#include <mainWindow.h>
#include <QtGui/QProgressDialog>
#include <QtGui/QMessageBox>
#endif

using namespace std;

const float CDicomFrames::iWindowMultiplyFactor=1.5;
CDicomFrames::CDicomFrames(char *fileName)
{
	iMainHeader = NULL;
	iData = NULL;
	iDicomImage = NULL;
	iImagesInfo.framesCount = 0;
	iImagesInfo.maxColorValue = 0;
	iImagesInfo.minColorValue = 128000;

	iFramesFileNames = new QList<QString*>();
	if(!LoadFromFile(fileName))
	{
////		throw DicomFramesException();
	}

}

CDicomFrames::~CDicomFrames()
{
	if (iFramesFileNames)
	{
		delete iFramesFileNames;
	}
	if (iData)
		delete iData;

	int length = iDicomHeaderVector.count();
	for(int i=0;i<length;i++)
	{
		CDicomHeader *header = iDicomHeaderVector.at(i);
		delete header;
		header = NULL;
	}
	if(iMainHeader)
	{
		delete iMainHeader;
	}
	if(iDicomImage)
		delete iDicomImage;
}
/**
* Load header info wich should be common to all frames in 
*/
bool CDicomFrames::LoadHeader(const char *fileName)
{

	//if(iDicomHeader)delete iDicomHeader;

	iMainHeader = new CDicomHeader ();

	if(iMainHeader->LoadFromFile(fileName))
	{
		/*cout << "SEX:" << header->GetPatientInfo().GetSex() << endl;
		cout << "Weight:" << header->GetPatientInfo().GetWeight() << endl;
		cout << "Name:" << header->GetPatientInfo().GetName() << endl;
		cout << "ID:" << header->GetPatientInfo().GetID() << endl;
		cout << "Series UID:" << header->GetSeriesInfo().GetSeriesInstanceUID() << endl;
		cout << "Series Description:" << header->GetSeriesInfo().GetSeriesDescription() << endl;
		cout << "Series Number:" << header->GetSeriesInfo().GetSeriesNumber() << endl;
		cout << "Slice thickness:" << header->GetImageInfo().GetSliceThickness () << endl;
		*/
		//	cout << "Institution:" << iDicomHeader->GetEquipmentInfo().GetInstitutionName() << endl;
	}
	return true;
}

/**
* @brief loads single image - perform windowing
* VOI LUT transformation not performed
*/
bool CDicomFrames::LoadDicomImage(char *fileName, bool isFirst, int framesCount )
{

	CDicomHeader *header = new CDicomHeader();
	iDicomHeaderVector.append(header);
	if(!header->LoadFromFile(fileName))
	{
		return false;
	}
	const char * seriesUID = header->GetSeriesInfo().GetSeriesInstanceUID();
	if(strcmp(seriesUID, iDicomHeaderVector.at(0)->GetSeriesInfo().GetSeriesInstanceUID())!=0)
	{
		return false;
	}

	if(iDicomImage )delete iDicomImage;
	iDicomImage=NULL;
	//TODO
	//write some header info to frameinfo list
	iDicomImage = new DicomImage (fileName);
	EI_Status imageStatus = iDicomImage->getStatus();
	if (imageStatus==EIS_MissingAttribute){			
		QString strCommand("gdcmconv.exe --raw --force ");
		strCommand.append(fileName);
		strCommand.append(" ");
		strCommand.append("temp.dcm");
		int i = system(strCommand.toAscii().data());
		if(i==0){
			iDicomImage=NULL;
			iDicomImage = new DicomImage ("temp.dcm");
			remove("temp.dcm");
		}else{
			QMessageBox msgBox;
			msgBox.setText("DICOM file is missing some header attribute.\ngdcmconv.exe can repair DICOM file but it was not successful.\nPlease check if gdcmconv.exe is present in application root directory.");
			msgBox.exec();
		}		
	}


	if(iDicomImage->getFrameCount()>1)
	{//TODO load multiple frames
		cout << fileName <<" not supported format-Dicom Image has more than one frame";
		int err=1;
		return false;
	}
	if(!iDicomImage->isMonochrome())
	{//TODO load color frames
		//iDicomImage->PhotometricInterpretation
		cout << fileName <<" not supported format--Dicom Image is not monochrome";
		int err=1;
		return false;
	}
	//monochrome
	iImagesInfo.colorsCount = 1;
	cerr << fileName <<" image loading...\n";
	bool bDecompressed = false;

tryReadDicomImage://Label for goto
	//perform decompression to temp file if neccessary 
	//TODO add more codecs support
	if ( iDicomImage != NULL )
	{
		EI_Status imageStatus = iDicomImage->getStatus();
		if ( imageStatus == EIS_Normal )
		{
			//Ok - image loaded
		}
		else if ( imageStatus == EIS_InvalidValue )
		{
			delete iDicomImage;
			iDicomImage=NULL;
			if ( bDecompressed ) return false;
			//bitmap is propably compressed JPEG
			DJDecoderRegistration::registerCodecs(); // register JPEG codecs
			DcmFileFormat fileformat;
			if ( fileformat.loadFile (fileName).good() )
			{
				DcmDataset *dataset = fileformat.getDataset();
				// decompress data set if compressed
				dataset->chooseRepresentation ( EXS_LittleEndianExplicit, NULL );
				// check if everything went well
				if ( dataset->canWriteXfer ( EXS_LittleEndianExplicit ) )
				{
					fileformat.saveFile ( "temp_decompressed.dcm", EXS_LittleEndianExplicit );
				}

			}
			DJDecoderRegistration::cleanup(); // deregister JPEG codecs
			iDicomImage = new DicomImage ( "temp_decompressed.dcm" );
			bDecompressed = true;
			goto tryReadDicomImage;
		}
		else if ( EIS_MissingAttribute )
		{
			//bitmap is propably old ARC/NEMA format
			cerr << "Error: cannot load DICOM image(ACR/NEMA??) (" << DicomImage::getString ( iDicomImage->getStatus() ) << ")" << endl;

			delete iDicomImage;
			iDicomImage=NULL;
			return false;
		}
		else
		{
			delete iDicomImage;
			iDicomImage=NULL;
			cerr << "Error: cannot load DICOM image (" << DicomImage::getString ( iDicomImage->getStatus() ) << ")" << endl;
			return false;
		}
	}

	//Image is now ready
	cerr << fileName <<" image should be loaded\n";
	//get info about image - check if values are the same as for the first image
	//HEIGHT
	if(isFirst)
	{
		iImagesInfo.height=iDicomImage->getHeight();
	}
	else if(iDicomImage->getHeight() != iImagesInfo.height)
	{
		cerr << fileName <<" image has bad height value\n";
	}
	//WIDTH
	if(isFirst)
	{
		iImagesInfo.width=iDicomImage->getWidth ();
	}
	else if(iDicomImage->getWidth() != iImagesInfo.width)
	{
		cerr << fileName <<" image has bad width value\n";
	}
	//BPS - bits per sample
	if(isFirst)
	{
		iImagesInfo.bps=iDicomImage->getDepth ();
	}
	else if(iDicomImage->getDepth() != iImagesInfo.bps)
	{
		cerr << fileName <<" image has bad bps value\n";
	}
	double min, max;
	iDicomImage->getMinMaxValues(min, max);
	//update values for (multi frames images)
	if(iImagesInfo.minColorValue > min)
	{
		iImagesInfo.minColorValue=min;
	}
	if(iImagesInfo.maxColorValue < max)
	{
		iImagesInfo.maxColorValue=max;
	}
	int VOICount = iDicomImage->getVoiLutCount ();
	if(VOICount>0)
	{
		//transformations on pixel data will be performed when getOutputData is calle
		//see
		//iDicomImage->setNoDisplayFunction ();
		//iDicomImage->setNoVoiTransformation ();
		//TODO add handling to this type of images
		cerr << fileName <<" image has VOI LUT\n";
		OFString strVoiLutExplanation;
		const char *exp = iDicomImage->getVoiLutExplanation(0,strVoiLutExplanation);
		int err;
	}
	int WindowCount = iDicomImage->getWindowCount();
	if(WindowCount>1)
	{
		cerr << fileName <<" image has more WINDOW\n";
		OFString strWindowExplanation;
		const char *exp = iDicomImage->getVoiWindowExplanation (0,strWindowExplanation);
		int err;
	}
	int OverlayPlaneCount = iDicomImage->getOverlayCount(); //additional bitmap data over original image

	if(OverlayPlaneCount>0)
	{
		cerr << fileName <<" image has overlay planes\n";
		OFString strPlaneExplanation;
		const char *exp = iDicomImage->getOverlayDescription (0);
		int err;
	}
	//TODO slice position check
	iImagesInfo.mainFrameIndex = iDicomImage->getRepresentativeFrame ();
	if(iImagesInfo.mainFrameIndex >0)
	{
		cout << "index of main frame is "<<iImagesInfo.mainFrameIndex << endl;
	}
	//prepare buffer for image data output ( 16 bits)
	//TODO solve
	const unsigned long size = iDicomImage->getOutputDataSize(8);;
	//number of unsigned ints to allocate
	iImagesInfo.frameQuintsCount = size / sizeof(quint8);
	if (isFirst)
	{//perform allocation only once
		iImagesInfo.frameSize = size;
		if (iData)
			delete iData;
		//framesCount = 512;
		//TODO handle huge numbger of frames // can not allocate
		iData = new quint8[iImagesInfo.frameQuintsCount * framesCount];
	}
	else
	{//check image size for compatibility
		if (iImagesInfo.frameSize !=size)
		{
			cerr << fileName <<" image has bad frame size value\n";
			int err=1;
			return false;
		}
	}

	//without this - some images would be undisplayable
	if(isFirst)
	{
		iDicomImage->setMinMaxWindow();
		double center, width;
		iDicomImage->getWindow(center,width);
		//set center width with reserve for additional frames
		iImagesInfo.window.center = center*iWindowMultiplyFactor;
		iImagesInfo.window.width = width*iWindowMultiplyFactor ;
	}
	else
	{//not first
		iDicomImage->setMinMaxWindow();
		double center, width;
		iDicomImage->getWindow(center,width);
		//is in range of first frame's window?
		if(center+width/2. > iImagesInfo.window.center+iImagesInfo.window.width/2.)
		{
			//TODO reload image with better window
			int err=1;
		}
		if(center-width/2. < iImagesInfo.window.center-iImagesInfo.window.width/2.)
		{
			//TODO reload image with better window
			int err=1;
		}
	}
	iDicomImage->setWindow(iImagesInfo.window.center,iImagesInfo.window.width);
	quint8 *target = iData+(iImagesInfo.frameQuintsCount*iImagesInfo.framesCount);
	iDicomImage->getOutputData(target,size,8);
	iImagesInfo.framesCount++;

	//delete image object - data are stored separatedly
	delete iDicomImage;
	iDicomImage = NULL;
	return true;
}
const void* CDicomFrames::GetImageData()
{
	return iData;
}

bool CDicomFrames::LoadFrames(char *fileName)
{
	//load frames from directory
	QString strFilePath(fileName);
	if(!strFilePath.contains("ima_") && !strFilePath.contains("dcm"))
	{
		return false;
	}

	int fileNamePosition = strFilePath.lastIndexOf ( '/' );
	QString strFileName ( strFilePath.right ( strFilePath.length() - fileNamePosition-1 ) ); //brain_001.dcm
	QString strDirectoryPath ( strFilePath.left ( fileNamePosition+1 ) ); //current path
	//parse file string if it contain _001
	int separatorPosition = strFilePath.lastIndexOf ( '_' );
	if (( separatorPosition == -1) | (separatorPosition < fileNamePosition) )
	{
		//try another separator string
		separatorPosition = strFilePath.lastIndexOf ( '-' );
	}
	if ( (separatorPosition == -1) | (separatorPosition < fileNamePosition) )
	{
		//not numbered file
		if(!LoadDicomImage(fileName ,true,1))
			return false;
		//TODO multiple frame file
	}
	else
	{
		//numbered files
		QString strFilenamePrefix ( strFilePath.mid ( fileNamePosition+1,separatorPosition-fileNamePosition ) ); //brain_
		QString strFilenameSuffix ( strFilePath.mid ( separatorPosition+1, strFilePath.length() - separatorPosition -1 -4 ) ); // -4 .dcm - 001
		bool bResult;
		//convert string to integer
		int fileIndex = strFilenameSuffix.toInt ( &bResult,10 );
		if ( bResult == true )
		{
			QDir dir(strDirectoryPath );
			QStringList files = dir.entryList();
#ifdef _DICOM_FRAMES_QT_PROGRESS
//////////////	tofix	    QProgressDialog progress("Loading sequence...", "Abort Loading", 1, files.count(), MainWindow::iSelfS);
/////////////	tofix		progress.setWindowModality(Qt::WindowModal);
#endif
			for (int i=1;i<files.count() ;i++)
			{		
				QString *file=new QString(files.at(i));
				file->prepend (strDirectoryPath);
				if (file->contains (strFilenamePrefix))
				{
					iFramesFileNames->append(new QString(*file));
				}
				delete file;
			}
			//load images
			cout << iFramesFileNames->at(0)->toAscii().data();
			LoadDicomImage(iFramesFileNames->at(0)->toAscii().data(),true,iFramesFileNames->count ());
			//TODO handle huge number of frames - how?
			int framesCountToLoad=iFramesFileNames->count();
			if(framesCountToLoad>Settings::GetIntegerConstant(EMaximumFramesToLoad))//tested more throws exception in opengl texture
				framesCountToLoad=Settings::GetIntegerConstant(EMaximumFramesToLoad);
			for (int i=1;i<framesCountToLoad ;i++)
			{
#ifdef _DICOM_FRAMES_QT_PROGRESS
//////tofix				progress.setValue(i);
/////tofix				if (progress.wasCanceled())
					break;
#endif
				if(!LoadDicomImage(iFramesFileNames->at(i)->toAscii().data()))
				{
					cerr << iFramesFileNames->at(i)->toAscii().data() << " skipped"; 
				}
			}
		}
	}
	PerformImageInputDataProcessing();
	return true;
}
void CDicomFrames::PerformImageInputDataProcessing()
{
	return;
	//test input data - comupte maximum and minimum values - and 
	unsigned int sum = 0;
	unsigned int sum2=0;
	int poc=0;
	int maxx=0;
	int minn=+32767;
	int vals[65536];
	for(int i=0;i<65536;i++)
	{
		vals[i]=0;
	}


	//input data processing
	for (int i=0;i<iImagesInfo.height*iImagesInfo.width*iImagesInfo.framesCount;i++)
	{
		if(iImagesInfo.bps==17)
		{//specialized actions for brain
			//iData[i] -= 32767;
			//iData[i] *= 16;
		}
		quint8 a=iData[i];
		if(a!=-32768)
		{
			a=a;
		}

		if (a>maxx)
			maxx=a;
		if(a<minn)
			minn=a;
		a=abs(a);
		if(a<65537)
		{
			vals[a]++;
			a=a-2147483648;
			poc++;
			sum+=iData[i];
			sum2+=iData[i]*iData[i];
		}
	}
	int diff=0;
	for(int i=0;i<65536;i++)
	{
		if(vals[i]!=0)
			diff++;
	}
	//end test
}
bool CDicomFrames::LoadFromFile(char *fileName)
{

	//obtain information about image size, bit depth and other info

	if(!LoadHeader(fileName))
	{
		return false;
	}
	if(!LoadFrames(fileName))
	{
		return false;
	}
	return true;

}

int CDicomFrames::GetFramesCount()
{
	return iImagesInfo.framesCount;
}

int CDicomFrames::GetWidth()
{
	return iImagesInfo.width;
}

int CDicomFrames::GetHeight(){
	return iImagesInfo.height;
}

int CDicomFrames::GetColorCount(){
	return iImagesInfo.colorsCount;
}

int CDicomFrames::GetBitsPerSampleCount()
{
	return iImagesInfo.bps;
}

int CDicomFrames::GetMinColorValue()
{
	return iImagesInfo.minColorValue;
}
TImageWindow CDicomFrames::GetWindowDefaults()
{
	return iImagesInfo.window;
}
int CDicomFrames::GetMaxColorValue()
{
	return iImagesInfo.maxColorValue;
}
void CDicomFrames::FreeData()
{
	if (iData)
		delete iData;
	iData= NULL;
}
CDicomHeader &CDicomFrames::GetHeader(int frame)
{
	if(frame<0 | frame>= iDicomHeaderVector.count())
		abort();
// TODO: fix exception (Oberhuber)
//		throw std::exception("user argument");
	return *iDicomHeaderVector.at(frame);
}
