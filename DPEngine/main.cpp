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

	CImage *im1 = new CImage(NULL, QString("im.dcm"), QPointF(10,10), QPointF(10,10));
	CWorkspace *workspace = new CWorkspace();
	workspace->addImage(im1);
	CWorkspaceManager::InitInstance();
	CWorkspaceManager::GetInstance()->SetActiveWorkspace(workspace);
	CWidget* widg = new CWidget(NULL);
//	widg->paint();
//	widg->show();

	return a.exec();
}
