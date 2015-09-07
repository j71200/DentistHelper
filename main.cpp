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

    // cout << "SCREEN_WIDTH " << SCREEN_WIDTH << endl;
    // cout << "SCREEN_HEIGHT " << SCREEN_HEIGHT << endl;



    const QSize DEFAULT_XRAY_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 );
    const QSize DEFAULT_IMAGE_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 );
    const QSize DEFAULT_MAIN_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT );



    XRayWindow x;
    x.show();
    x.resize(DEFAULT_XRAY_WINDOW_SIZE);
    // x.setFixedSize(DEFAULT_XRAY_WINDOW_SIZE);
    x.move(SCREEN_WIDTH/2 + 1, 0);
    

    ImageWindow i;
    i.show();
    i.resize(DEFAULT_IMAGE_WINDOW_SIZE);
    // i.setFixedSize(DEFAULT_IMAGE_WINDOW_SIZE);
    i.move(SCREEN_WIDTH/2 + 1, DEFAULT_XRAY_WINDOW_SIZE.height() + 1);


    MainWindow w;
	w.show();
    w.resize(DEFAULT_MAIN_WINDOW_SIZE);
    // w.setFixedSize(DEFAULT_MAIN_WINDOW_SIZE);
    w.move(0, 0);



	return a.exec();
}
