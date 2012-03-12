#include <cwidget.h>
#include <cworkspace.h>
#include <workspacemanager.h>

CWidget *CWidget::instance = NULL;

CWidget::CWidget(QWidget *parent){
	iPixmap = new QPixmap();
	setPixmap(*iPixmap);
}
void CWidget::mousePressEvent(QMouseEvent *event){
	repaint();
}

void CWidget::paint(){
	CWorkspaceManager::GetInstance()->GetActiveWorkspace()->paint();
	QImage im = *(CWorkspaceManager::GetInstance()->GetActiveWorkspace()->iWorkspaceImage);
	iPixmap->convertFromImage(im);
	setPixmap(*iPixmap);
}

CWidget *CWidget::GetInstance(){
	return instance;
}

CWidget* CWidget::InitInstance(QWidget *parent)
{
	if(!instance)
	{
		instance = new CWidget(parent);
	}
	return instance;
}