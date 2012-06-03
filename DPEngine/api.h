#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QTextStream>
#include <QtGui/QtGui>
#include <QtXml/qdom.h>
#include <QtCore/QObject>
#include <windows.h>

#define FUNCMAX 10
typedef bool mainFunction();
typedef bool intFunction(int);
typedef bool doubleFunction(double);
typedef bool charFunction(char);

enum buttonType { noButton, leftButton, rightButton };

class drawLabel : public QLabel {
	Q_OBJECT
public:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	drawLabel();
	QPixmap *iMemoryPixmap;
	QPixmap *iDrawPixmap;
private:
	buttonType pressedButton;
};

class libraryLoader : public QObject {
	Q_OBJECT
public:
	~libraryLoader();
	libraryLoader();
	void init();
private:
	int intFuncMax;
	int doubleFuncMax;
	int charFuncMax;
	QString libraryFilename;
	QString mainFunctionName;
	HINSTANCE LoadedLibrary;
	FARPROC ProcessAdress;
	QWidget *window;
	QGridLayout *Layout;
	QFile *file;
	QTextStream *in;
	intFunction* intFunctionTable[FUNCMAX];
	doubleFunction* doubleFunctionTable[FUNCMAX];
	mainFunction* mainFunctionTable[FUNCMAX];
	charFunction* charFunctionTable[FUNCMAX];
	QWidget* intControlTable[FUNCMAX];
	QWidget* doubleControlTable[FUNCMAX];
	QWidget* charControlTable[FUNCMAX];
	void initRun();
	void setUi();
	void setDrawingUnit();
	drawLabel *iDrawImageLabel;
public slots:
	void backToMain();
	void reset();
	int intHandler(int,int);
	int mainHandler(int);
	int charHandler(int,int);
};
/*
class mapSpinBox : public QSpinBox {
	Q_OBJECT
public:
	mapSpinBox::mapSpinBox(int);
private:
	int id;

}*/

class intTransfer : public QObject {
	Q_OBJECT
public:
	intTransfer(int);
private:
	int id;
public slots:
	void getValue(int);
signals:
	void emitValue(int,int);
};

class doubleTransfer : public QObject {
	Q_OBJECT
public:
	doubleTransfer(int);
private:
	int id;
public slots:
	void getValue(double);
signals:
	void emitValue(int,double);
};

class charTransfer : public QObject {
	Q_OBJECT
public:
	charTransfer(int);
private:
	int id;
public slots:
	void getValue(int);
signals:
	void emitValue(int,int);
};

class mainTransfer : public QObject {
	Q_OBJECT
public:
	mainTransfer(int);
private:
	int id;
public slots:
	void getPress();
signals:
	void emitPress(int);
};