#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "xraywindow.h"
#include "imagewindow.h"
#include <QScreen>
#include <QRect>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    Preferences::load();

    QRect rec = QApplication::desktop()->screenGeometry();
    const int SCREEN_WIDTH = rec.width();
    const int SCREEN_HEIGHT = rec.height();
    const QSize DEFAULT_MAIN_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/4 );

    MainWindow w;
	w.show();
    w.resize(DEFAULT_MAIN_WINDOW_SIZE);
    // w.setFixedSize(DEFAULT_MAIN_WINDOW_SIZE);
    w.move(0, 0);


	return a.exec();
}
