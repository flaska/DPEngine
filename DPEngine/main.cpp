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
#include <mainwindow.h>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow w;
    w.show();
	//CWidget::InitInstance(NULL);
	//CWidget::GetInstance()->paint();
	//CWidget::GetInstance()->show();
	//CImageExplorer::GetInstance()->OpenImage(QString("s:/DP/DP/bin/Knee/IM-0001-0001.dcm"));
	return a.exec();
}
