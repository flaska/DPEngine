#include <QtGui/QtGui>
#include <cobject.h>
class CImageExplorer;
class CWidget : public QLabel, public CObject {
//	Q_OBJECT 
public:
	CWidget(QWidget *parent);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paint();
	static CWidget *GetInstance();
	static CWidget* InitInstance(QWidget *parent);
	const int width();
	const int height();
	QPixmap* getWidgetImage();
//private:
	QPixmap* iPixmap;
	static CWidget *instance;
	CObject *iActiveObject;
	CImageExplorer* iImageExplorer;
};
