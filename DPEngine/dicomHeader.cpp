#include <dicomHeader.h>




/*
*	Image's information
*/
CDicomImageModule::CDicomImageModule(CDicomHeader &aDicomHeader):iDicomHeader (aDicomHeader)
{
	iIsModuleRetrieved = false;
	iDepth = 0;
}

CDicomImageModule::~CDicomImageModule()
{
}

bool CDicomImageModule::RetrieveInfo()
{
	DcmDataset* dataset= iDicomHeader.GetFile().getDataset();
	// patient orientation
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.row.x,0);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.row.y,1);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.row.z,2);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.column.x,3);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.column.y,4);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImageOrientationPatient,iImageOrientationPatient.column.z,5);
	//patient position
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImagePositionPatient,iImagePositionPatient.x,0);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImagePositionPatient,iImagePositionPatient.y,1);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_ImagePositionPatient,iImagePositionPatient.z,2);
	//slice thickness- zSpacing
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_SliceThickness,iSliceThickness);

	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_SliceLocation  , iSliceLocation); 

	// number of slices
	Uint16 slicesCount;
	iDicomHeader.GetFile().getDataset()->findAndGetUint16 (DCM_NumberOfSlices, slicesCount);
	iNumberOfSlices = slicesCount;
	//pixel spacing
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_PixelSpacing,iPixelSpacing.x,0);
	iDicomHeader.GetFile().getDataset()->findAndGetFloat64(DCM_PixelSpacing,iPixelSpacing.y,1);


	iIsModuleRetrieved = true;
	return true;
}

TImagePosition CDicomImageModule::GetImagePosition()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iImagePositionPatient;
}
double CDicomImageModule::GetSliceLocation()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSliceLocation;

}


int CDicomImageModule::GetNumberOfSlices()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iNumberOfSlices;
}
TPixelSpacing CDicomImageModule::GetPixelSpacing()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iPixelSpacing;
}


double CDicomImageModule::GetSliceThickness()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSliceThickness;

}
TImageOrientation CDicomImageModule::GetImageOrientation()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();

	return iImageOrientationPatient;

}

/*
*	Equipment's information
*/
CDicomGeneralEquipmentModule::CDicomGeneralEquipmentModule(CDicomHeader &aDicomHeader):iDicomHeader (aDicomHeader)
{
	iIsModuleRetrieved = false;
}

CDicomGeneralEquipmentModule::~CDicomGeneralEquipmentModule()
{
}

bool CDicomGeneralEquipmentModule::RetrieveInfo()
{
	iManufacturer = "";
	iInstitutionName = "";
	iInstitutionAddress = "";
	iStationName = "";
	iInstitutionalDepartmentName = "";
	iManufacturersModelName = "";
	iDeviceSerialNumber = "";
	iSoftwareVersions = "";

	iSpatialResolution = "";
	iDateOfLastCalibration = "";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_InstitutionName , iInstitutionName); 
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_Manufacturer , iManufacturer);

	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_InstitutionAddress , iInstitutionAddress);
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_StationName , iStationName);
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_InstitutionalDepartmentName , iInstitutionalDepartmentName);
//flaska	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_ManufacturersModelName , iManufacturersModelName);
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_DeviceSerialNumber , iDeviceSerialNumber);
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_SoftwareVersions , iSoftwareVersions);


	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_SpatialResolution , iSpatialResolution);
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_DateOfLastCalibration , iDateOfLastCalibration);


	iIsModuleRetrieved = true;
	return true;
}

const char* CDicomGeneralEquipmentModule::GetManufacturer()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iManufacturer.c_str();
}
const char* CDicomGeneralEquipmentModule::GetInstitutionName(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iInstitutionName.c_str();
}
const char* CDicomGeneralEquipmentModule::GetInstitutionAddress(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iInstitutionAddress.c_str();
}
const char* CDicomGeneralEquipmentModule::GetStationName(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iStationName.c_str();
}
const char* CDicomGeneralEquipmentModule::GetInstitutionalDepartmentName(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iInstitutionalDepartmentName.c_str();
}
const char* CDicomGeneralEquipmentModule::GetManufacturersModelName(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iManufacturersModelName.c_str();
}
const char* CDicomGeneralEquipmentModule::GetDeviceSerialNumber(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iDeviceSerialNumber.c_str();
}
const char* CDicomGeneralEquipmentModule::GetSoftwareVersions(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSoftwareVersions.c_str();
}
const char* CDicomGeneralEquipmentModule::GetSpatialResolution(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSpatialResolution.c_str();
}
const char* CDicomGeneralEquipmentModule::GetDateOfLastCalibration(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iDateOfLastCalibration.c_str();
}
/*
const char *CDicomGeneralEquipmentModule::GetModality(){
if (!iIsModuleRetrieved)
RetrieveInfo();
return iModality.c_str();
};*/

/*
*	Series's information
*/
CDicomSeriesModule::CDicomSeriesModule(CDicomHeader &aDicomHeader):iDicomHeader (aDicomHeader)
{
	iIsModuleRetrieved = false;
}

CDicomSeriesModule::~CDicomSeriesModule()
{
}

bool CDicomSeriesModule::RetrieveInfo()
{
	iModality="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_Modality, iModality);
	iStudyInstanceUID="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_StudyInstanceUID, iStudyInstanceUID );
	iSeriesInstanceUID="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_SeriesInstanceUID, iSeriesInstanceUID );
	iSeriesNumber="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_SeriesNumber,iSeriesNumber );
	iSeriesDescription="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_SeriesDescription, iSeriesDescription );
	iSeriesDate="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_SeriesDate, iSeriesDate );
	iSeriesTime="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_SeriesTime, iSeriesTime );
	iPerformingPhysiciansName="";
//flaska	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_PerformingPhysiciansName , iPerformingPhysiciansName );
	iPerformingPhysicianIdentificationSequence="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_PerformingPhysicianIdentificationSequence  , iPerformingPhysicianIdentificationSequence );
	iOperatorsName="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_OperatorsName   , iOperatorsName );
	iOperatorIdentificationSequence="";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString (DCM_OperatorIdentificationSequence   , iOperatorIdentificationSequence );
	iIsModuleRetrieved = true;
	return true;
}

const char *CDicomSeriesModule::GetModality(){
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iModality.c_str();
};
const char *CDicomSeriesModule::GetStudyInstanceUID()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iStudyInstanceUID.c_str();
};
const char *CDicomSeriesModule::GetSeriesInstanceUID()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSeriesInstanceUID.c_str();
};
const char *CDicomSeriesModule::GetSeriesDescription()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSeriesDescription.c_str();
};
const char *CDicomSeriesModule::GetSeriesNumber()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSeriesNumber.c_str();
};
const char *CDicomSeriesModule::GetSeriesDate()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSeriesDate.c_str();
};
const char *CDicomSeriesModule::GetSeriesTime()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSeriesTime.c_str();
};
const char *CDicomSeriesModule::GetPerformingPhysiciansName()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iPerformingPhysiciansName.c_str();
};
const char *CDicomSeriesModule::GetPerformingPhysicianIdentificationSequence()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iPerformingPhysicianIdentificationSequence.c_str();
};
const char *CDicomSeriesModule::GetOperatorsName()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iOperatorsName.c_str();
};
const char *CDicomSeriesModule::GetOperatorIdentificationSequence()	{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iOperatorIdentificationSequence.c_str();
};

/*
*	Patient's information
*/
CDicomPatientModule::CDicomPatientModule(CDicomHeader &aDicomHeader):iDicomHeader (aDicomHeader)
{
	iIsModuleRetrieved = false;
}

CDicomPatientModule::~CDicomPatientModule()
{
}

bool CDicomPatientModule::RetrieveInfo()
{
	iSex = "";
//flaska	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_PatientsSex, iSex);
	iWeight = "";
//flaska	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_PatientsWeight, iWeight);  
	iName = "";
//flaska	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_PatientsName, iName);
	iID = "";
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_PatientID, iID);
	iPatientPosition = "";
	/*The Defined Terms are:
HFP = Head First-Prone HFS = Head First-Supine
HFDR = Head First-Decubitus Right HFDL = Head First-Decubitus Left
FFDR = Feet First-Decubitus Right FFDL = Feet First-Decubitus Left
*/
//see an 3.17 for info about orientation
	iDicomHeader.GetFile().getDataset()->findAndGetOFString(DCM_PatientPosition, iPatientPosition);

	iIsModuleRetrieved = true;
	return true;
}

const char *CDicomPatientModule::GetPosition()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iPatientPosition.c_str();
}
const char *CDicomPatientModule::GetOrientation()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iPatientOrientation.c_str();
}
const char *CDicomPatientModule::GetWeight()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iWeight.c_str();
}

const char *CDicomPatientModule::GetName()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iName.c_str();
}
const char *CDicomPatientModule::GetID()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iID.c_str();
}
const char *CDicomPatientModule::GetSex()
{
	if (!iIsModuleRetrieved)
		RetrieveInfo();
	return iSex.c_str();
}

/*
* CDicomHeader
*/
CDicomHeader::CDicomHeader()
{
	iDicomFile = new DcmFileFormat();
	iDcmFileFormatLoaded=false;
	iPatientModule = new CDicomPatientModule(*this);
	iSeriesModule = new CDicomSeriesModule(*this);
	iEquipmentModule = new CDicomGeneralEquipmentModule(*this);
	iImageModule = new CDicomImageModule(*this);
	return;
}

bool CDicomHeader::LoadFromFile(const char *fileName)
{

	OFCondition status = iDicomFile->loadFile(fileName);
	if ( status.good() )
	{
		iDcmFileFormatLoaded=true;
		return true;
	}
	iDcmFileFormatLoaded=false;
	

	return false;
}
CDicomHeader::~CDicomHeader()
{
	delete iDicomFile;
	delete iPatientModule;
	delete iImageModule;
	delete iSeriesModule;
	delete iEquipmentModule;
}

DcmFileFormat& CDicomHeader::GetFile()
{
	return *iDicomFile;
}

CDicomPatientModule& CDicomHeader::GetPatientInfo()
{
	return  *iPatientModule;
}
CDicomGeneralEquipmentModule& CDicomHeader::GetEquipmentInfo()
{
	return  *iEquipmentModule;
}

CDicomImageModule& CDicomHeader::GetImageInfo()
{
	return  *iImageModule;
}

CDicomSeriesModule& CDicomHeader::GetSeriesInfo()
{
	return  *iSeriesModule;
}


