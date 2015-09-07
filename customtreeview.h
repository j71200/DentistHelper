#ifndef CUSTOMTREEVIEW
#define CUSTOMTREEVIEW

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
    // void zKeyPressedSignal(QString);
    // void xKeyPressedSignal(QString);
    void fileChangedSignal(QString);


protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
        selectedIdxList = this->selectedIndexes();
        
        if( (selectedIdxList.size() > 0) && (!model.isDir(selectedIdxList.at(0))) ){
            selectedFilePath = model.filePath(selectedIdxList.at(0));
            emit fileChangedSignal(selectedFilePath);
        }

        QTreeView::selectionChanged(selected, deselected);
    }

private:
    QList<QModelIndex> selectedIdxList;
    QString selectedFilePath;
    QFileSystemModel model;
};

// void keyPressEvent(QKeyEvent *event){
//     switch(event->key()){
//     case Qt::Key_Z:
//         if(selectedIdxList.size() > 0){
//             selectedFilePath = model.filePath(selectedIdxList.at(0));
//             emit zKeyPressedSignal( selectedFilePath );
//         }
//         break;

//     case Qt::Key_X:
//         if(selectedIdxList.size() > 0){
//             selectedFilePath = model.filePath(selectedIdxList.at(0));
//             emit xKeyPressedSignal( selectedFilePath );
//         }
//         break;

//     default:
//         QTreeView::keyPressEvent(event);
//         break;
//     }
// }


#endif // CUSTOMTREEVIEW

