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
#include <cimageexplorer.h>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CWidget::InitInstance(NULL);
	CWidget::GetInstance()->paint();
	CWidget::GetInstance()->show();
	CImageExplorer::GetInstance()->OpenImage(QString("im1.dcm"));
	CImageExplorer::GetInstance()->OpenImage(QString("im2.dcm"));
	return a.exec();
}
