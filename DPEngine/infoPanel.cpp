#include <QtGui/QPalette>
#include <iostream>
using namespace std;

#include <dicom3DTexture.h>
#include <infoPanel.h>
#include <workspaceManager.h>
#include <cwidget.h>
//#include <animation/animationManager.h>
#include <mainWindow.h>
#include <settings.h>
#include <cimageexplorer.h>

CInfoPanel* CInfoPanel::instance = NULL;
QDockWidget* CInfoPanel::iParent = NULL;
bool CInfoPanel::iDeleted = false;
void CInfoPanel::CreateWorkspaceInfoGroupBox(QDockWidget *parent)
{
	iWorkspaceInfoGroupBox = new QGroupBox(parent);
	iWorkspaceInfoGroupBox->setFlat(true);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iWorkspaceInfoGroupBox->setLayout(layout);
}

void CInfoPanel::CreateWorkspaceGroupBox(QDockWidget *parent)
{

	
	iWorkspaceGroupBox = new QGroupBox(parent);
	iWorkspaceGroupBox->setObjectName(QString::fromUtf8("groupBox"));
	iWorkspaceGroupBox->setGeometry(QRect(830, 30, 231, 651));
	iWorkspaceGroupBox->setTitle(QApplication::translate("MainWindow", "Workspace properties", 0, QApplication::UnicodeUTF8));

	QVBoxLayout *layout = new QVBoxLayout;

	iLblWorkspaceName = new QLabel(iWorkspaceGroupBox);
	iLblWorkspaceName->setObjectName(QString::fromUtf8("lblWorkspaceName"));
	//iLblWorkspaceName->setGeometry(QRect(10, 25, 201, 21));
	iLblWorkspaceName->setText(QApplication::translate("MainWindow", "name:", 0, QApplication::UnicodeUTF8));

	iTxtWorkspaceName = new QLineEdit(iWorkspaceGroupBox);
	iTxtWorkspaceName->setObjectName(QString::fromUtf8("txtWorkspaceName"));
	//iTxtWorkspaceName->setGeometry(QRect(10, 25, 201, 21));
	iTxtWorkspaceName->setText(QApplication::translate("MainWindow", "jmeno", 0, QApplication::UnicodeUTF8));
	QObject::connect(iTxtWorkspaceName , SIGNAL(textEdited(const QString &)), 
		this, SLOT(WorkspaceNameChanged(const QString &))); 


	iLblWorkspaceLayout = new QLabel(iWorkspaceGroupBox);
	iLblWorkspaceLayout->setObjectName(QString::fromUtf8("lblWorkspaceLayout"));
	//iLblWorkspaceLayout->setGeometry(QRect(10, 25, 201, 21));
	iLblWorkspaceLayout->setText(QApplication::translate("MainWindow", "layout:", 0, QApplication::UnicodeUTF8));

	iComboLayout = new QComboBox(iWorkspaceGroupBox);
	iComboLayout->setObjectName(QString::fromUtf8("comboLayout"));
	//iComboLayout->setGeometry(QRect(10, 25, 201, 21));
	iComboLayout->addItem(QString("Growing grids layout-vertical"));
	iComboLayout->addItem(QString("Growing grids layout-horizontal"));
	iComboLayout->addItem(QString("Free layout"));
	iComboLayout->setEditable(false);
	QObject::connect(iComboLayout , SIGNAL(activated(const QString &)), 
		this, SLOT(WorkspaceLayoutSelected(const QString&))); 
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	layout->addWidget(iLblWorkspaceName);
	layout->addWidget(iTxtWorkspaceName);
	layout->addWidget(iLblWorkspaceLayout);
	layout->addWidget(iComboLayout);
	iWorkspaceGroupBox->setLayout(layout);


}
void CInfoPanel::ImageZoomChanged(double zoom)
{
	if(iSourceImage)
	{
		iSourceImage->SetZoom(zoom);
		CWidget::GetInstance()->paint();
	}
}

void CInfoPanel::AnimationMSIntervalChanged(double msInterval)
{
	if(iSourceImage)
	{
//		if(iSourceImage->GetAnimation())
		{
//			iSourceImage->GetAnimation()->SetMSInterval(msInterval);
		}
	}
}
void CInfoPanel::ImageWindowWidthChanged(int value)
{
	if(iSourceImage)
	{
		TImageWindow window = iSourceImage->GetImageWindow();
		window.width = value;
		iSourceImage->SetImageWindow(window);
	}
}

void CInfoPanel::ImageWindowCenterChanged(int value)
{
	if(iSourceImage)
	{
		TImageWindow window = iSourceImage->GetImageWindow();
		window.center = value;
		iSourceImage->SetImageWindow(window);
	}
}
	void CInfoPanel::ImageFrameDataChecked(int value)
	{
		if(iSourceImage)
		{
//		iSourceImage->SetTextDisplay(EDisplayTextFrameData, value);
		}
	}
void CInfoPanel::ImageFrameDataChanged(int value){
	if(iSourceImage){
		iSourceImage->MoveToFrame(value);
	}
}

void CInfoPanel::GlobalAnimationPauseChecked(int value)
	{
//	if(CAnimationManager::GetInstance())
	{
//		CAnimationManager::GetInstance()->PauseAll(value);
	}
	}

	void CInfoPanel::GlobalAnimationSpeedChanged(double value)
	{
//		if(CAnimationManager::GetInstance())
	{
//		CAnimationManager::GetInstance()->ChangeGlobalSpeedFactor(value);
	}
	}
void CInfoPanel::GlobalAnimationRestartAll()
{
//	if(CAnimationManager::GetInstance())
	{
//		CAnimationManager::GetInstance()->RestartAll();
	}
}
void CInfoPanel::ImageWindowChecked(int value)
{
	if(iSourceImage)
	{
//		iSourceImage->SetTextDisplay(EDisplayTextWindow, value);
	}
}
void CInfoPanel::ImageOrientationChecked(int value)
{
	if(iSourceImage)
	{
//		iSourceImage->SetTextDisplay(EDisplayTextOrientation, value);

	}
}
void CInfoPanel::ImageZoomChecked(int value)
{
	if(iSourceImage)
	{
//		iSourceImage->SetTextDisplay(EDisplayTextZoom, value);
	}
}
void CInfoPanel::ImageOrientationSelected( const QString& str)
{
	int index = iComboImageOrientation->currentIndex();
	if(iSourceImage)
	{
//		iSourceImage->SetOrientation((TImageAxisOrientation)index);
	}

}
void	CInfoPanel::ImageNameChanged(const QString& text)
{
	if(iSourceImage)
	{

//		iSourceImage->SetName(iTxtImageName->text());
	}
}

void CInfoPanel::WorkspaceLayoutSelected( const QString& str)
{
	int index = iComboLayout->currentIndex();
	if(iSourceWorkspace)
	{
//		iSourceWorkspace->SetLayout((TLayoutType)index);
		if(	CWidget::GetInstance())
		{
			CWidget::GetInstance()->paint();
		}
	}


}
void	CInfoPanel::WorkspaceNameChanged(const QString& text)
{
	if(iSourceWorkspace)
	{

//		iSourceWorkspace->SetName(iTxtWorkspaceName->text());
	}
}
void CInfoPanel::CreateWorkspaceExplorerGroupBox(QDockWidget *parent)
{
	iWorkspaceExplorerGroupBox = new QGroupBox(parent);
	iWorkspaceExplorerGroupBox->setFlat(true);

iCreateNewWorkspaceButton = new QPushButton(parent);
	iCreateNewWorkspaceButton->setText(QApplication::translate("MainWindow", "Create new workspace", 0, QApplication::UnicodeUTF8));
	QObject::connect(iCreateNewWorkspaceButton , SIGNAL(clicked()), 
		this, SLOT(CreateNewWorkspace())); 

	iSetMultiPlanarWorkspaceButton = new QPushButton(parent);
	iSetMultiPlanarWorkspaceButton->setText(QApplication::translate("MainWindow", "Choose Multi-Planar Workspace", 0, QApplication::UnicodeUTF8));
	QObject::connect(iSetMultiPlanarWorkspaceButton , SIGNAL(clicked()), 
		this, SLOT(SwitchToPlanarWorkspace())); 

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	layout->addWidget(iCreateNewWorkspaceButton);
	layout->addWidget(iSetMultiPlanarWorkspaceButton);
	iWorkspaceExplorerGroupBox->setLayout(layout);
}

void CInfoPanel::SwitchToPlanarWorkspace(){
	CWorkspaceExplorer::GetInstance()->SelectPlanarWorkspace();
}

void CInfoPanel::CreateDicomHeaderGroupBox(QDockWidget *parent)
{
	iDicomHeaderGroupBox = new QGroupBox(parent);
	iDicomHeaderGroupBox->setObjectName(QString::fromUtf8("dicomHeadergroupBox"));
	iDicomHeaderGroupBox->setGeometry(QRect(830, 30, 231, 651));
	iDicomHeaderGroupBox->setTitle(QApplication::translate("MainWindow", "Dicom Header", 0, QApplication::UnicodeUTF8));

	
	iTableHeader = new QTableWidget (1,2,iDicomHeaderGroupBox);
	iTableHeader->setFont(QFont(QString("Arial"),8));
	iTableHeader->setObjectName(QString::fromUtf8("tableView"));
	iTableHeader->setGeometry(QRect(10, 260, 211, 441));
	iTableHeader->setFrameShape(QFrame::StyledPanel);
	iTableHeader->setFrameShadow(QFrame::Sunken);
	iTableHeader->verticalHeader()->hide();

	QStringList headers;
	headers << "Tag" << "Value";
	iTableHeader->setHorizontalHeaderLabels(headers);
	QVBoxLayout* layout=new QVBoxLayout();
	layout->addWidget(iTableHeader);
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iDicomHeaderGroupBox->setLayout(layout);
}
void CInfoPanel::CreateImageAnimationGroupBox(QDockWidget *parent)
{
	//Animation
	iAnimationGroupBox = new QGroupBox(parent);
	iAnimationGroupBox->setObjectName(QString::fromUtf8("animationGroupBox"));
	iAnimationGroupBox->setGeometry(QRect(830, 30, 231, 651));
	iAnimationGroupBox->setTitle(QApplication::translate("MainWindow", "Animation properties", 0, QApplication::UnicodeUTF8));
	iAnimationGroupBox->setCheckable(true);
	QObject::connect(iAnimationGroupBox , SIGNAL(toggled ( bool)), 
		this, SLOT(AnimationStateChanged(bool))); 
	void toggled(bool);
	/*iCheckBoxAnimate = new QCheckBox(iImageInfoGroupBox);
	iCheckBoxAnimate->setObjectName(QString::fromUtf8("chkboxAnimate"));
	iCheckBoxAnimate->setText(QApplication::translate("MainWindow", "animate", 0, QApplication::UnicodeUTF8));
	QObject::connect(iCheckBoxAnimate , SIGNAL(stateChanged ( int)), 
	this, SLOT(AnimationStateChanged(int))); 
	*/

	iAnimationMSIntervalFrame = new QFrame(iImageInfoGroupBox);
	QHBoxLayout *MSIntervalLayout = new QHBoxLayout();
	iLblAnimationMSInterval = new QLabel(iAnimationMSIntervalFrame);
	iLblAnimationMSInterval->setObjectName(QString::fromUtf8("lblAnimationMSInterval"));
	iLblAnimationMSInterval->setText(QApplication::translate("MainWindow", "Frame interval:", 0, QApplication::UnicodeUTF8));

	iAnimationMSIntervalField = new QDoubleSpinBox(iAnimationMSIntervalFrame);
	iAnimationMSIntervalField->setObjectName(QString::fromUtf8("ms interval field"));
	
	iAnimationMSIntervalField->setMaximum(10000);
	iAnimationMSIntervalField->setMinimum(1);
	iAnimationMSIntervalField->setValue(40.0);
	QObject::connect(iAnimationMSIntervalField , SIGNAL(valueChanged(double)), 
		this, SLOT(AnimationMSIntervalChanged(double))); 
	//iFPSField->setText(QApplication::translate("MainWindow", "FPS", 0, QApplication::UnicodeUTF8));

		iLblAnimationMSLabel = new QLabel(iAnimationMSIntervalFrame);
	iLblAnimationMSLabel->setObjectName(QString::fromUtf8("lblAnimationMSlabel"));
	iLblAnimationMSLabel->setText(QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8));


	MSIntervalLayout->addWidget(iLblAnimationMSInterval);
	MSIntervalLayout->addWidget(iAnimationMSIntervalField);
	MSIntervalLayout->addWidget(iLblAnimationMSLabel);
	MSIntervalLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	MSIntervalLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iAnimationMSIntervalFrame->setLayout(MSIntervalLayout);

	iAnimationStartStopFrame = new QFrame(iImageInfoGroupBox);
	QHBoxLayout *startStopFrameLayout = new QHBoxLayout();
	iLblAnimationStart = new QLabel(iAnimationStartStopFrame);
	iLblAnimationStart->setObjectName(QString::fromUtf8("lblAnimationStart"));
	iLblAnimationStart->setText(QApplication::translate("MainWindow", "start:", 0, QApplication::UnicodeUTF8));
	iAnimationStartField = new QSpinBox(iAnimationStartStopFrame);
	iAnimationStartField->setObjectName(QString::fromUtf8("animationStartField"));
	
	iAnimationStartField->setMaximum(1);
	iAnimationStartField->setMinimum(1);
	iAnimationStartField->setValue(1);
	QObject::connect(iAnimationStartField , SIGNAL(valueChanged(int)), 
		this, SLOT(AnimationStartFrameChanged(int))); 

	iLblAnimationStop = new QLabel(iAnimationStartStopFrame);
	iLblAnimationStop->setObjectName(QString::fromUtf8("lblAnimationStop"));
	iLblAnimationStop->setText(QApplication::translate("MainWindow", "stop:", 0, QApplication::UnicodeUTF8));
	iAnimationStopField = new QSpinBox(iAnimationStartStopFrame);
	iAnimationStopField->setObjectName(QString::fromUtf8("animationStopField"));
	iAnimationStopField->setValue(1);
	iAnimationStopField->setMaximum(1);
	iAnimationStopField->setMinimum(1);
	QObject::connect(iAnimationStopField , SIGNAL(valueChanged(int)), 
		this, SLOT(AnimationStopFrameChanged(int)));

startStopFrameLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	startStopFrameLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	startStopFrameLayout->addWidget(iLblAnimationStart);
	startStopFrameLayout->addWidget(iAnimationStartField);
	startStopFrameLayout->addWidget(iLblAnimationStop);
	startStopFrameLayout->addWidget(iAnimationStopField);

	iAnimationStartStopFrame->setLayout(startStopFrameLayout);

	QLayout *layout= new QVBoxLayout();
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	//layout->addWidget(iCheckBoxAnimate);
	layout->addWidget(iAnimationMSIntervalFrame);
	layout->addWidget(iAnimationStartStopFrame);
	iAnimationGroupBox->setLayout(layout);
}
void CInfoPanel::CreateGlobalAnimationPanel(QDockWidget *parent)
{
	iGlobalAnimationGroupBox = new QGroupBox(parent);
	iGlobalAnimationGroupBox->setObjectName(QString::fromUtf8("globalAnimationGroupBox"));
	iGlobalAnimationGroupBox->setTitle(QApplication::translate("MainWindow", "Global animation panel", 0, QApplication::UnicodeUTF8));

	iGlobalAnimationPauseCheckbox = new QCheckBox(iGlobalAnimationGroupBox);
	iGlobalAnimationPauseCheckbox->setObjectName(QString::fromUtf8("globalAnimationGroupBox"));
	iGlobalAnimationPauseCheckbox->setText(QApplication::translate("MainWindow", "Pause all", 0, QApplication::UnicodeUTF8));
	QObject::connect(iGlobalAnimationPauseCheckbox , SIGNAL(stateChanged(int)), 
		this, SLOT(GlobalAnimationPauseChecked(int))); 

	iGlobalAnimationRestartAllButton = new QPushButton(iGlobalAnimationGroupBox);
	iGlobalAnimationRestartAllButton->setObjectName(QString::fromUtf8("globalAnimationRestartAllButton"));
	iGlobalAnimationRestartAllButton->setText(QApplication::translate("MainWindow", "Restart all", 0, QApplication::UnicodeUTF8));
	QObject::connect(iGlobalAnimationRestartAllButton , SIGNAL(clicked()), 
		this, SLOT(GlobalAnimationRestartAll()));


	iGlobalAnimationSpeedFrame = new QFrame(iGlobalAnimationGroupBox);
	QHBoxLayout* speedframeLayout = new QHBoxLayout();
	iGlobalAnimationSpeedLabel = new QLabel(iGlobalAnimationSpeedFrame);
	iGlobalAnimationSpeedLabel->setObjectName(QString::fromUtf8("globalAnimationSpeedLabel"));
	iGlobalAnimationSpeedLabel->setText(QApplication::translate("MainWindow", "Speed factor", 0, QApplication::UnicodeUTF8));

	iGlobalAnimationSpeedField = new QDoubleSpinBox(iGlobalAnimationSpeedFrame);
	iGlobalAnimationSpeedField->setObjectName(QString::fromUtf8("global animation speed field"));
	
	iGlobalAnimationSpeedField->setMaximum(1000);
	iGlobalAnimationSpeedField->setMinimum(0);
	iGlobalAnimationSpeedField->setValue(1.0);
	QObject::connect(iGlobalAnimationSpeedField , SIGNAL(valueChanged(double)), 
		this, SLOT(GlobalAnimationSpeedChanged(double))); 
	iGlobalAnimationSpeedLabelX = new QLabel(iGlobalAnimationSpeedFrame);
	iGlobalAnimationSpeedLabelX->setObjectName(QString::fromUtf8("globalAnimationSpeedLabelX"));
	iGlobalAnimationSpeedLabelX->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));

	speedframeLayout->addWidget(iGlobalAnimationSpeedLabel);
	speedframeLayout->addWidget(iGlobalAnimationSpeedField);
	speedframeLayout->addWidget(iGlobalAnimationSpeedLabelX);
	speedframeLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	speedframeLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iGlobalAnimationSpeedFrame->setLayout(speedframeLayout);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	layout->addWidget(iGlobalAnimationPauseCheckbox);
	layout->addWidget(iGlobalAnimationRestartAllButton);
	layout->addWidget(iGlobalAnimationSpeedFrame);

	iGlobalAnimationGroupBox->setLayout(layout);
	
}
void CInfoPanel::CreateImageInfoGroupBox(QDockWidget *parent)
{
	iImageInfoGroupBox = new QGroupBox(parent);
	iImageInfoGroupBox->setObjectName(QString::fromUtf8("imageInfogroupBox"));
	iImageInfoGroupBox->setGeometry(QRect(830, 30, 231, 651));
	iImageInfoGroupBox->setTitle(QApplication::translate("MainWindow", "Image Info", 0, QApplication::UnicodeUTF8));
	


	iLblImageName = new QLabel(iImageInfoGroupBox);
	iLblImageName->setObjectName(QString::fromUtf8("lblImageName"));
	iLblImageName->setText(QApplication::translate("MainWindow", "Name:", 0, QApplication::UnicodeUTF8));

	iTxtImageName = new QLineEdit(iImageInfoGroupBox);
	iTxtImageName->setObjectName(QString::fromUtf8("txtImageName"));
	iTxtImageName->setText(QApplication::translate("MainWindow", "jmeno", 0, QApplication::UnicodeUTF8));
	QObject::connect(iTxtImageName , SIGNAL(textEdited(const QString&)), 
		this, SLOT(ImageNameChanged(const QString&))); 



	iLblImageOrientation = new QLabel(iImageInfoGroupBox);
	iLblImageOrientation->setObjectName(QString::fromUtf8("lblImageOrientation"));
	iLblImageOrientation->setText(QApplication::translate("MainWindow", "Orientation:", 0, QApplication::UnicodeUTF8));

	iComboImageOrientation = new QComboBox(iImageInfoGroupBox);
	iComboImageOrientation->setObjectName(QString::fromUtf8("comboImageOrientation"));
	iComboImageOrientation->addItem(QString("axial"));
	iComboImageOrientation->addItem(QString("sagital"));
	iComboImageOrientation->addItem(QString("coronal"));
	iComboImageOrientation->setEditable(false);

	QObject::connect(iComboImageOrientation , SIGNAL(activated(const QString &)), 
		this, SLOT(ImageOrientationSelected(const QString&))); 

	iImageZoomFrame = new QFrame(iImageInfoGroupBox);
	iImageZoomCheckBox = new QCheckBox(iImageZoomFrame);
	iImageZoomCheckBox->setObjectName(QString::fromUtf8("checkBoxZoom"));
	iImageZoomCheckBox->setText(QApplication::translate("MainWindow", "Zoom:", 0, QApplication::UnicodeUTF8));
	QObject::connect(iImageZoomCheckBox , SIGNAL(stateChanged(int)), 
		this, SLOT(ImageZoomChecked(int))); 



	QHBoxLayout *zoomFrameLayout = new QHBoxLayout();
zoomFrameLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	zoomFrameLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iImageZoomField = new QDoubleSpinBox(iImageZoomFrame);
	iImageZoomField->setObjectName(QString::fromUtf8("imageZoomField"));
	
	iImageZoomField->setMaximum(10000.0);
	iImageZoomField->setMinimum(0.0);
	iImageZoomField->setValue(1.0);
	iImageZoomField->setSingleStep(0.1);
	QObject::connect(iImageZoomField , SIGNAL(valueChanged(double)), 
		this, SLOT(ImageZoomChanged(double))); 

	zoomFrameLayout->addWidget(iImageZoomCheckBox);
	zoomFrameLayout->addWidget(iImageZoomField);
	iImageZoomFrame->setLayout(zoomFrameLayout);


	QHBoxLayout *windowFrameLayout = new QHBoxLayout();
windowFrameLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	windowFrameLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iImageWindowFrame = new QFrame(iImageInfoGroupBox);
	iImageWindowCheckbox = new QCheckBox(iImageWindowFrame);
	iImageWindowCheckbox->setObjectName(QString::fromUtf8("checkBoxWindow"));
	iImageWindowCheckbox->setText(QApplication::translate("MainWindow", "C/W", 0, QApplication::UnicodeUTF8));
	QObject::connect(iImageWindowCheckbox , SIGNAL(stateChanged(int)), 
		this, SLOT(ImageWindowChecked(int))); 

	iImageWindowCenter = new QSpinBox(iImageWindowFrame);
	iImageWindowCenter->setObjectName(QString::fromUtf8("imageWindowCenter"));
	iImageWindowCenter->setValue(1);
	iImageWindowCenter->setMaximum(10000);
	iImageWindowCenter->setMinimum(-10000);
	QObject::connect(iImageWindowCenter , SIGNAL(valueChanged(int)), 
		this, SLOT(ImageWindowCenterChanged(int)));



	iImageWindowWidth = new QSpinBox(iImageWindowFrame);
	iImageWindowWidth->setObjectName(QString::fromUtf8("imageWindowWidth"));
	iImageWindowWidth->setValue(1);
	iImageWindowWidth->setMaximum(10000);
	iImageWindowWidth->setMinimum(-10000);
	QObject::connect(iImageWindowWidth , SIGNAL(valueChanged(int)), 
		this, SLOT(ImageWindowWidthChanged(int))); 




	windowFrameLayout->addWidget(iImageWindowCheckbox);
	windowFrameLayout->addWidget(iImageWindowCenter);
	windowFrameLayout->addWidget(iImageWindowWidth);
	iImageWindowFrame->setLayout(windowFrameLayout);


	QHBoxLayout *imageFrameDataFrameLayout = new QHBoxLayout();
imageFrameDataFrameLayout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	imageFrameDataFrameLayout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iImageFrameDataFrame = new QFrame(iImageInfoGroupBox);
	iImageFrameDataCheckbox = new QCheckBox(iImageFrameDataFrame);
	iImageFrameDataCheckbox->setObjectName(QString::fromUtf8("checkBoxImageFrameData"));
	iImageFrameDataCheckbox->setText(QApplication::translate("MainWindow", "Frame nr:", 0, QApplication::UnicodeUTF8));
	QObject::connect(iImageFrameDataCheckbox , SIGNAL(stateChanged(int)), 
		this, SLOT(ImageFrameDataChecked(int))); 

	iImageFrameDataField = new QSpinBox(iImageWindowFrame);
	iImageFrameDataField->setObjectName(QString::fromUtf8("imageWindowCenter"));
	iImageFrameDataField->setValue(1);
	iImageFrameDataField->setMaximum(10000);
	iImageFrameDataField->setMinimum(-10000);
	QObject::connect(iImageFrameDataField , SIGNAL(valueChanged(int)), 
		this, SLOT(ImageFrameDataChanged(int)));


	imageFrameDataFrameLayout->addWidget(iImageFrameDataCheckbox);
	imageFrameDataFrameLayout->addWidget(iImageFrameDataField);
	
	iImageFrameDataFrame->setLayout(imageFrameDataFrameLayout);


		iImageOrientationCheckBox = new QCheckBox(iImageInfoGroupBox);
	iImageOrientationCheckBox->setObjectName(QString::fromUtf8("imageOrientationCheckBox"));
	iImageOrientationCheckBox->setText(QApplication::translate("MainWindow", "Display orientation", 0, QApplication::UnicodeUTF8));

	QObject::connect(iImageOrientationCheckBox , SIGNAL(stateChanged(int)), 
		this, SLOT(ImageOrientationChecked(int)));

	QLayout *layout= new QVBoxLayout();
layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	layout->addWidget(iLblImageName);
	layout->addWidget(iTxtImageName);
	layout->addWidget(iLblImageOrientation);
	layout->addWidget(iComboImageOrientation);
	layout->addWidget(iImageOrientationCheckBox);
	layout->addWidget(iImageZoomFrame);
	layout->addWidget(iImageWindowFrame);
	layout->addWidget(iImageFrameDataFrame);
	
	
	iImageInfoGroupBox->setLayout(layout);
	// iImageInfoGroupBox->hide();
}
void CInfoPanel::CreateImageExplorerGroupBox(QDockWidget *parent)
{

	iImageExplorerGroupBox = new QGroupBox(parent);
	iImageExplorerGroupBox->setFlat(true);
	/*iImageExplorerGroupBox->setObjectName(QString::fromUtf8("groupBox"));
	iImageExplorerGroupBox->setGeometry(QRect(830, 30, 281, 651));
	iImageExplorerGroupBox->setTitle(QApplication::translate("MainWindow", "Image Explorer properties", 0, QApplication::UnicodeUTF8));
*/

	iOpenNewImageButton = new QPushButton(parent);
	iOpenNewImageButton->setText(QApplication::translate("MainWindow", "Open Dicom Image", 0, QApplication::UnicodeUTF8));
	QObject::connect(iOpenNewImageButton , SIGNAL(clicked()), 
		this, SLOT(OpenNewImage())); 


	iOpenedImageGroupBox = new QGroupBox(parent);
	iOpenedImageGroupBox->setObjectName(QString::fromUtf8("groupBox"));
	iOpenedImageGroupBox->setGeometry(QRect(830, 30, 231, 651));
	iOpenedImageGroupBox->setTitle(QApplication::translate("MainWindow", "Opened Image properties", 0, QApplication::UnicodeUTF8));


	iLblListOfOpenedImagesHeader = new QLabel(iOpenedImageGroupBox);

	iLblListOfOpenedImagesHeader->setObjectName(QString::fromUtf8("lblListOfOpenedImages"));
	iLblListOfOpenedImagesHeader->setGeometry(QRect(10, 25, 201, 21));
	iLblListOfOpenedImagesHeader->setText(QApplication::translate("MainWindow", "Image copies", 0, QApplication::UnicodeUTF8));
	

	iTableOfOpenedImageCopies = new QTableWidget (0,2,iOpenedImageGroupBox);
	iTableOfOpenedImageCopies->setObjectName(QString::fromUtf8("tableView"));
	iTableOfOpenedImageCopies->setGeometry(QRect(10, 260, 211, 441));
	iTableOfOpenedImageCopies->setFrameShape(QFrame::StyledPanel);
	iTableOfOpenedImageCopies->setFrameShadow(QFrame::Sunken);
	//iTableOfOpenedImageCopies->item(1,0)->setFlags(!Qt::ItemIsEditable);
	iTableOfOpenedImageCopies->setSelectionBehavior(QAbstractItemView::SelectRows);
	iTableOfOpenedImageCopies->verticalHeader()->hide();
	iTableOfOpenedImageCopies->setColumnWidth(0,80);
	QStringList headers;
	headers << "Workspace" << "Image";
	iTableOfOpenedImageCopies->setHorizontalHeaderLabels(headers);

	QObject::connect(iTableOfOpenedImageCopies , SIGNAL(cellDoubleClicked ( int , int )), 
		this, SLOT(TableOfOpenedImagesClicked( int , int ))); 


	iCreateImageButton = new QPushButton(QString("Create copy"),iOpenedImageGroupBox);
	iCreateImageButton->setGeometry(QRect(10,195,211,30));
	QObject::connect(iCreateImageButton , SIGNAL(clicked()), 
		this, SLOT(CreateNewImageCopy())); 

	iMultiPlanarReconstruction = new QPushButton(QString("Multi-planar reconstruction"),iOpenedImageGroupBox);
	iCreateImageButton->setGeometry(QRect(10,195,211,30));
	QObject::connect(iMultiPlanarReconstruction , SIGNAL(clicked()), 
	this, SLOT(CreateNewPlanarWorkspace())); 
	//flaska//

	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(iLblListOfOpenedImagesHeader);

	layout->addWidget(iTableOfOpenedImageCopies);
	layout->addWidget(iCreateImageButton);
	layout->addWidget(iMultiPlanarReconstruction);
	layout->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layout->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));

	iOpenedImageGroupBox->setLayout(layout);
	QVBoxLayout *layoutMain = new QVBoxLayout();
	layoutMain->addWidget(iOpenNewImageButton);
	layoutMain->addWidget(iOpenedImageGroupBox);
	layoutMain->setSpacing(Settings::GetIntegerConstant(EInfoPanelSpacing));
	layoutMain->setContentsMargins(Settings::GetIntegerConstant(EInfoPanelMarginLeft),Settings::GetIntegerConstant(EInfoPanelMarginTop),Settings::GetIntegerConstant(EInfoPanelMarginRight),
		Settings::GetIntegerConstant(EInfoPanelMarginBottom));
	iImageExplorerGroupBox->setLayout(layoutMain);


}

void CInfoPanel::SetWorkspaceInfoView()
{
	if(!CWorkspaceManager::GetInstance())
		return;
	
	iSourceWorkspace = CWorkspaceManager::GetInstance()->GetActiveWorkspace();
	iWorkspaceInfoGroupBox->layout()->addWidget(iWorkspaceGroupBox);
	iWorkspaceInfoGroupBox->layout()->addWidget(iImageInfoGroupBox);
	iWorkspaceInfoGroupBox->layout()->addWidget(iAnimationGroupBox);
	iWorkspaceInfoGroupBox->layout()->addWidget(iGlobalAnimationGroupBox);
	iWorkspaceInfoGroupBox->layout()->addWidget(iDicomHeaderGroupBox);
	iWorkspaceInfoGroupBox->show();
	iParent->setWidget(iWorkspaceInfoGroupBox);
	iWorkspaceGroupBox->show();
	iWorkspaceExplorerGroupBox->hide();
	iImageExplorerGroupBox->hide();
	if(iSourceWorkspace)
	{
//		iTxtWorkspaceName->setText(iSourceWorkspace->GetName());
		TLayoutType layoutType = iSourceWorkspace->GetLayout().GetType();
		iComboLayout->setCurrentIndex((int)layoutType);
		CImage* image = iSourceWorkspace->GetActiveImage();
		if(image)
		{
			SetSourceImage(image);
		}


	}
	if(iSourceImage)
	{
//		iTxtImageName->setText(iSourceImage->GetName());

//		TImageAxisOrientation imageOrientation = iSourceImage->GetOrientation();
//		iComboImageOrientation->setCurrentIndex((int)imageOrientation);
	}
}

void CInfoPanel::SetWorkspaceExplorerInfoView()
{
	
	iParent->setWidget(iWorkspaceExplorerGroupBox);
	
	if(!CWorkspaceManager::GetInstance())
		return;
	
	iSourceWorkspace = CWorkspaceManager::GetInstance()->GetActiveWorkspace();
	iWorkspaceExplorerGroupBox->layout()->addWidget(iWorkspaceGroupBox);
	iWorkspaceExplorerGroupBox->layout()->addWidget(iGlobalAnimationGroupBox);
	iWorkspaceExplorerGroupBox->layout()->addWidget(iDicomHeaderGroupBox);
	iWorkspaceExplorerGroupBox->show();
	iParent->setWidget(iWorkspaceExplorerGroupBox);
	iWorkspaceInfoGroupBox->hide();
	iImageExplorerGroupBox->hide();

	if(iSourceWorkspace)
	{
//		iTxtWorkspaceName->setText(iSourceWorkspace->GetName());
		TLayoutType layoutType = iSourceWorkspace->GetLayout().GetType();
		iComboLayout->setCurrentIndex((int)layoutType);
//		CImage* image = iSourceWorkspace->GetActiveImage();
//		if(image)
		{
//			SetSourceImage(image);
		}


	}
	if(iSourceImage)
	{
//		iTxtImageName->setText(iSourceImage->GetName());

//		TImageAxisOrientation imageOrientation = iSourceImage->GetOrientation();
//		iComboImageOrientation->setCurrentIndex((int)imageOrientation);
	}
}
void CInfoPanel::SetImageExplorerInfoView()
{
	if(!CImageExplorer::GetInstance())
		return;
	iImageExplorerGroupBox->show();
	iWorkspaceInfoGroupBox->hide();
	iWorkspaceExplorerGroupBox->hide();

	iParent->setWidget(iImageExplorerGroupBox);
	iImageExplorerGroupBox->layout()->addWidget(iImageInfoGroupBox);
	iImageExplorerGroupBox->layout()->addWidget(iAnimationGroupBox);
	iImageExplorerGroupBox->layout()->addWidget(iGlobalAnimationGroupBox);
	iImageExplorerGroupBox->layout()->addWidget(iDicomHeaderGroupBox);
	
	iImageExplorerGroupBox->layout()->update();
	iDicomHeaderGroupBox->show();
	CImage* image = CImageExplorer::GetInstance()->GetSelectedImage();
	SetSourceImage(image);
	if(iSourceImage)
	{
//		iTxtImageName->setText(iSourceImage->GetName());

//		TImageAxisOrientation imageOrientation = iSourceImage->GetOrientation();
//		iComboImageOrientation->setCurrentIndex((int)imageOrientation);
	}
}
CInfoPanel::CInfoPanel(QDockWidget *parent)
{
	iSourceImage = NULL;
	CreateImageInfoGroupBox(parent);
	CreateImageAnimationGroupBox(parent);
	CreateGlobalAnimationPanel(parent);
	CreateDicomHeaderGroupBox(parent);
	CreateWorkspaceGroupBox(parent);
	CreateWorkspaceInfoGroupBox(parent);
	CreateWorkspaceExplorerGroupBox(parent);
	CreateImageExplorerGroupBox(parent);

}

void CInfoPanel::CreateNewWorkspace()
{
	if(CWorkspaceExplorer::GetInstance())
	{
		CWorkspaceExplorer::GetInstance()->AddNewWorkspace();
	}
}
/*
void CInfoPanel::CreateNewPlanarWorkspace()
{
	if(!CWorkspaceExplorer::GetInstance())
		return;
//	if(!iSourceImage)
//		return;
	CWorkspaceExplorer::GetInstance()->CreateNewPlanarWorkspace();
	CImage *image = iSourceImage;
	if(!image)
		return;
//	CWorkspaceManager::GetInstance()->GetPlanarWorkspace()->UseImage(image);
	//CWorkspaceManager::GetInstance()->GetActiveWorkspace()->UpdateTexture();
}
*/

void CInfoPanel::OpenNewImage(){
	if(MainWindow::iSelfS){
		MainWindow::iSelfS->OpenFile();
	}
}

void CInfoPanel::CreateNewImageCopy()
{
	if(!CWorkspaceManager::GetInstance())
		return;
	if(!iSourceImage)
		return;
	CImage *image = iSourceImage->CreateDerivedImage(EImageOrientationAxial);
	if(!image)
		return;
	if(CWorkspaceManager::GetInstance()->GetActiveWorkspace())
	{
		CWorkspaceManager::GetInstance()->GetActiveWorkspace()->addImage(image);
	//CWorkspaceManager::GetInstance()->GetActiveWorkspace()->UpdateTexture();
	}
	image->SetOwner(iSourceImage);
	//update source to update list visualiyation
	SetSourceImage(iSourceImage);	
}
CInfoPanel::~CInfoPanel()
{
	iDeleted=true;
	instance = NULL;

	if(iDicomHeaderGroupBox)
		delete iDicomHeaderGroupBox;
	if(iWorkspaceGroupBox)
		delete iWorkspaceGroupBox;
	if(iImageExplorerGroupBox)
		delete iImageExplorerGroupBox;
	if(iWorkspaceExplorerGroupBox)
		delete iWorkspaceExplorerGroupBox;



}
CInfoPanel* CInfoPanel::InitInstance(QDockWidget *parent)
{
	if(!instance)
	{
		if(parent)
		{
			iParent = parent;
		}
		else
		{
			return NULL;
		}
		instance = new CInfoPanel(parent);
	}
	return instance;
}

CInfoPanel* CInfoPanel::GetInstance()
{
	return instance;
}

CImage* CInfoPanel::GetSourceImage()
{
	return iSourceImage;
}
/**
* @brief Set DICOM Header info and image info
*/
void CInfoPanel::SetSourceImage(CImage *source){
	if(!iParent)
		return;
	iSourceImage = source;
	if(iSourceImage == NULL)
		return;
	if(!(source->GetTexture()))
		return;

	//IMAGE BASIC Settings
//	iImageZoomCheckBox->setChecked(source->GetTextDisplay(EDisplayTextZoom));
	iImageZoomField->setValue(source->GetZoom());
//	iImageWindowCheckbox->setChecked(source->GetTextDisplay(EDisplayTextWindow));
	iImageWindowCenter->setValue(source->GetImageWindow().center);
	iImageWindowWidth->setValue(source->GetImageWindow().width);
//	iImageOrientationCheckBox->setChecked(source->GetTextDisplay(EDisplayTextOrientation));
//	iImageFrameDataCheckbox->setChecked(source->GetTextDisplay(EDisplayTextFrameData));

 ///////////////////////////////////

	//save frame number before it will be changed by setmaximum
	int frameNr = source->GetActualFrameNr();
	iImageFrameDataField->setMinimum(0);
	iImageFrameDataField->setMaximum(source->GetActualTextureDepth()-1);
	iImageFrameDataField->setValue(frameNr);
	
	//DICOM HEADER
	//std::cout << source->GetTexture()->GetDicomHeader().GetSeriesInfo().GetSeriesInstanceUID();
	iTableHeader->clearContents();
	int row = 0;
	iTableHeader->setRowCount(6);
	iTableHeader->setItem(row,0,new QTableWidgetItem("Image width"));
	
	iTableHeader->setItem(row,1,new QTableWidgetItem(QString::number(source->GetTexture()->GetWidth())));
	row++;
	iTableHeader->setItem(row,0,new QTableWidgetItem("Image height"));
	iTableHeader->setItem(row,1,new QTableWidgetItem(QString::number(source->GetTexture()->GetHeight())));
	row++;
		iTableHeader->setItem(row,0,new QTableWidgetItem("Image depth"));
	iTableHeader->setItem(row,1,new QTableWidgetItem(QString::number(source->GetTexture()->GetDepth())));
	row++;
		iTableHeader->setItem(row,0,new QTableWidgetItem("Slice thickness"));
		float sliceThickness =0;
		try{
			int frameNr = source->GetActualFrameNr();
			if(source->GetOrientation() != EImageOrientationAxial)
			{
				frameNr = 0;//default
			}
			CDicomHeader& header = source->GetTexture()->GetDicomHeader(frameNr);
		
			sliceThickness = header.GetImageInfo().GetSliceThickness();
			iTableHeader->setItem(row,1,new QTableWidgetItem(QString::number(sliceThickness)));
	row++;
	float slicePosition = header.GetImageInfo().GetSliceLocation();
		iTableHeader->setItem(row,0,new QTableWidgetItem("Slice position"));
		iTableHeader->setItem(row,1,new QTableWidgetItem(QString::number(slicePosition)));
	row++;
	iTableHeader->setItem(row,0,new QTableWidgetItem("Series UID"));
	iTableHeader->setItem(row,1,new QTableWidgetItem(header.GetSeriesInfo().GetSeriesInstanceUID()));
	row++;
	
	iTableHeader->setItem(row,0,new QTableWidgetItem("Patient's name"));
	iTableHeader->setItem(row,1,new QTableWidgetItem(header.GetPatientInfo().GetName ()));
	
		}
		catch (exception *e)
		{
			e;
		}
		

	//DERIVED IMAGES TABLE
	iTableOfOpenedImageCopies->clearContents();
	//Has it derived images ?? if yes it is image in image explorer window
	QListIterator<CImage*> images(source->GetDerivedImages());
	images.toFront();
	row=0;
	while(images.hasNext())
	{

		CImage *im = images.next();
		iTableOfOpenedImageCopies->setRowCount(row+1);
		iTableOfOpenedImageCopies->setItem(row,0,new QTableWidgetItem(im->GetParentWorkspace()->GetName()));
		iTableOfOpenedImageCopies->setItem(row,1,new QTableWidgetItem(im->GetName()));
		QTableWidgetItem *item = iTableOfOpenedImageCopies->item(row,0);
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		item = iTableOfOpenedImageCopies->item(row,1);
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
		row++;	
	}
/*	
	//Animation
	if(source)
	{
		CAnimation* anim = source->GetAnimation();
		if(anim)
		{
			//save ms interval before it will be changed by set maximum
				int msInterval = anim->GetMSInterval();
				int start = anim->GetStartFrame();
				int stop = anim->GetStopFrame();
			iAnimationStartField->setMaximum(iSourceImage->GetActualTextureDepth());
			iAnimationStopField->setMaximum(iSourceImage->GetActualTextureDepth());
			//iAnimationMSIntervalField->setMaximum(anim->GetStartFrame());
			iAnimationStopField->setValue(stop);
			iAnimationStartField->setValue(start);
			iAnimationMSIntervalField->setValue(msInterval);
		
			if(anim->IsActive())
			{
				iAnimationGroupBox->setChecked(true);
				//iCheckBoxAnimate->setCheckState(Qt::Checked);
			}
			else
			{
				iAnimationGroupBox->setChecked(false);
			}
		}
		else
		{
			iAnimationGroupBox->setChecked(false);
			iAnimationStartField->setMaximum(iSourceImage->GetActualTextureDepth());
			iAnimationStopField->setMaximum(iSourceImage->GetActualTextureDepth());
			
			iAnimationStopField->setValue(iSourceImage->GetActualTextureDepth());
			iAnimationStartField->setValue(1);
			iAnimationMSIntervalField->setValue(40.0f);
			//iCheckBoxAnimate->setCheckState(Qt::Unchecked);
		}
	}
*/
}

void CInfoPanel::SelectDerivedImage(CImage *image)
{/*
	if(!image->GetOwner())
	{

		return;
	}
	if(iSourceImage==NULL)
	{
		return;
	}
	QListIterator<CImage*> images(iSourceImage->GetDerivedImages());
	images.toFront();
	int counter=0;
	while(images.hasNext())
	{
		counter++;
		CImage *im  = images.next();

		if (im==image)
		{

			iTableOfOpenedImageCopies->selectRow(counter-1);
		}

	}*/
}

void CInfoPanel::TableOfOpenedImagesClicked( int row, int column)
{/*


	int counter=0;
	//while(counter < iSourceImage->GetDerivedImages().count())
	//{
	QTableWidgetItem *itemWS  = iTableOfOpenedImageCopies->item(row,0);
	QTableWidgetItem *itemIM  = iTableOfOpenedImageCopies->item(row,1);

	if(iSourceImage)
	{

		CImage *imageToSelect = iSourceImage->GetDerivedImages().at(row);
		if(imageToSelect)
		{
			CWorkspace *workspaceToSelect = imageToSelect->GetParentWorkspace();
			if(workspaceToSelect)
			{
				CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspaceToSelect);
			}

			if(CWorkspaceManager::GetInstance())
			{
				CWorkspaceManager::GetInstance()->GetActiveWorkspace()->SelectImage(imageToSelect);
			}

		}
	}


	if(CWidget::GetInstance())
	{
		CWidget::GetInstance()->updateGL();
	}*/
}

void CInfoPanel::AnimationStopFrameChanged(int val)
{/*
	if(iSourceImage)
	{
		CAnimation *animation = iSourceImage->GetAnimation();
		if(!animation)
			return;
		animation->SetStopFrame(val);
	}
*/}
void CInfoPanel::AnimationStartFrameChanged(int val)
{/*
	if(iSourceImage)
	{
		CAnimation *animation = iSourceImage->GetAnimation();
		if(!animation)
			return;
		animation->SetStartFrame(val);
	}
*/}

void CInfoPanel::AnimationStateChanged(bool state)
{/*
	if(!CAnimationManager::GetInstance())
		return;
	int stav = state;
	if(iSourceImage)
	{
		CAnimation* animation = NULL;
		if(iSourceImage->GetAnimation())
		{
			animation = iSourceImage->GetAnimation();
			animation->SetActive(state);

		}
		else
		{
			animation = CAnimationManager::GetInstance()->GetAnimation(iSourceImage);
			//animation->SetOwnerImage(iSourceImage);
			iSourceImage->SetAnimation(animation);
		}
		//TODO get animation params from UI
		if(animation)
		{
		animation->SetStartFrame(iAnimationStartField->value());
		animation->SetMSInterval(iAnimationMSIntervalField->value());
		animation->SetStopFrame(iAnimationStopField->value());
		animation->SetLoop(true);
		
		}
		animation->SetActive(state);
		}
	*/
}

