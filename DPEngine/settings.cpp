#include "settings.h" 
#include <QtCore/QSettings>
#include <QtCore/QRect>
#include <QtCore/QRectF>
int Settings::imageWindowingCenterSensitivity = 1;
int Settings::imageWindowingWidthSensitivity = 1;
int Settings::iconSize = 25;
bool Settings::iDeleted = false;
bool Settings::iSettingsRead = false;
int Settings::KWorkspaceTextureWidth = 768; //must be 2^n ?
int Settings::KWorkspaceTextureHeight = 768;
int Settings::KInfoPanelSpacing =2 ;
int Settings::KInfoPanelMarginLeft=4;
int Settings::KInfoPanelMarginTop=2;
int Settings::KInfoPanelMarginRight=2;
int Settings::KInfoPanelMarginBottom=2;
int Settings::KMaximumFramesToLoad=1000;
int Settings::imageExplorerSize = 200;
TBorders Settings::KImageBorders={3,3,3,3};
TColor Settings::KImageBorderColor={0.2,0.2,0.2,1};
TColor Settings::KImageInnerColor={0.2,0.2,0.2,1};

TBorders Settings::KImageExplorerBorders={3,3,3,3};
TColor Settings::KImageExplorerBorderColor={0.2,0.2,0.2,1};
TColor Settings::KImageExplorerInnerColor={0.2,0.2,0.2,1};

TBorders Settings::KWorkspaceExplorerBorders={3,3,3,3};
TColor Settings::KWorkspaceExplorerBorderColor={0.2,0.2,0.2,1};
TColor Settings::KWorkspaceExplorerInnerColor={0.2,0.2,0.2,1};

TBorders Settings::KWorkspaceSnapshotBorders={3,3,3,3};
TColor Settings::KWorkspaceSnapshotBorderColor={0.2,0.2,0.2,1};
TColor Settings::KWorkspaceSnapshotInnerColor={0.2,0.2,0.2,1};

TBorders Settings::KWorkspaceBorders={3,3,3,3};
TColor Settings::KWorkspaceBorderColor={0.2,0.2,0.2,1};
TColor Settings::KWorkspaceInnerColor={0.2,0.2,0.2,1};

TColor Settings::KImageExplorerTextColor={0.2,0.9,0.9,1.};
TColor Settings::KWorkspaceExplorerTextColor={0.2,0.9,0.9,1.};
Settings *Settings::instance;

QString Settings::MoveIconFileName = QString("moveicon.bmp");
QString Settings::CloseIconFileName = QString("closeicon.bmp");
QString Settings::ResizeIconFileName = QString("resizeicon.bmp");


Settings::Settings()
{
}

Settings::~Settings()
{
	iDeleted=true;

}
void Settings::WriteSettings()
{
	QSettings settings("DicomPresenter.ini",
		QSettings::IniFormat);
	//QSettings settings("Pavel Neskudla", "DicomPresenter");
	settings.beginGroup("MainWindow");
	settings.setValue("WorkspaceTextureWidth",KWorkspaceTextureWidth);
	settings.setValue("WorkspaceTextureHeight",KWorkspaceTextureHeight);
	settings.setValue("InfoPanelSpacing",KInfoPanelSpacing);
	settings.setValue("InfoPanelMarginLeft",KInfoPanelMarginLeft);
	settings.setValue("InfoPanelMarginTop",KInfoPanelMarginTop);
	settings.setValue("InfoPanelMarginRight",KInfoPanelMarginRight);
	settings.setValue("InfoPanelMarginBottom",KInfoPanelMarginBottom);
	settings.setValue("MaximumFramesToLoad",KMaximumFramesToLoad);

	QRect imageBorders(KImageBorders.left,KImageBorders.top,KImageBorders.right,KImageBorders.bottom);
	settings.setValue("ImageBorders",imageBorders);
	QRect imageBorderColor(KImageBorderColor.r*255,KImageBorderColor.g*255,KImageBorderColor.b*255,KImageBorderColor.a*255);
	settings.setValue("ImageBorderColor",imageBorderColor);
	QRect imageInnerColor(KImageInnerColor.r*255,KImageInnerColor.g*255,KImageInnerColor.b*255,KImageInnerColor.a*255);
	settings.setValue("ImageInnerColor",imageInnerColor);

	QRect imageExplorerBorders(KImageExplorerBorders.left,KImageExplorerBorders.top,KImageExplorerBorders.right,KImageExplorerBorders.bottom);
	settings.setValue("ImageExplorerBorders",imageExplorerBorders);
	QRect imageExplorerBorderColor(KImageExplorerBorderColor.r*255,KImageExplorerBorderColor.g*255,KImageExplorerBorderColor.b*255,KImageExplorerBorderColor.a*255);
	settings.setValue("ImageExplorerBorderColor",imageExplorerBorderColor);
	QRect imageExplorerInnerColor(KImageExplorerInnerColor.r*255,KImageExplorerInnerColor.g*255,KImageExplorerInnerColor.b*255,KImageExplorerInnerColor.a*255);
	settings.setValue("ImageExplorerInnerColor",imageExplorerInnerColor);
	QRect imageExplorerTextColor(KImageExplorerTextColor.r*255,KImageExplorerTextColor.g*255,KImageExplorerTextColor.b*255,KImageExplorerTextColor.a*255);
	settings.setValue("ImageExplorerTextColor",imageExplorerTextColor);

	QRect workspaceExplorerBorders(KWorkspaceExplorerBorders.left,KWorkspaceExplorerBorders.top,KWorkspaceExplorerBorders.right,KWorkspaceExplorerBorders.bottom);
	settings.setValue("WorkspaceExplorerBorders",workspaceExplorerBorders);
	QRect workspaceExplorerBorderColor(KWorkspaceExplorerBorderColor.r*255,KWorkspaceExplorerBorderColor.g*255,KWorkspaceExplorerBorderColor.b*255,KWorkspaceExplorerBorderColor.a*255);
	settings.setValue("WorkspaceExplorerBorderColor",workspaceExplorerBorderColor);
	QRect workspaceExplorerInnerColor(KWorkspaceExplorerInnerColor.r*255,KWorkspaceExplorerInnerColor.g*255,KWorkspaceExplorerInnerColor.b*255,KWorkspaceExplorerInnerColor.a*255);
	settings.setValue("WorkspaceExplorerInnerColor",workspaceExplorerInnerColor);
	QRect workspaceExplorerTextColor(KWorkspaceExplorerTextColor.r*255,KWorkspaceExplorerTextColor.g*255,KWorkspaceExplorerTextColor.b*255,KWorkspaceExplorerTextColor.a*255);
	settings.setValue("WorkspaceExplorerTextColor",workspaceExplorerTextColor);

	QRect workspaceSnapshotBorders(KWorkspaceSnapshotBorders.left,KWorkspaceSnapshotBorders.top,KWorkspaceSnapshotBorders.right,KWorkspaceSnapshotBorders.bottom);
	settings.setValue("WorkspaceSnapshotBorders",workspaceSnapshotBorders);
	QRect workspaceSnapshotBorderColor(KWorkspaceSnapshotBorderColor.r*255,KWorkspaceSnapshotBorderColor.g*255,KWorkspaceSnapshotBorderColor.b*255,KWorkspaceSnapshotBorderColor.a*255);
	settings.setValue("WorkspaceSnapshotBorderColor",workspaceSnapshotBorderColor);
	QRect workspaceSnapshotInnerColor(KWorkspaceSnapshotInnerColor.r*255,KWorkspaceSnapshotInnerColor.g*255,KWorkspaceSnapshotInnerColor.b*255,KWorkspaceSnapshotInnerColor.a*255);
	settings.setValue("WorkspaceSnapshotInnerColor",workspaceSnapshotInnerColor);

	QRect workspaceBorders(KWorkspaceBorders.left,KWorkspaceBorders.top,KWorkspaceBorders.right,KWorkspaceBorders.bottom);
	settings.setValue("WorkspaceBorders",workspaceBorders);
	QRect workspaceBorderColor(KWorkspaceBorderColor.r*255,KWorkspaceBorderColor.g*255,KWorkspaceBorderColor.b*255,KWorkspaceBorderColor.a*255);
	settings.setValue("WorkspaceBorderColor",workspaceBorderColor);
	QRect workspaceInnerColor(KWorkspaceInnerColor.r*255,KWorkspaceInnerColor.g*255,KWorkspaceInnerColor.b*255,KWorkspaceInnerColor.a*255);
	settings.setValue("WorkspaceInnerColor",workspaceInnerColor);

	settings.endGroup();
}

void Settings::ReadSettings()
{
	QSettings settings("DicomPresenter.ini",
		QSettings::IniFormat);
	settings.beginGroup("MainWindow");
	KWorkspaceTextureWidth =settings.value("WorkspaceTextureWidth", 1024).toInt();
	KWorkspaceTextureHeight = settings.value("WorkspaceTextureHeight", 768).toInt();
	KInfoPanelSpacing =settings.value("InfoPanelSpacing", 2).toInt();
	KInfoPanelMarginLeft=settings.value("InfoPanelMarginLeft", 4).toInt();
	KInfoPanelMarginTop=settings.value("InfoPanelMarginTop", 2).toInt();
	KInfoPanelMarginRight=settings.value("InfoPanelMarginRight", 2).toInt();
	KInfoPanelMarginBottom=settings.value("InfoPanelMarginBottom", 2).toInt();

//WORKSPACE
	QRect workspaceBorders = settings.value("WorkspaceBorders", QRect(10,10,10,10)).toRect();
	KWorkspaceBorders.left = workspaceBorders.left();
	KWorkspaceBorders.top=	workspaceBorders.top();
	KWorkspaceBorders.right=workspaceBorders.right();
	KWorkspaceBorders.bottom=workspaceBorders.bottom();

	QRectF workspaceBorderColor = settings.value("WorkspaceBorderColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceBorderColor.r = workspaceBorderColor.left()/255.0f;
	KWorkspaceBorderColor.g=	workspaceBorderColor.top()/255.0f;
	KWorkspaceBorderColor.b=workspaceBorderColor.width()/255.0f;
	KWorkspaceBorderColor.a=workspaceBorderColor.height()/255.0f;

	QRectF workspaceInnerColor = settings.value("WorkspaceInnerColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceInnerColor.r = workspaceInnerColor.left()/255.0f;
	KWorkspaceInnerColor.g = workspaceInnerColor.top()/255.0f;
	KWorkspaceInnerColor.b = workspaceInnerColor.width()/255.0f;
	KWorkspaceInnerColor.a = workspaceInnerColor.height()/255.0f;

//IMAGE
	QRect imageBorders = settings.value("ImageBorders", QRect(10,10,10,10)).toRect();
	KImageBorders.left = imageBorders.left();
	KImageBorders.top=	imageBorders.top();
	KImageBorders.right=imageBorders.right()-imageBorders.left()+1;
	KImageBorders.bottom=imageBorders.bottom()-imageBorders.top()+1;

	QRectF imageBorderColor = settings.value("ImageBorderColor", QRectF(1,1,1,1)).toRectF();
	KImageBorderColor.r = imageBorderColor.left()/255.0f;
	KImageBorderColor.g=	imageBorderColor.top()/255.0f;
	KImageBorderColor.b=imageBorderColor.width()/255.0f;
	KImageBorderColor.a=imageBorderColor.height()/255.0f;

	QRectF imageInnerColor = settings.value("ImageInnerColor", QRectF(1,1,1,1)).toRectF();
	KImageInnerColor.r = imageInnerColor.left()/255.0f;
	KImageInnerColor.g = imageInnerColor.top()/255.0f;
	KImageInnerColor.b = imageInnerColor.width()/255.0f;
	KImageInnerColor.a = imageInnerColor.height()/255.0f;

	//WORKSPACE EXPLORER
	QRect workspaceExplorerBorders = settings.value("WorkspaceExplorerBorders", QRect(10,10,10,10)).toRect();
	KWorkspaceExplorerBorders.left = workspaceExplorerBorders.left();
	KWorkspaceExplorerBorders.top=	workspaceExplorerBorders.top();
	KWorkspaceExplorerBorders.right=workspaceExplorerBorders.width();
	KWorkspaceExplorerBorders.bottom=workspaceExplorerBorders.height();

	QRectF workspaceExplorerBorderColor = settings.value("WorkspaceExplorerBorderColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceExplorerBorderColor.r = workspaceExplorerBorderColor.left()/255.0f;
	KWorkspaceExplorerBorderColor.g = workspaceExplorerBorderColor.top()/255.0f;
	KWorkspaceExplorerBorderColor.b = workspaceExplorerBorderColor.width()/255.0f;
	KWorkspaceExplorerBorderColor.a = workspaceExplorerBorderColor.height()/255.0f;

	QRectF workspaceExplorerInnerColor = settings.value("WorkspaceExplorerInnerColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceExplorerInnerColor.r = workspaceExplorerInnerColor.left()/255.0f;
	KWorkspaceExplorerInnerColor.g = workspaceExplorerInnerColor.top()/255.0f;
	KWorkspaceExplorerInnerColor.b = workspaceExplorerInnerColor.width()/255.0f;
	KWorkspaceExplorerInnerColor.a = workspaceExplorerInnerColor.height()/255.0f;

	QRectF workspaceExplorerTextColor = settings.value("WorkspaceExplorerTextColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceExplorerTextColor.r = workspaceExplorerTextColor.left()/255.0f;
	KWorkspaceExplorerTextColor.g = workspaceExplorerTextColor.top()/255.0f;
	KWorkspaceExplorerTextColor.b = workspaceExplorerTextColor.width()/255.0f;
	KWorkspaceExplorerTextColor.a = workspaceExplorerTextColor.height()/255.0f;


		//WORKSPACE SNAPSHOT
	QRect workspaceSnapshotBorders = settings.value("WorkspaceSnapshotBorders", QRect(10,10,10,10)).toRect();
	KWorkspaceSnapshotBorders.left = workspaceSnapshotBorders.left();
	KWorkspaceSnapshotBorders.top=	workspaceSnapshotBorders.top();
	KWorkspaceSnapshotBorders.right=workspaceSnapshotBorders.width();
	KWorkspaceSnapshotBorders.bottom=workspaceSnapshotBorders.height();

	QRectF workspaceSnapshotBorderColor = settings.value("WorkspaceSnapshotBorderColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceSnapshotBorderColor.r = workspaceSnapshotBorderColor.left()/255.0f;
	KWorkspaceSnapshotBorderColor.g = workspaceSnapshotBorderColor.top()/255.0f;
	KWorkspaceSnapshotBorderColor.b = workspaceSnapshotBorderColor.width()/255.0f;
	KWorkspaceSnapshotBorderColor.a = workspaceSnapshotBorderColor.height()/255.0f;

	QRectF workspaceSnapshotInnerColor = settings.value("WorkspaceSnapshotInnerColor", QRectF(1,1,1,1)).toRectF();
	KWorkspaceSnapshotInnerColor.r = workspaceSnapshotInnerColor.left()/255.0f;
	KWorkspaceSnapshotInnerColor.g = workspaceSnapshotInnerColor.top()/255.0f;
	KWorkspaceSnapshotInnerColor.b = workspaceSnapshotInnerColor.width()/255.0f;
	KWorkspaceSnapshotInnerColor.a = workspaceSnapshotInnerColor.height()/255.0f;

	//IMAGE EXPLORER
	QRect imageExplorerBorders = settings.value("ImageExplorerBorders", QRect(10,10,10,10)).toRect();
	KImageExplorerBorders.left = imageExplorerBorders.left();
	KImageExplorerBorders.top=	imageExplorerBorders.top();
	KImageExplorerBorders.right=imageExplorerBorders.width();
	KImageExplorerBorders.bottom=imageExplorerBorders.height();

	QRectF imageExplorerBorderColor = settings.value("ImageExplorerBorderColor", QRectF(1,1,1,1)).toRectF();
	KImageExplorerBorderColor.r = imageExplorerBorderColor.left()/255.0f;
	KImageExplorerBorderColor.g=	imageExplorerBorderColor.top()/255.0f;
	KImageExplorerBorderColor.b=imageExplorerBorderColor.width()/255.0f;
	KImageExplorerBorderColor.a=imageExplorerBorderColor.height()/255.0f;

	QRectF imageExplorerInnerColor = settings.value("ImageExplorerInnerColor", QRectF(1,1,1,1)).toRectF();
	KImageExplorerInnerColor.r = imageExplorerInnerColor.left()/255.0f;
	KImageExplorerInnerColor.g = imageExplorerInnerColor.top()/255.0f;
	KImageExplorerInnerColor.b = imageExplorerInnerColor.width()/255.0f;
	KImageExplorerInnerColor.a = imageExplorerInnerColor.height()/255.0f;

	QRectF imageExplorerTextColor = settings.value("ImageExplorerTextColor", QRectF(1,1,1,1)).toRectF();
	KImageExplorerTextColor.r = imageExplorerTextColor.left()/255.0f;
	KImageExplorerTextColor.g = imageExplorerTextColor.top()/255.0f;
	KImageExplorerTextColor.b = imageExplorerTextColor.width()/255.0f;
	KImageExplorerTextColor.a = imageExplorerTextColor.height()/255.0f;
	
	//QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	settings.endGroup();
	iSettingsRead = true;
}

int Settings::GetIntegerConstant(TSettingConstants constant)
{
	if(!iSettingsRead)
	{
	//	WriteSettings();
		ReadSettings();
	}
	switch(constant)
	{
	case EWorkspaceTextureWidth:
		{
			return KWorkspaceTextureWidth;
			break;
		}
	case EWorkspaceTextureHeight:
		{
			return KWorkspaceTextureHeight;
			break;
		}
	case EInfoPanelSpacing:
		{
			return KInfoPanelSpacing;
			break;
		}
	case EInfoPanelMarginLeft:
		{
			return KInfoPanelMarginLeft;
			break;
		}
	case EInfoPanelMarginTop:
		{
			return KInfoPanelMarginTop;
			break;
		}
	case EInfoPanelMarginRight:
		{
			return KInfoPanelMarginRight;
			break;
		}
	case EInfoPanelMarginBottom:
		{
			return KInfoPanelMarginBottom;
			break;
		}
	case EMaximumFramesToLoad:
		{
			return KMaximumFramesToLoad;
			break;
		}
	default:
		return 1;
		break;

	};
	return 0;
}

TBorders Settings::GetBordersConstant(TSettingConstants constant)
{
	if(!iSettingsRead)
	{
	//	WriteSettings();
		ReadSettings();
	}
	switch(constant)
	{
	case 	EImageBorders:
		{
			return KImageBorders;
			break;
		}
		case 	EImageExplorerBorders:
		{
			return KImageExplorerBorders;
			break;
		}
			case 	EWorkspaceExplorerBorders:
		{
			return KWorkspaceExplorerBorders;
			break;
		}
			case 	EWorkspaceBorders:
		{
			return KWorkspaceBorders;
			break;
		}
			case 	EWorkspaceSnapshotBorders:
		{
			return KWorkspaceSnapshotBorders;
			break;
		}

	default:
		break;

	};
	TBorders ret = {0,0,0,0};
	
	return ret;
}
TColor Settings::GetColorConstant(TSettingConstants constant)
{
	if(!iSettingsRead)
	{
	//	WriteSettings();
		ReadSettings();
	}
	switch(constant)
	{

	case EImageBorderColor:
		{
			return KImageBorderColor;
			break;
		}
	case EImageInnerColor:
		{
			return KImageInnerColor;
			break;
		}
	case EImageExplorerBorderColor:
		{
			return KImageExplorerBorderColor;
			break;
		}
	case EImageExplorerInnerColor:
		{
			return KImageExplorerInnerColor;
			break;
		}
		case EImageExplorerTextColor:
		{
			return KImageExplorerTextColor;
			break;
		}
		case EWorkspaceExplorerBorderColor:
		{
			return KWorkspaceExplorerBorderColor;
			break;
		}
	case EWorkspaceExplorerInnerColor:
		{
			return KWorkspaceExplorerInnerColor;
			break;
		}
			case EWorkspaceExplorerTextColor:
		{
			return KWorkspaceExplorerTextColor;
			break;
		}
		case EWorkspaceBorderColor:
		{
			return KWorkspaceBorderColor;
			break;
		}
	case EWorkspaceInnerColor:
		{
			return KWorkspaceInnerColor;
			break;
		}
	case EWorkspaceSnapshotBorderColor:
		{
			return KWorkspaceSnapshotBorderColor;
			break;
		}
	case EWorkspaceSnapshotInnerColor:
		{
			return KWorkspaceSnapshotInnerColor;
			break;
		}
	default:
		break;

	};
	TColor ret = {0,0,0,0};
	return ret;
}

