#include <QtGui/QApplication>
#include <QtGui/QtGui>

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	QImage *im = new QImage(250,250,QImage::Format_RGB16);

	QPainter p;
    p.begin((QPaintDevice*)im);
	p.setPen(QPen(QColor(100,100,100), 5, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    p.drawEllipse (10,10,50,50);        // drawing code
    p.end();

	QLabel *label = new QLabel();
	QPixmap *pix = new QPixmap(250,250);
	pix->convertFromImage(*im);

	label->setPixmap(*pix);
	label->show();

	return a.exec();
}