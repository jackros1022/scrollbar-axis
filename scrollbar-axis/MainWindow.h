#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "qcustomplot.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	void setupPlot();
	private slots:
	void horzScrollBarChanged(int value);
	void vertScrollBarChanged(int value);
	void xAxisChanged(QCPRange range);
	void yAxisChanged(QCPRange range);
private:
	Ui::MainWindowClass ui;
};
