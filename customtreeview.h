#include <QTreeView>
#include <QKeyEvent>
#include <iostream>
#include <QFileSystemModel>
#include "mainwindow.h"
using namespace std;

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomTreeView(QWidget *_parent = 0) : QTreeView(_parent){
    }
    virtual ~CustomTreeView(){}

signals:
    void zKeyPressedSignal(QString);
    void xKeyPressedSignal(QString);


private:
    QList<QModelIndex> selectedIdxList;

    QFileSystemModel model;

    void keyPressEvent(QKeyEvent *event){

        selectedIdxList = this->selectedIndexes();

        switch(event->key()){
        case Qt::Key_Left:
            cout << "left" << endl;
            QTreeView::keyPressEvent(event);
            break;

        case Qt::Key_Up:
            cout << "up" << endl;
            QTreeView::keyPressEvent(event);
            break;

        case Qt::Key_Right:
            cout << "right" << endl;
            QTreeView::keyPressEvent(event);
            break;

        case Qt::Key_Down:
            cout << "down" << endl;
            QTreeView::keyPressEvent(event);
            break;

        case Qt::Key_Z:
            cout << "z" << endl;
            emit zKeyPressedSignal( model.filePath(selectedIdxList.at(0)) );
            break;

        case Qt::Key_X:
            cout << "x" << endl;
            emit xKeyPressedSignal( model.filePath(selectedIdxList.at(0)) );
            break;

        default:
            cout << "pressed" << endl;
            QTreeView::keyPressEvent(event);
            break;
        }
    }
};
