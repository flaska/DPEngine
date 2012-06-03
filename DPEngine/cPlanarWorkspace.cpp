#include <cPlanarWorkspace.h>
#include <cWidget.h>
#include <infoPanel.h>
#include <growingGridLayout.h>
#include <freeLayout.h>
#include <workspaceManager.h>
#include <cWorkspaceSnapshot.h>
#include <settings.h>


CPlanarWorkspace::CPlanarWorkspace(CObject *parent, const QPointF &position, const QPointF &size):
CObject(parent, position, size){
	//iLayout = NULL;
	iLastInnerHeight = 0;
	iLastInnerWidth = 0;
	iWorkspaceChanged = true;
	iName = new QString();
	iSaveSnapshot = false;
	iSaveSnapshotFileName = NULL;
	QString name;
	name.clear();
	name.append("MPS");
	//name.append(QString::number(CWorkspaceManager::GetInstance()->GetWorkspaces().count()));
	SetName(name);
	iImage = NULL;
	//SetLayout(layoutType);
	iWorkspaceSnapshot =new CWorkspaceSnapshot(parent,(CWorkspace*)this,QPointF(10,10), QPointF(100,100));
	SetBorders(Settings::GetBordersConstant(EWorkspaceBorders));
	SetBorderColor(Settings::GetColorConstant(EWorkspaceBorderColor));
	SetInnerColor(Settings::GetColorConstant(EWorkspaceInnerColor));
	iPlanarCrossPosition.x=0.5;
	iPlanarCrossPosition.y=0.5;
	iPlanarCrossPosition.z=0.5;
	setMouseTracking(true);
	iEventHistory = new QPoint();
	iCursorHistory = new QPoint();
	iSensitivity = 1000;
}


void CPlanarWorkspace::SetGeometry(float x, float y, float w, float h){
	QPointF oldPos = iPosition;
	if(iLastInnerHeight ==0){

		iLastInnerWidth = iSize.x()-GetBorders().left-GetBorders().right;
		iLastInnerHeight = iSize.y()-GetBorders().top-GetBorders().bottom;
	}
	int posxdif = x - oldPos.x();
	int posydif = y - oldPos.y();
	int innerWidth = w - GetBorders().left-GetBorders().right;
	int innerHeight = h- GetBorders().top-GetBorders().bottom;
	float sizeRatioX = (float)(innerWidth)/((float)iLastInnerWidth);
	float sizeRatioY = (float)(innerHeight)/((float)iLastInnerHeight);
	iLastInnerWidth = innerWidth;
	iLastInnerHeight = innerHeight;
	CObject::SetGeometry(x,y,w,h);
	UpdateTexture();
}

void CPlanarWorkspace::UseImage(CImage *image){
	iImage = image;
	if(CWidget::GetInstance())
	{
		CWidget::GetInstance()->updateGL();
	}
}


void CPlanarWorkspace::SetName( const QString &name)
{
	iName->clear();
	iName->append(name);
}

QString& CPlanarWorkspace::GetName(){
	return *iName;
}

CPlanarWorkspace::~CPlanarWorkspace(){

}

void CPlanarWorkspace::initializeGL(){

}

CWorkspaceSnapshot& CPlanarWorkspace::GetSnapshot(){
	return *iWorkspaceSnapshot;
}

void CPlanarWorkspace::SaveSnapshot(QString& fileName){
	if(fileName.isEmpty())
		return;
	iSaveSnapshot = true;
	if(iSaveSnapshotFileName){
		delete iSaveSnapshotFileName;
		iSaveSnapshotFileName = NULL;
	}
	iSaveSnapshotFileName = new QString(fileName);
	paintGL();
}

int CPlanarWorkspace::GetSaveSnapshotWidth()
{
	return iSaveSnapshotWidth;
}
int CPlanarWorkspace::GetSaveSnapshotHeight()
{
	return iSaveSnapshotHeight;
}

void CPlanarWorkspace::SetSaveSnapshotWidth(int width)
{
	iSaveSnapshotWidth = width;
}
void CPlanarWorkspace::SetSaveSnapshotHeight(int height)
{
	iSaveSnapshotHeight = height;
}


void CPlanarWorkspace::paintGL(){
	if(!iImage){
		glEnable(GL_BLEND);
		return;
	}
	iImage->PreparePlanarSlice('z',iPlanarCrossPosition);
	iImage->PreparePlanarSlice('x',iPlanarCrossPosition);
	iImage->PreparePlanarSlice('y',iPlanarCrossPosition);

	CWidget::GetInstance()->resetGLView();
	//Translate();
	DrawBorderRect();	
	DrawInnerRect();
	int ypos= CWidget::GetInstance()->GetSize().y()
		-iSize.y()
		-iPosition.y()+GetBorders().bottom;
	glViewport(iPosition.x()+GetBorders().left,
		ypos ,
		iSize.x()-GetBorders().left-GetBorders().right
		, iSize.y()-GetBorders().top-GetBorders().bottom);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1 , 0,1, 0.1, 90); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();				
	glTranslatef(0,0,-50);
	glDisable(GL_BLEND);

	iImage->DrawSliceZ();
	iImage->DrawSliceX();
	iImage->DrawSliceY();

	DrawBorders();

	glEnable(GL_BLEND);
}

void CPlanarWorkspace::DrawBorders(){
	glColor4f( 0., 1., 1., 1.); 
    glLineWidth(10); 
    glBegin(GL_LINES); 
    glVertex2f( 0., 0.); 
    glVertex2f( 0., 1.); 
    glEnd();
	glBegin(GL_LINES); 
    glVertex2f( 0., 1.); 
    glVertex2f( 1., 1.); 
    glEnd();
    glBegin(GL_LINES); 
    glVertex2f( 1., 1.); 
    glVertex2f( 1., 0.); 
    glEnd();
    glBegin(GL_LINES); 
    glVertex2f( 1., 0.); 
    glVertex2f( 0., 0.); 
    glEnd();
    glBegin(GL_LINES); 
    glVertex2f( 0.5, 0.); 
    glVertex2f( 0.5, 1.); 
    glEnd();
    glBegin(GL_LINES); 
    glVertex2f( 1., 0.5); 
    glVertex2f( 0., 0.5); 
    glEnd();
}

void CPlanarWorkspace::UpdateTexture(){
	iWorkspaceChanged =true;
}


void CPlanarWorkspace::mouseDoubleClickEvent(QMouseEvent *event){

}

void CPlanarWorkspace::wheelEvent(QWheelEvent *event){
}

void CPlanarWorkspace::SelectImage(CImage *image){

}

void CPlanarWorkspace::mousePressEvent(QMouseEvent *event){
	int thisSizeX = this->GetSize().x();
	int thisSizeY = this->GetSize().y();
	int mousePositionX = event->x();
	int mousePositionY = event->y();
	if((mousePositionX<thisSizeX/2)&&(mousePositionY<thisSizeY/2)){
		UserManipulatingSlice = SliceOrientation::z;
		CWidget::GetInstance()->setCursor(QCursor(Qt::BlankCursor));
		*iEventHistory = event->pos();
		*iCursorHistory = QCursor::pos();
	}
	if((mousePositionX>thisSizeX/2)&&(mousePositionY<thisSizeY/2)){
		UserManipulatingSlice = SliceOrientation::x;
		CWidget::GetInstance()->setCursor(QCursor(Qt::BlankCursor));
		*iEventHistory = event->pos();
		*iCursorHistory = QCursor::pos();

	}
	if((mousePositionX<thisSizeX/2)&&(mousePositionY>thisSizeY/2)){
		UserManipulatingSlice = SliceOrientation::y;
		CWidget::GetInstance()->setCursor(QCursor(Qt::BlankCursor));
		*iEventHistory = event->pos();
		*iCursorHistory = QCursor::pos();
	}
}

void CPlanarWorkspace::mouseMoveEvent(QMouseEvent *event){
	int mouseAfterMovePositionX = event->x();
	int mouseAfterMovePositionY = event->y();
	QCursor::setPos(*iCursorHistory);
	if(UserManipulatingSlice == SliceOrientation::z){
		int dx = mouseAfterMovePositionX - iEventHistory->x();
		int dy = iEventHistory->y() - mouseAfterMovePositionY;
		if ((iPlanarCrossPosition.x+(float)dx/(float)iSensitivity>0.) && (iPlanarCrossPosition.x+(float)dx/(float)iSensitivity<1.))
			iPlanarCrossPosition.x=iPlanarCrossPosition.x+(float)dx/(float)iSensitivity;
		if ((iPlanarCrossPosition.y+(float)dy/(float)iSensitivity>0.) && (iPlanarCrossPosition.y+(float)dy/(float)iSensitivity<1.))
			iPlanarCrossPosition.y=iPlanarCrossPosition.y+(float)dy/(float)iSensitivity;
	}
	if(UserManipulatingSlice == SliceOrientation::x){
		int dx = iEventHistory->x() - mouseAfterMovePositionX;
		int dy = iEventHistory->y() - mouseAfterMovePositionY;
		if ((iPlanarCrossPosition.y+(float)dy/(float)iSensitivity>0.) && (iPlanarCrossPosition.y+(float)dy/(float)iSensitivity<1.))
			iPlanarCrossPosition.z=iPlanarCrossPosition.z+(float)dy/(float)iSensitivity;
		if ((iPlanarCrossPosition.z+(float)dx/(float)iSensitivity>0.) && (iPlanarCrossPosition.z+(float)dx/(float)iSensitivity<1.))
			iPlanarCrossPosition.y=iPlanarCrossPosition.y+(float)dx/(float)iSensitivity;
	}
	if(UserManipulatingSlice == SliceOrientation::y){
		int dx = mouseAfterMovePositionX - iEventHistory->x();
		int dy = iEventHistory->y() - mouseAfterMovePositionY;
		if ((iPlanarCrossPosition.x+(float)dx/(float)iSensitivity>0.) && (iPlanarCrossPosition.x+(float)dx/(float)iSensitivity<1.))
			iPlanarCrossPosition.x=iPlanarCrossPosition.x+(float)dx/(float)iSensitivity;
		if ((iPlanarCrossPosition.z+(float)dy/(float)iSensitivity>0.) && (iPlanarCrossPosition.z+(float)dy/(float)iSensitivity<1.))
			iPlanarCrossPosition.z=iPlanarCrossPosition.z+(float)dy/(float)iSensitivity;
	}
	CWidget::GetInstance()->updateGL();
}

void CPlanarWorkspace::mouseReleaseEvent(QMouseEvent *event){
	CWidget::GetInstance()->unsetCursor();
}
