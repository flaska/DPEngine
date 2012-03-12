#ifndef _DICOMHEADER_H_
#define _DICOMHEADER_H_
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdeftag.h>
//To find detailed definitions and information about parameters search for dicom tag in DICOM standart 3.3 - part 3 
//e.g. look at definition of DCM_NumberOfSlices and search for corresponding tag (hexa pair)

//forward declarations
class CDicomHeader;

/*Image Position (Patient) (0020,0032) 1 The x, y, and z coordinates of the upper
left hand corner (center of the first voxel
transmitted) of the image, in mm. See (3.3)
C.7.6.2.1.1 for further explanation.*/
struct TImagePosition
{
	double x, y,z;
};



/*Image Orientation (Patient) (0020,0037) 1 The direction cosines of the first row and
the first column with respect to the patient.
See C.7.6.2.1.1 for further explanation.*/
struct TDirectionCosines
{
		double x, y,z;
};

struct TImageOrientation
{
	TDirectionCosines row;
	TDirectionCosines column;
};

struct TPixelSpacing
{
	double x, y;
};

/**
 * @short Class to access header information from Dicom file (Study Description, Image Width,...)
 * Retreive information on the first acces to member
 
 * @author Pavel,,, <pavel@pa>
 * @version 0.1
 */
class CDicomImageModule
{
	
public:
    /**
     * Default Constructor
     */

    CDicomImageModule(CDicomHeader& aDicomHeader);
 	
	TImagePosition GetImagePosition();
	TImageOrientation GetImageOrientation();
	double GetSliceThickness();
	double GetSliceLocation();
	TPixelSpacing GetPixelSpacing();
	int GetNumberOfSlices();
	
    /**
     * Default Destructor
     */
    virtual ~CDicomImageModule();
private:
	CDicomHeader &iDicomHeader;
	bool RetrieveInfo();
	bool iIsModuleRetrieved;
 
double iSliceLocation;
double iSliceThickness;
TImagePosition iImagePositionPatient;//patient
TImageOrientation iImageOrientationPatient;
TPixelSpacing iPixelSpacing;
int iNumberOfSlices;
int iWidth, iHeight, iDepth;
};

/**
 * @short Class to access header information from Dicom file (Study Description, Image Width,...)
 * Retreive information on the first acces to member
 * GENERAL EQUIPMENT MODULE ATTRIBUTES (DICOM PS 3.3 - p. 306)
 * @author Pavel,,, <pavel@pa>
 * @version 0.1
 */
class CDicomGeneralEquipmentModule
{
	
public:
    /**
     * Default Constructor
     */

    CDicomGeneralEquipmentModule(CDicomHeader& aDicomHeader);
 	
	const char* GetManufacturer();
const char* GetInstitutionName();
const char* GetInstitutionAddress();
const char* GetStationName();
const char* GetInstitutionalDepartmentName();
const char* GetManufacturersModelName();
const char* GetDeviceSerialNumber();
const char* GetSoftwareVersions();

const char* GetSpatialResolution();
const char* GetDateOfLastCalibration();
    /**
     * Default Destructor
     */
    virtual ~CDicomGeneralEquipmentModule();
private:
	CDicomHeader &iDicomHeader;
	bool RetrieveInfo();
	bool iIsModuleRetrieved;
 
OFString iManufacturer;
OFString iInstitutionName;
OFString iInstitutionAddress;
OFString iStationName;
OFString iInstitutionalDepartmentName;
OFString iManufacturersModelName;
OFString iDeviceSerialNumber;
OFString iSoftwareVersions;
OFString iSpatialResolution;
OFString iDateOfLastCalibration;
	
};

/**
 * @short Class to access header information from Dicom file (Study Description, Image Width,...)
 * Retreive information on the first acces to member
 * GENERAL SERIES MODULE ATTRIBUTES (DICOM PS 3.3 - p. 297)
 * @author Pavel,,, <pavel@pa>
 * @version 0.1
 */
class CDicomSeriesModule
{
	
public:
	const char *GetModality();
	const char *GetStudyInstanceUID();
	const char *GetSeriesInstanceUID();
	const char *GetSeriesDescription();
	const char *GetSeriesNumber();
	const char *GetSeriesDate();
	const char *GetSeriesTime();
	const char *GetPerformingPhysiciansName();
	const char *GetPerformingPhysicianIdentificationSequence();
	const char *GetOperatorsName();
	const char *GetOperatorIdentificationSequence();

	
public:
    /**
     * Default Constructor
     */

    CDicomSeriesModule(CDicomHeader& aDicomHeader);

    /**
     * Default Destructor
     */
    virtual ~CDicomSeriesModule();
private:
	CDicomHeader &iDicomHeader;
	bool RetrieveInfo();
	bool iIsModuleRetrieved;
 	OFString iModality;
	OFString iStudyInstanceUID;
	OFString iSeriesInstanceUID;
	OFString iSeriesNumber;
	OFString iSeriesDescription;
	OFString iSeriesDate;
	OFString iSeriesTime;
	OFString iPerformingPhysiciansName;
	OFString iPerformingPhysicianIdentificationSequence;
	OFString iOperatorsName;
	OFString iOperatorIdentificationSequence;
	

};

/**
 * @short Class to access header information form Dicom file (Patient's name, Study Description, Image Width,...)
 * Retreive information on the first acces to member
 * @author Pavel,,, <pavel@pa>
 * @version 0.1
 */
class CDicomPatientModule
{
public:
	const char *GetName();
	const char *GetSex();
	const char *GetID();
	const char *GetWeight();
	const char *GetPosition();
		const char *GetOrientation();
public:
    /**
     * Default Constructor
     */

    CDicomPatientModule(CDicomHeader& aDicomHeader);

    /**
     * Default Destructor
     */
    virtual ~CDicomPatientModule();
private:
	CDicomHeader &iDicomHeader;
	bool RetrieveInfo();
	bool iIsModuleRetrieved;
	
 	OFString iWeight;
 	OFString iName;
	OFString iPatientPosition;
	OFString iPatientOrientation;
	OFString iSex;
	OFString iID;

};


/**
 * @short Class to access header information form Dicom file (Patient's name, Study Description, Image Width,...)
 * @author Pavel,,, <pavel@pa>
 * @version 0.1
 */
class CDicomHeader
{
public:
	DcmFileFormat &GetFile();
	CDicomPatientModule &GetPatientInfo();
	
	CDicomImageModule& GetImageInfo();
	CDicomGeneralEquipmentModule &GetEquipmentInfo();
	CDicomSeriesModule &GetSeriesInfo();
    /**
     * Default Constructor
     */

    CDicomHeader();
	bool LoadFromFile(const char* fileName);



    /**
     * Default Destructor
     */
    virtual ~CDicomHeader();
private:

	bool iDcmFileFormatLoaded;
	DcmFileFormat *iDicomFile;
	CDicomPatientModule* iPatientModule;
	CDicomSeriesModule* iSeriesModule;
	CDicomImageModule * iImageModule;
	CDicomGeneralEquipmentModule *iEquipmentModule;
};

#endif // _DicomHEADER_H_

