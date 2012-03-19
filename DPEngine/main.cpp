#include <QtGui/QApplication>
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmjpeg/djdecode.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmimage/diregist.h>
#include <dicom3DTexture.h>
#include <cwidget.h>
#include <cimage.h>
#include <cworkspace.h>
#include <workspacemanager.h>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//CWidget* widg = new CWidget(NULL);
	CWidget::InitInstance(NULL);
	CWorkspace *workspace = new CWorkspace();
	CWorkspaceManager::InitInstance();
	CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);
	CWidget::GetInstance()->paint();
	CWidget::GetInstance()->show();
	return a.exec();
}
