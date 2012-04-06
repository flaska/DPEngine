#include <cobject.h>
#include <cwidget.h>


void CObject::SetGeometry(float x, float y, float width, float height)
{
	iPosition.setX(x);
	iPosition.setY(y);
	iSize.setX (width);
	iSize.setY (height);
	resizeObject();
}
void CObject::resizeObject()
{
	iMoveIcon.position.setX(GetBorders().left);
	iMoveIcon.position.setY(GetBorders().top);
	iMoveIcon.size.setX(50);
	iMoveIcon.size.setY(50);

	iResizeIcon.size.setX(50);
	iResizeIcon.size.setY(50);
	iResizeIcon.position.setX(iSize.x()-iResizeIcon.size.x()-GetBorders().right);
	iResizeIcon.position.setY(iSize.y()-iResizeIcon.size.y()-GetBorders().bottom);

	iCloseIcon.size.setX(50);
	iCloseIcon.size.setY(50);
	iCloseIcon.position.setX(iSize.x()-iCloseIcon.size.x()-GetBorders().right);
	iCloseIcon.position.setY(0+GetBorders().bottom);
}
CObject::CObject(CObject *parentWindow, const QPointF& position, const QPointF &size ):iParentWindow(parentWindow ),iPosition(position ),iSize(size)
{	
	iBorders.left=0;
	iBorders.top=0;
	iBorders.right=0;
	iBorders.bottom=0;
	
	iMoveIcon.position.setX(0);
	iMoveIcon.position.setY(0);
	iMoveIcon.size.setX(50);
	iMoveIcon.size.setY(50);

	iResizeIcon.size.setX(50);
	iResizeIcon.size.setY(50);
	iResizeIcon.position.setX(iSize.x()-iResizeIcon.size.x());
	iResizeIcon.position.setY(iSize.y()-iResizeIcon.size.y());

	iCloseIcon.size.setX(50);
	iCloseIcon.size.setY(50);
	iCloseIcon.position.setX(iSize.x()-iCloseIcon.size.x());
	iCloseIcon.position.setY(0);
}

CObject::CObject()
{	
	iParentWindow = NULL;
}

/* TODO
void CObject::resizeGL()
{
	iMoveIcon.position.setX(GetBorders().left);
	iMoveIcon.position.setY(GetBorders().top);
	iMoveIcon.size.setX(20);
	iMoveIcon.size.setY(20);

	iResizeIcon.size.setX(20);
	iResizeIcon.size.setY(20);
	iResizeIcon.position.setX(iSize.x()-iResizeIcon.size.x()-GetBorders().right);
	iResizeIcon.position.setY(iSize.y()-iResizeIcon.size.y()-GetBorders().bottom);

	iCloseIcon.size.setX(20);
	iCloseIcon.size.setY(20);
	iCloseIcon.position.setX(iSize.x()-iCloseIcon.size.x()-GetBorders().right);
	iCloseIcon.position.setY(0+GetBorders().bottom);
}
*/

void CObject::DrawInnerRect(QPainter* painter)
{

	//glColor4f(iInnerColor.r,iInnerColor.g,iInnerColor.b,iInnerColor.a);
	const QRect& r =GetInnerRect();
	int rheight=r.height();
	int rtop=r.top();
	int bottom = iSize.y()-r.height()-r.top();
	int right = r.left()+r.width();
	int top = iSize.y()-r.top();
	painter->setPen(QPen(QColor(255,0,0)));

	QPointF position = GetPosition();
	QPointF size = GetSize();
	painter->drawRect(QRect(position.toPoint(),QSize(size.x(),size.y())));
}
void CObject::SetInnerColor(TColor color)
{
	iInnerColor=color;
}
void CObject::SetInnerColor(float r, float g, float b, float alpha)
{
	iInnerColor.r=r;
	iInnerColor.g=g;
	iInnerColor.b=b;
	iInnerColor.a=alpha;
}
TColor CObject::GetInnerColor()
{
	return iInnerColor;
}



void CObject::DrawIcons(QPainter* painter){
	float opaq = 0.5;
	if(iMoveAbility  )
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iMoveIcon.position.x()+GetPosition().x(),iMoveIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(30,30)));

	}
	//Resize icon
	if(iResizeAbility )
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iResizeIcon.position.x()+GetPosition().x(),iResizeIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(30,30)));
		
	}
	//Close icon
	if(iCloseAbility)
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iCloseIcon.position.x()+GetPosition().x(),iCloseIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(30,30)));
	}
}

void CObject::SetSize(const QPointF &size)
{
	//iSize=size;
	SetGeometry(iPosition.x(),iPosition.y(),size.x(),size.y());
}
void CObject::SetPosition(const QPointF &position)
{
	//iPosition=position;
	SetGeometry(position.x(),position.y(),
		iSize.x(),iSize.y());
}
bool CObject::IsOnCloseIcon(int x, int y)
{

	if(!iCloseAbility  )return false;

	if(x<iCloseIcon.position.x())
		return false;
	if(y<iCloseIcon.position.y())
		return false;
	if(x>(iCloseIcon.position.x()+iCloseIcon.size.x()))
		return false;
	if(y>(iCloseIcon.position.y()+iCloseIcon.size.y()))
		return false;
	return true;
}

bool CObject::IsOnResizeIcon(int x, int y)
{
	if(!iResizeAbility  )return false;

	if(x<iResizeIcon.position.x())
		return false;
	if(y<iResizeIcon.position.y())
		return false;
	if(x>(iResizeIcon.position.x()+iResizeIcon.size.x()))
		return false;
	if(y>(iResizeIcon.position.y()+iResizeIcon.size.y()))
		return false;
	return true;
}

void CObject::SetMoveability(bool on)
{
	iMoveAbility = on;
}
void CObject::SetClosability(bool on){
	iCloseAbility = on;
}
void CObject::SetResizeability(bool on)
{
	iResizeAbility = on;
}
bool CObject::IsOnMoveIcon(int x, int y)
{
	if(!iMoveAbility )return false;
	if(x<iMoveIcon.position.x())
		return false;
	if(y<iMoveIcon.position.y())
		return false;
	if(x>(iMoveIcon.position.x()+iMoveIcon.size.x()))
		return false;
	if(y>(iMoveIcon.position.y()+iMoveIcon.size.y()))
		return false;
	return true;
}

void CObject::DrawSelection()
{
/*	glDisable(GL_BLEND);
	glColor4f(0.5,1,1,1);
	glRectf(0,0,
		GetBorders().left,
		GetSize().y());
	glRectf(0,0,
		GetSize().x(),
		GetBorders().bottom);

	glRectf(GetSize().x()-GetBorders().right,
		0,
		GetSize().x(),
		GetSize().y());
	
	glRectf(0,
		GetSize().y()-GetBorders().top,
		GetSize().x(),
		GetSize().y());

	glColor4f(0.9,0.9,0.9,1);
	glRectf(0,0,
		1,
		GetSize().y());
	glRectf(0,0,
		GetSize().x(),
		1);

	glRectf(GetSize().x()-1,
		0,
		GetSize().x(),
		GetSize().y());
	
	glRectf(0,
		GetSize().y()-1,
		GetSize().x(),
		GetSize().y());
	glEnable(GL_BLEND);*/
	/*
	glEnable(GL_BLEND);
	glColor4f(0.5,1,1,0.1);
	glRectf(GetBorders().left,GetBorders().bottom
		,
		GetSize().x()-GetBorders().right,
		GetSize().y()-GetBorders().top);
	glDisable(GL_BLEND);
	*/
}
void CObject::DrawBorderRect()
{
	// nahrat jednotkovou matici

	//glColor4f(iBorderColor.r,iBorderColor.g,iBorderColor.b,iBorderColor.a);
	//glRectf(0,0,iSize.x(),iSize.y());
	/*	glBegin(GL_LINES);
	glVertex2i(0,0);
	glVertex2i(iSize.x(),0);
	glVertex2i(0,1);
	glVertex2i(iSize.x(),1);


	glVertex2i(iSize.x(),0);
	glVertex2i(iSize.x(),iSize.y()-1);
	glVertex2i(iSize.x()-1,0);
	glVertex2i(iSize.x()-1,iSize.y()-1);

	glVertex2i(iSize.x(),iSize.y()-1);
	glVertex2i(0,iSize.y()-1);
	glVertex2i(iSize.x(),iSize.y()-2);
	glVertex2i(0,iSize.y()-2);

	glVertex2i(0,iSize.y()-1);
	glVertex2i(0,0);
	glVertex2i(1,iSize.y()-1);
	glVertex2i(1,0);
	glEnd();
	*/
}

//set matrix to start position of object
void CObject::Translate()
{
	if(iParentWindow==NULL)
		return;
	//glMatrixMode(GL_MODELVIEW);                 // bude se menit modelova matice
	//glLoadIdentity();   
	int posy=CWidget::GetInstance()->height();
	//glTranslatef(iPosition.x(),posy-iPosition.y()-iSize.y(), -50.0f); 
}


void CObject::SetBorderColor(TColor color)
{
	iBorderColor=color;

}
void CObject::SetBorderColor(float r, float g, float b, float alpha)
{
	iBorderColor.r=r;
	iBorderColor.g=g;
	iBorderColor.b=b;
	iBorderColor.a=alpha;
}

void CObject::SetBorders(TBorders border)
{
	iBorders.left = border.left;
	iBorders.top = border.top;
	iBorders.right = border.right;
	iBorders.bottom = border.bottom;
}

const QPointF &CObject::GetPosition()
{
	return iPosition;
}
const QPointF &CObject::GetSize()
{

	return iSize;
}

const QRect CObject::GetInnerRect()
{
	return QRect(
		iBorders.left,
		iBorders.top,
		iSize.x()-iBorders.right-iBorders.left,
		iSize.y()-iBorders.bottom-iBorders.top
		);
}
const int CObject::height()
{
	return iSize.y();
}
const int CObject::width()
{
	return iSize.x();
}

bool CObject::IsPointOnObject(int x, int y)
{
	if(x<iPosition.x())
		return false;
	if(y<iPosition.y())
		return false;
	if(x>(iPosition.x()+iSize.x()))
		return false;
	if(y>(iPosition.y()+iSize.y()))
		return false;
	return true;

}


