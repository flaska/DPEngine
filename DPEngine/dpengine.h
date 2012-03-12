#ifndef DPENGINE_H
#define DPENGINE_H

#include <QtGui/QMainWindow>
#include "ui_dpengine.h"

class DPEngine : public QMainWindow
{
	Q_OBJECT

public:
	DPEngine(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DPEngine();

private:
	Ui::DPEngineClass ui;
};

#endif // DPENGINE_H
