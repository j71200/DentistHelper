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
    CustomTreeView(QWidget *_parent = 0) : QTreeView(_parent){}
    virtual ~CustomTreeView(){}

signals:
    void zKeyPressedSignal(QString);
    void xKeyPressedSignal(QString);

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
        selectedIdxList = this->selectedIndexes();
        if(selectedIdxList.size() > 0)
            selectedFilePath = model.filePath(selectedIdxList.at(0));

        QTreeView::selectionChanged(selected, deselected);
    }

private:
    QList<QModelIndex> selectedIdxList;
    QString selectedFilePath;
    QFileSystemModel model;

    void keyPressEvent(QKeyEvent *event){
        switch(event->key()){
        case Qt::Key_Z:
            // cout << "z" << endl;
            emit zKeyPressedSignal( model.filePath(selectedIdxList.at(0)) );
            break;

        case Qt::Key_X:
            // cout << "x" << endl;
            emit xKeyPressedSignal( model.filePath(selectedIdxList.at(0)) );
            break;

        default:
            // cout << "pressed" << endl;
            QTreeView::keyPressEvent(event);
            break;
        }
    }
};
