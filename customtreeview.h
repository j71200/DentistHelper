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
    void fileChangedSignal(QString);
    void tvSpacePressedSignal();


protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
        selectedIdxList = this->selectedIndexes();
        
        if( (selectedIdxList.size() > 0) && (!model.isDir(selectedIdxList.at(0))) ){
            selectedFilePath = model.filePath(selectedIdxList.at(0));
            emit fileChangedSignal(selectedFilePath);
        }

        QTreeView::selectionChanged(selected, deselected);
    }

    void keyPressEvent(QKeyEvent *event){
        switch(event->key()){
        case Qt::Key_Space:
            emit tvSpacePressedSignal();
            break;

        default:
            QTreeView::keyPressEvent(event);
            break;
    }
}

private:
    QList<QModelIndex> selectedIdxList;
    QString selectedFilePath;
    QFileSystemModel model;
};

#endif // CUSTOMTREEVIEW

