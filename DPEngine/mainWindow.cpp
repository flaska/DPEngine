#include <QtGui/QFileDialog>

#include <mainWindow.h>
#include <infoPanel.h>
#include <workspaceManager.h>
#include <cimageexplorer.h>
//#include <animationManager.h>
//#include <saveSequenceDialog.h>
#include "api.h"

MainWindow* MainWindow::iSelfS=NULL;
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{

	iSelfS= this;
	iOpenGLInitialized = false;
	ui.setupUi(this);

	QObject::connect(ui.actionExit , SIGNAL(triggered()), 
		this, SLOT(Exit())); 
	//
	QObject::connect(ui.actionOtev_t , SIGNAL(triggered()), 
		this, SLOT(OpenFile())); 

	QObject::connect(ui.actionSaveSnapshot , SIGNAL(triggered()), 
		this, SLOT(SaveSnapshot())); 
	QObject::connect(ui.actionSaveSequence , SIGNAL(triggered()), 
		this, SLOT(SaveSequence())); 
	QObject::connect(ui.actionPlugins , SIGNAL(triggered()), 
		this, SLOT(runPlugins())); 		
	iWidget  = CWidget::InitInstance(this);
	//iAnimationManager = CAnimationManager::InitInstance();
	setCentralWidget(iWidget);
	//continues in openglinitialized function
	iDock = new QDockWidget(QString("Properties"),this);
	iDock->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	iDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea,iDock);
	Init();
}

MainWindow::~MainWindow()
{
	//delete iWorkspaceManager;
	delete iInfoPanel;
	delete iWidget;
	//delete iAnimationManager;
	
}
void MainWindow::Exit()
{
	QApplication::exit();
}
//FInish initialization
void MainWindow::Init()
{
	//iWorkspaceManager = CWorkspaceManager::InitInstance(iWidget);
	//CWorkspace * newWorkspace = new CWorkspace(iWidget,iWidget->GetDefaultWorkspacePosition(),iWidget->GetDefaultWorkspaceSize());
	//CWorkspaceManager::GetInstance()->AddWorkspace(newWorkspace);
	//newWorkspace->SetGeometry(iWidget->GetDefaultWorkspacePosition().x(),iWidget->GetDefaultWorkspacePosition().y(),iWidget->GetDefaultWorkspaceSize().x(),iWidget->GetDefaultWorkspaceSize().y());
	iWidget->show();
	iInfoPanel = CInfoPanel::InitInstance(iDock);
	CInfoPanel::GetInstance()->SetImageExplorerInfoView();
	iWidget->setGeometry(15,50,800,600);
	iOpenGLInitialized = true;
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
}

/**
* @brief Save the actual workspace animation
*/
void MainWindow::SaveSequence()
{
	/*
	SaveSequenceDialog dial;
	int ret = dial.exec();
	if(ret)
	{
		QString fileName = QFileDialog::getSaveFileName(this, tr("Save sequence"),
			"",
			tr("video file (*.avi)"));
		CAnimationManager::GetInstance()->SaveSequence(fileName);
	}
	*/
}

/**
* @brief Save the actual workspace as image file
*/
void MainWindow::SaveSnapshot()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save snapshot"),
		"",
		tr("picture (*.png)"));
	//TODO CWorkspaceManager::GetInstance()->GetActiveWorkspace()->SaveSnapshot(fileName);
}


void MainWindow::OpenFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"", tr("DICOM Images (*.dcm *.ima)"));
	CImageExplorer::GetInstance()->OpenImage(fileName);
}
void MainWindow::mousePressEvent ( QMouseEvent * e )
{
	//iGLWidget->SetOpenGLInterpolation(true);
}

void MainWindow::runPlugins()
{
	//CWorkspaceManager::GetInstance()->GetActiveWorkspace()->SaveSnapshot(QString("projekt-data.pgm"));
	CImage *im=CWorkspaceManager::GetInstance()->GetActiveWorkspace()->GetActiveImage();
	im->save(QString("projekt-data.pgm"));
	libraryLoader *loader=new libraryLoader();
	loader->init();
}


