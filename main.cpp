#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}


//#include <QApplication>
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QGraphicsPixmapItem>

//int main(int argc, char *argv[])
//{
//	QApplication a(argc, argv);

//	QGraphicsScene scene;
//	QGraphicsView view(&scene);
////	QPixmap aa("/Users/blue/Pictures/lena.gif");
//	QPixmap aa;
//	QSize ss(10, 500);
//	aa = QPixmap("/Users/blue/Pictures/lena.gif").scaled(ss);
//	QGraphicsPixmapItem item(aa);
//	scene.addItem(&item);
//	view.show();

//	return a.exec();
//}
