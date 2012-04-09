#include <cobject.h>
#include <cwidget.h>
#include <settings.h>


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
	iMoveIcon.size.setX(Settings::iconSize);
	iMoveIcon.size.setY(Settings::iconSize);

	iResizeIcon.size.setX(Settings::iconSize);
	iResizeIcon.size.setY(Settings::iconSize);
	iResizeIcon.position.setX(iSize.x()-iResizeIcon.size.x()-GetBorders().right);
	iResizeIcon.position.setY(iSize.y()-iResizeIcon.size.y()-GetBorders().bottom);

	iCloseIcon.size.setX(Settings::iconSize);
	iCloseIcon.size.setY(Settings::iconSize);
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
	iMoveIcon.size.setX(Settings::iconSize);
	iMoveIcon.size.setY(Settings::iconSize);

	iResizeIcon.size.setX(Settings::iconSize);
	iResizeIcon.size.setY(Settings::iconSize);
	iResizeIcon.position.setX(iSize.x()-iResizeIcon.size.x());
	iResizeIcon.position.setY(iSize.y()-iResizeIcon.size.y());

	iCloseIcon.size.setX(Settings::iconSize);
	iCloseIcon.size.setY(Settings::iconSize);
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
	const QRect& r =GetInnerRect();
	int rheight=r.height();
	int rtop=r.top();
	int bottom = iSize.y()-r.height()-r.top();
	int right = r.left()+r.width();
	int top = iSize.y()-r.top();
	//painter->setPen(QPen(QColor(0,0,0)));
	QPointF position = GetPosition();
	QPointF size = GetSize();
	painter->fillRect(QRect(position.toPoint(),QSize(size.x(),size.y())),Qt::black);
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
	if(iMoveAbility )
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iMoveIcon.position.x()+GetPosition().x(),iMoveIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(iMoveIcon.size.x(),iMoveIcon.size.y())));
		painter->drawImage(QRect(position,QSize(iMoveIcon.size.x(),iMoveIcon.size.y())),*CWidget::GetInstance()->getIcon(TIconType::MoveIcon));

	}
	//Resize icon
	if(iResizeAbility )
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iResizeIcon.position.x()+GetPosition().x(),iResizeIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(iResizeIcon.size.x(),iResizeIcon.size.y())));
		painter->drawImage(QRect(position,QSize(iMoveIcon.size.x(),iMoveIcon.size.y())),*CWidget::GetInstance()->getIcon(TIconType::ResizeIcon));
		
	}
	//Close icon
	if(iCloseAbility)
	{
		painter->setPen(QPen(QColor(255,0,0)));
		QPoint position(iCloseIcon.position.x()+GetPosition().x(),iCloseIcon.position.y()+GetPosition().y());
		painter->drawRect(QRect(position,QSize(iCloseIcon.size.x(),iCloseIcon.size.y())));
		painter->drawImage(QRect(position,QSize(iMoveIcon.size.x(),iMoveIcon.size.y())),*CWidget::GetInstance()->getIcon(TIconType::CloseIcon));
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

		std::cout << "Resize Icon Real Position LT: x" << iResizeIcon.position.x() + iPosition.x()<< " y " << iResizeIcon.position.y() + iPosition.y() << std::endl;
		std::cout << "Resize Icon Real Position RB: x" << iResizeIcon.position.x()+iResizeIcon.size.x() + iPosition.x()<< " y " << iResizeIcon.position.y()+iResizeIcon.size.y() + iPosition.y()<< std::endl;
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

void CObject::DrawSelection(QPainter* painter)
{
	QPen pen(Qt::green, (GetBorders().bottom+GetBorders().left+GetBorders().right+GetBorders().top)/4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
	painter->setPen(pen);
	painter->drawRect(QRect(QPoint(GetPosition().x()+GetBorders().left/2,GetPosition().y()+GetBorders().top/2),QPoint(GetPosition().x()+GetSize().x()-GetBorders().right/2,GetPosition().y()+GetSize().y()-GetBorders().bottom/2)));
}
void CObject::DrawBorderRect(QPainter* painter)
{
	QPen pen(Qt::gray, (GetBorders().bottom+GetBorders().left+GetBorders().right+GetBorders().top)/4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
	painter->setPen(pen);
	painter->drawRect(QRect(QPoint(GetPosition().x()+GetBorders().left/2,GetPosition().y()+GetBorders().top/2),QPoint(GetPosition().x()+GetSize().x()-GetBorders().right/2,GetPosition().y()+GetSize().y()-GetBorders().bottom/2)));
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


