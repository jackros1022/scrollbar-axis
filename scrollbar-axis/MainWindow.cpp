#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setupPlot();

	ui.horizontalScrollBar->setRange(-500,500);
	ui.verticalScrollBar->setRange(-500,500);

	connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
	connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
	connect(ui.plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
	connect(ui.plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

	ui.plot->xAxis->setRange(0, 6, Qt::AlignCenter);
	ui.plot->yAxis->setRange(0, 10, Qt::AlignCenter);
}

void MainWindow::setupPlot()
{
	// The following plot setup is mostly taken from the plot demos:
	ui.plot->addGraph();
	ui.plot->graph()->setPen(QPen(Qt::blue));
	ui.plot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
	ui.plot->addGraph();
	ui.plot->graph()->setPen(QPen(Qt::red));
	QVector<double> x(500), y0(500), y1(500);
	for (int i = 0; i<500; ++i)
	{
		x[i] = (i / 499.0 - 0.5) * 10;
		y0[i] = qExp(-x[i] * x[i] * 0.25)*qSin(x[i] * 5) * 5;
		y1[i] = qExp(-x[i] * x[i] * 0.25) * 5;
	}
	ui.plot->graph(0)->setData(x, y0);
	ui.plot->graph(1)->setData(x, y1);
	ui.plot->axisRect()->setupFullAxesBox(true);
	ui.plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::horzScrollBarChanged(int value)
{
	if (qAbs(ui.plot->xAxis->range().center() - value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		ui.plot->xAxis->setRange(value / 100.0, ui.plot->xAxis->range().size(), Qt::AlignCenter);
		ui.plot->replot();
	}
}

void MainWindow::vertScrollBarChanged(int value)
{
	if (qAbs(ui.plot->yAxis->range().center() + value / 100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
	{
		ui.plot->yAxis->setRange(-value / 100.0, ui.plot->yAxis->range().size(), Qt::AlignCenter);
		ui.plot->replot();
	}
}

void MainWindow::xAxisChanged(QCPRange range)
{
	ui.horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
	ui.horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void MainWindow::yAxisChanged(QCPRange range)
{
	ui.verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
	ui.verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}