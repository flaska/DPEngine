#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QTextStream>
#include <QtGui/QtGui>
#include <QtXml/qdom.h>
#include <QtGui/QProgressDialog>
#include <iostream>
#include <windows.h>
#include <cimageexplorer.h>

#include "api.h"

libraryLoader::libraryLoader(){

}

libraryLoader::~libraryLoader(){
	FreeLibrary(LoadedLibrary);
}

void libraryLoader::init(){
	libraryFilename="LouckyDLL.dll"; 
	LoadedLibrary = LoadLibrary(TEXT("LouckyDLL.dll"));
	Layout=new QGridLayout();
	QPushButton* reset = new QPushButton("Reset");
	connect(reset,SIGNAL(pressed()),this,SLOT(reset()));

	Layout->addWidget(reset,0,3);



	//Layout->setColumnStretch(1,10);
	file = new QFile("gui.ini");	
	file->open(QIODevice::ReadOnly | QIODevice::Text);
    in = new QTextStream(file);
	window = new QWidget();
	setUi();
	setDrawingUnit();
	QGridLayout* CompleteLayout=new QGridLayout();
	CompleteLayout->addWidget(window,1,0);
	CompleteLayout->addWidget(iDrawImageLabel,0,0);
	QWidget* completeWidget = new QWidget();
	completeWidget->setLayout(CompleteLayout);
	completeWidget->show();
}

void libraryLoader::setDrawingUnit(){
	iDrawImageLabel = new drawLabel();
	iDrawImageLabel->setMouseTracking(true);
	//iDrawImageLabel->show();
}


void libraryLoader::setUi(){
	QString data=in->readAll();
	QDomDocument doc("myDocument");
	QFile file("gui.ini");

	if (file.size()<10) return;
	doc.setContent(&file);                

	QDomElement docElement = doc.documentElement();
	QDomNode node;

	node = docElement.firstChild();
	int y=0;
	int i=0;
	int d=0;
	int m=0;
	int c=0;
	while (!node.isNull())  {
		if (node.isElement())  {
			QDomElement e = node.toElement();
			QString tag= e.tagName();	
			QString type = e.attribute("type");
			if (type=="int"||type=="double"){
				if (e.hasAttribute("function")){
					QString functionName = e.attribute("function");
					ProcessAdress = GetProcAddress(LoadedLibrary,functionName.toStdString().c_str());
					if (type=="int") intFunctionTable[i] = (intFunction*)ProcessAdress;
					if (type=="double") doubleFunctionTable[d] = (doubleFunction*)ProcessAdress;
				}
				if (e.hasAttribute("name")){
					QLabel *label = new QLabel(e.attribute("name"));
					//Layout->addWidget(label,y,0);
					Layout->addWidget(label,1,y);
				}
				if (tag=="numinput") {
					QSpinBox *spinbox = new QSpinBox();
					if (e.hasAttribute("min")&&e.hasAttribute("max")){
						int min= QString(e.attribute("min")).toInt();
						int max= QString(e.attribute("max")).toInt();				
						spinbox->setMinimum (min);
						spinbox->setMaximum (max);
						if (type=="int") intControlTable[i]=dynamic_cast<QWidget*>(spinbox); 
						if (type=="double") doubleControlTable[d]=dynamic_cast<QWidget*>(spinbox); 
					}
					//Layout->addWidget(spinbox,y,1);
					Layout->addWidget(spinbox,2,y);
					if (type=="int"){
						intTransfer* tr = new intTransfer(i);
						connect(spinbox,SIGNAL(valueChanged(int)),tr,SLOT(getValue(int)));
						connect(tr,SIGNAL(emitValue(int,int)),this,SLOT(intHandler(int,int)));
					}
					if (type=="double"){
						doubleTransfer* dt = new doubleTransfer(d);
						connect(spinbox,SIGNAL(valueChanged(int)),dt,SLOT(getValue(int)));
						connect(dt,SIGNAL(emitValue(int,int)),this,SLOT(doubleHandler(int,int)));
					}
					if (e.hasAttribute("default")){
						int defval=QString(e.attribute("default")).toInt();
						spinbox->setValue(defval);
					}
				}
				if (tag=="combobox"){
					QComboBox *combobox = new QComboBox();
					if (e.hasChildNodes()){
						QDomNodeList childs=e.childNodes();
						for (int k=0; k<childs.count(); k++){
							QDomNode n = childs.at(k);
							QDomElement el = n.toElement();
							QString value = el.attribute("value");
							combobox->addItem(el.attribute("name"),el.attribute("value"));
						}					
					}
					intControlTable[i]=dynamic_cast<QWidget*>(combobox); 
					//Layout->addWidget(combobox,y,1);
					Layout->addWidget(combobox,2,y);
					intTransfer* tr = new intTransfer(i);
					connect(combobox,SIGNAL(valueChanged(int)),tr,SLOT(getValue(int)));
					connect(tr,SIGNAL(emitValue(int,int)),this,SLOT(intHandler(int,int)));
				}					
				if (type=="int") i++;
				if (type=="double") d++;
			}
			if (type=="char"){
				if (e.hasAttribute("function")){
					QString functionName = e.attribute("function");
					ProcessAdress = GetProcAddress(LoadedLibrary,functionName.toStdString().c_str());
					charFunctionTable[c] = (charFunction*)ProcessAdress;
				}		
				if (e.hasAttribute("name")){
					QLabel *label = new QLabel(e.attribute("name"));
					//Layout->addWidget(label,y,0);
					Layout->addWidget(label,1,y);
				}
				if (tag=="combobox"){
					QComboBox *combobox = new QComboBox();
					if (e.hasChildNodes()){
						QDomNodeList childs=e.childNodes();
						for (int k=0; k<childs.count(); k++){
							QDomNode n = childs.at(k);
							QDomElement el = n.toElement();
							QString value = el.attribute("value");
							combobox->addItem(el.attribute("name"),el.attribute("value"));
						}					
					}
					charControlTable[c]=dynamic_cast<QWidget*>(combobox); 
					//Layout->addWidget(combobox,y,1);
					Layout->addWidget(combobox,2,y);
					charTransfer* ct = new charTransfer(c);
					connect(combobox,SIGNAL(activated(int)),ct,SLOT(getValue(int)));
					connect(ct,SIGNAL(emitValue(int,int)),this,SLOT(charHandler(int,int)));
				}
				c++;
			}
			if (tag=="button"){
				if (e.hasAttribute("function")){
					QString functionName = e.attribute("function");
					ProcessAdress = GetProcAddress(LoadedLibrary,functionName.toStdString().c_str());
					mainFunctionTable[m] = (mainFunction*)ProcessAdress;
				}		
				QPushButton *mainButton = new QPushButton(e.attribute("name").toStdString().c_str());
				//Layout->addWidget(mainButton,y,1);
				Layout->addWidget(mainButton,2,y);
				mainTransfer* mt = new mainTransfer(m);
				connect(mainButton,SIGNAL(pressed()),mt,SLOT(getPress()));
				connect(mt,SIGNAL(emitPress(int)),this,SLOT(mainHandler(int)));
				m++;
			}
			node = node.nextSibling();
			y++;
		}
	}
	intFuncMax=i-1;
	doubleFuncMax=d-1;
	charFuncMax=c-1;
	window->setFixedSize(512,100);
	//window->show();
	window->setLayout(Layout);
}

void libraryLoader::initRun(){
	//QWidget *loadingWindow = new QWidget();
	//loadingWindow->setFixedSize(100,100);
	//QLayout *layout=new QGridLayout();
	//QLabel *label = new QLabel("Loading..");
	//layout->addWidget(label);
	//loadingWindow->show();
	//loadingWindow->setLayout(layout);
	for (int i=0;i<=intFuncMax;i++) {
		intFunction* func=intFunctionTable[i];
		int val;
		if (dynamic_cast<QSpinBox*>(intControlTable[i])){
			QSpinBox* spin=dynamic_cast<QSpinBox*>(intControlTable[i]);
			val= spin->value();
		}
		if (dynamic_cast<QComboBox*>(intControlTable[i])){
			QComboBox* combo=dynamic_cast<QComboBox*>(intControlTable[i]);
			val=combo->itemData(combo->currentIndex()).toInt();
		}
		func(val);
	}
	for (int d=0;d<=doubleFuncMax;d++) {
		doubleFunction* func=doubleFunctionTable[d];
		int val;
		if (dynamic_cast<QSpinBox*>(doubleControlTable[d])){
			QSpinBox* spin=dynamic_cast<QSpinBox*>(doubleControlTable[d]);
			val= spin->value();
		}
		if (dynamic_cast<QComboBox*>(doubleControlTable[d])){
			QComboBox* combo=dynamic_cast<QComboBox*>(doubleControlTable[d]);
			val=combo->itemData(combo->currentIndex()).toInt();
		}
		func(val);
	}
	for (int c=0;c<=charFuncMax;c++) {
		charFunction* func=charFunctionTable[c];
		QString val;
		if (dynamic_cast<QComboBox*>(charControlTable[c])){
			QComboBox* combo=dynamic_cast<QComboBox*>(charControlTable[c]);
			val=combo->itemData(combo->currentIndex()).toString();
		}
		func(*val.toStdString().c_str());
	}
	QImage(iDrawImageLabel->iMemoryPixmap->toImage()).save("projekt-seed.pgm");
	//QImage(this->iDrawImageLabel->  ->toImage()).save("projekt-seed.pgm");
}

int libraryLoader::intHandler(int elemeintid, int iPar){
	intFunction* func=intFunctionTable[elemeintid];
	//func(iPar);
	return 0;
}

int libraryLoader::charHandler(int elemeintid, int cPar){
	charFunction* func=charFunctionTable[elemeintid];
	//func(cPar);
	return 0;
}

int libraryLoader::mainHandler(int elemeintid){

	initRun();
	mainFunction* func=mainFunctionTable[elemeintid];
	func();
	FreeLibrary(LoadedLibrary);
	QWidget* w = new QWidget();
	QGridLayout* ly=new QGridLayout();
	QPixmap *image = new QPixmap("projekt-seg.ppm","PPM");
	QLabel *imageLabel = new QLabel();
	imageLabel->setPixmap(*image);
	ly->addWidget(imageLabel,0,0);
	QPushButton *button = new QPushButton(QString("To Main Window"));
	ly->addWidget(button,1,0);
	w->setLayout(ly);
	w->show();
	connect(button,SIGNAL(pressed()),this,SLOT(backToMain()));
	//imageLabel->show();
	return 0;
}


void libraryLoader::backToMain(){
	system(QString("convert -separate projekt-seg.ppm projekt-seg.jpg").toAscii().data());
	system(QString("convert -define png:bit-depth=8 projekt-seg-2.jpg projekt-seg.png").toAscii().data());
	system(QString("convert projekt-seg.png projekt-seg.jpg").toAscii().data());
	system(QString("img2dcm projekt-seg.jpg IM-0001-0001.dcm").toAscii().data());
	CImageExplorer::GetInstance()->OpenImage(QString("IM-0001-0001.dcm"));
	remove("projekt-seg-0.jpg");
	remove("projekt-seg-1.jpg");
	remove("projekt-seg-2.jpg");
	remove("projekt-seg.png");
	remove("projekt-seg.jpg");
	remove("IM-0001-0001.dcm");
}


/*
window = new QWidget();
	setUi();
	setDrawingUnit();
	QGridLayout* CompleteLayout=new QGridLayout();
	CompleteLayout->addWidget(window,1,0);
	CompleteLayout->addWidget(iDrawImageLabel,0,0);
	QWidget* completeWidget = new QWidget();
	completeWidget->setLayout(CompleteLayout);
	completeWidget->show();


*/



intTransfer::intTransfer(int i){
	id = i;
}

void intTransfer::getValue(int val){
	emit emitValue(id,val);
}

doubleTransfer::doubleTransfer(int i){
	id = i;
}

void doubleTransfer::getValue(double val){
	emit emitValue(id,val);
}

charTransfer::charTransfer(int i){
	id = i;
}

void charTransfer::getValue(int ind){
	emit emitValue(id,ind);
}

mainTransfer::mainTransfer(int i){
	id = i;
}

void mainTransfer::getPress(){
	emit emitPress(id);
}

void drawLabel::mousePressEvent(QMouseEvent* event){
	if (event->button()==Qt::LeftButton) pressedButton = leftButton;
	if (event->button()==Qt::RightButton) pressedButton = rightButton;
}

void drawLabel::mouseMoveEvent(QMouseEvent* event){
	if (pressedButton==noButton) return;
	int x = event->x();
	int y = event->y();
	QColor visible;
	QColor invisible;
	if (pressedButton==rightButton){
		visible.setRgb(0,0,255);
		invisible.setRgb(255,255,255);
	}
	if (pressedButton==leftButton){
		visible.setRgb(255,0,0);
		invisible.setRgb(1,1,1);
	}
	QPainter painter((QPaintDevice*)pixmap());
	painter.setPen(QPen(visible, 5, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
	painter.drawEllipse (x,y,5,5);
	update();

	QPainter painter2((QPaintDevice*)iMemoryPixmap);
	painter2.setPen(QPen(invisible, 5, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
	painter2.drawEllipse (x,y,5,5);
}

void drawLabel::mouseReleaseEvent(QMouseEvent* event){
	pressedButton = noButton;
}

drawLabel::drawLabel(){
	iDrawPixmap = new QPixmap("projekt-data.pgm","PGM");
	
	QPainter painter;
	painter.begin((QPaintDevice*)iDrawPixmap);
	painter.setFont(QFont("Arial", 10));
	painter.setPen(Qt::red);
	painter.drawText(QPoint(10,30),QString("left mouse button - inner area"));
	painter.setPen(Qt::blue);
	painter.drawText(QPoint(10,45),QString("right mouse button - outer area"));
	painter.end();

	setPixmap(*iDrawPixmap);
	iMemoryPixmap = new QPixmap(QSize(iDrawPixmap->size().width(),iDrawPixmap->size().height()));
	iMemoryPixmap->fill(Qt::black);
	pressedButton = noButton;
	setFixedSize(iDrawPixmap->size().width(),iDrawPixmap->size().height());
}

void libraryLoader::reset(){
	iDrawImageLabel->iDrawPixmap->fill(Qt::black);
	iDrawImageLabel->iDrawPixmap->load("projekt-data.pgm","PGM");
	QPainter painter;
	painter.begin((QPaintDevice*)iDrawImageLabel->iDrawPixmap);
	painter.setFont(QFont("Arial", 10));
	painter.setPen(Qt::red);
	painter.drawText(QPoint(10,30),QString("left mouse button - inner area"));
	painter.setPen(Qt::blue);
	painter.drawText(QPoint(10,45),QString("right mouse button - outer area"));
	painter.end();
	iDrawImageLabel->setPixmap(*(iDrawImageLabel->iDrawPixmap));
	iDrawImageLabel->iMemoryPixmap->fill(Qt::black);
	iDrawImageLabel->update();
}