#include <QtGui/QtGui>
#include <cobject.h>
class CWidget : public QLabel, public CObject {
//	Q_OBJECT 
public:
	CWidget(QWidget *parent);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paint();
	static CWidget *GetInstance();
	static CWidget* InitInstance(QWidget *parent);
//private:
	QPixmap* iPixmap;
	static CWidget *instance;
	CObject *iActiveObject;
};
