#ifndef CInfoPanel_H_asdasd456
#define CInfoPanel_H_asdasd456
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QComboBox>
#include <QtGui/QListWidget>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QSpinBox>


#include <QtGui/QLabel>
#include <QtGui/QPushButton>

#include <QtGui/QApplication>
#include <cworkspace.h>
//#include <animation/animation.h>
//forward


class CImage;


class CInfoPanel : public QObject
{
	Q_OBJECT
private:

	void CreateWorkspaceInfoGroupBox(QDockWidget *parent);
	void CreateWorkspaceGroupBox(QDockWidget *parent);
	void CreateWorkspaceExplorerGroupBox(QDockWidget *parent);
	void CreateImageExplorerGroupBox(QDockWidget *parent);
	void CreateDicomHeaderGroupBox(QDockWidget *parent);
	void CreateImageAnimationGroupBox(QDockWidget *parent);
	void CreateImageInfoGroupBox(QDockWidget *parent);
	void CreateGlobalAnimationPanel(QDockWidget *parent);	

public:
	CImage* GetSourceImage();
	CInfoPanel(QDockWidget *parent);
	~CInfoPanel();
	void SetWorkspaceInfoView();
	void SetWorkspaceExplorerInfoView();
	void SetImageExplorerInfoView();
	static CInfoPanel* InitInstance(QDockWidget *parent = NULL);
	static CInfoPanel* GetInstance();
	void SetSourceImage(CImage *source);
	void SelectDerivedImage(CImage *image);
private:
	static bool iDeleted;
	static CInfoPanel *instance;	
	static QDockWidget *iParent;
	public slots:
		void SwitchToPlanarWorkspace();
		void ImageWindowWidthChanged(int value);
		void ImageWindowCenterChanged(int value);
		void ImageZoomChanged(double zoom);
		void AnimationMSIntervalChanged(double);
		void ImageZoomChecked(int);
		void ImageWindowChecked(int);
		void ImageOrientationChecked(int);

		void ImageFrameDataChecked(int value);
		void ImageFrameDataChanged(int value);
		void ImageOrientationSelected( const QString&);
		void	ImageNameChanged(const QString&);
		void WorkspaceLayoutSelected( const QString&);
		void	WorkspaceNameChanged(const QString& text);
		void TableOfOpenedImagesClicked( int row, int column);
		void AnimationStateChanged(bool state);
		void AnimationStopFrameChanged(int val);
		void AnimationStartFrameChanged(int val);
		void CreateNewImageCopy();
		void CreateNewWorkspace();
		void CreateNewPlanarWorkspace();
		void OpenNewImage();
		void GlobalAnimationPauseChecked(int value);
		void GlobalAnimationRestartAll();
		void GlobalAnimationSpeedChanged(double value);
private:
//Global animation panel
	QGroupBox *iGlobalAnimationGroupBox;
	QCheckBox *iGlobalAnimationPauseCheckbox;
	QPushButton *iGlobalAnimationRestartAllButton;
	QFrame* iGlobalAnimationSpeedFrame;
	QLabel* iGlobalAnimationSpeedLabel;
	QDoubleSpinBox* iGlobalAnimationSpeedField;
	QLabel *iGlobalAnimationSpeedLabelX;
	
	CImage *iSourceImage;
	QGroupBox *iImageInfoGroupBox;
	QGroupBox *iAnimationGroupBox;
	QLabel *iLblImageName;

	QLineEdit *iTxtImageName;
	QLabel*	iLblImageOrientation;
	//QCheckBox* iCheckBoxAnimate;
	QFrame* iAnimationMSIntervalFrame;
	QLabel *iLblAnimationMSInterval;
	QLabel *iLblAnimationMSLabel;
	QDoubleSpinBox* iAnimationMSIntervalField;

	QFrame* iAnimationStartStopFrame;

	QLabel* iLblAnimationStart;
	QSpinBox* iAnimationStartField;
	QLabel* iLblAnimationStop;
	QSpinBox* iAnimationStopField;
	

	QComboBox*	iComboImageOrientation;
	QFrame* iImageZoomFrame;
	QDoubleSpinBox* iImageZoomField;
	QCheckBox* iImageZoomCheckBox;

	QFrame *iImageWindowFrame;
	QCheckBox* iImageWindowCheckbox;
	
	QSpinBox* iImageWindowCenter;
	QSpinBox* iImageWindowWidth;

	QCheckBox *iImageOrientationCheckBox;
	

		QFrame *iImageFrameDataFrame;
	QCheckBox *iImageFrameDataCheckbox;
	

	QSpinBox *iImageFrameDataField;
	
	

	QGroupBox* iWorkspaceGroupBox;
	QGroupBox* iWorkspaceInfoGroupBox;
	QLabel* iLblWorkspaceName;
	QLineEdit* iTxtWorkspaceName;
	QLabel* iLblWorkspaceLayout;
	QComboBox* iComboLayout;

	QGroupBox* iWorkspaceExplorerGroupBox;
	QPushButton* iCreateNewWorkspaceButton;
	QPushButton* iSetMultiPlanarWorkspaceButton;
	QGroupBox* iImageExplorerGroupBox;
	QPushButton *iOpenNewImageButton;
	QGroupBox *iOpenedImageGroupBox;
	QGroupBox* iDicomHeaderGroupBox;
	
	QTableWidget *iTableHeader;

	
	QLabel *iLblListOfOpenedImagesHeader;
	//QListWidget *iListOfOpenedImages;
	QTableWidget *iTableOfOpenedImageCopies;
	QPushButton *iCreateImageButton;
	QPushButton *iMultiPlanarReconstruction;

	CWorkspace* iSourceWorkspace;

};
#endif
