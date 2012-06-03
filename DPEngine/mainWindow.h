#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>
#include <ui_mainwindow.h>
#include <CWidget.h>
#include <infopanel.h>
//#include <animationManager.h>
class CInfoPanel;
class CWorkspaceManager;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();
	void mousePressEvent ( QMouseEvent * e );
	void Init();

public slots:
	void Exit();
	void OpenFile();
	void SaveSnapshot();
	void SaveSequence();
	void runPlugins();
public:
void resizeEvent(QResizeEvent* event);
	static MainWindow* iSelfS;
private:
	Ui::DicomPresenter ui;
	CInfoPanel *iInfoPanel;
	CWidget *iWidget;
	CWorkspaceManager* iWorkspaceManager;
	QDockWidget *iDock;
	bool iOpenGLInitialized;
	//CAnimationManager * iAnimationManager;
};

#endif // MAINWINDOW_H
