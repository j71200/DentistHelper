#include <QTreeView>
#include <QKeyEvent>
#include <iostream>
#include <QFileSystemModel>
using namespace std;

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomTreeView(QWidget *parent = 0) : QTreeView(parent){
    }
    virtual ~CustomTreeView(){}

private:
    QList<QModelIndex> selectedIdxList;
    QFileSystemModel model;

    void keyPressEvent(QKeyEvent *event){
        switch(event->key()){
        case Qt::Key_Left:


            // selectedIdxList = this->selectedIndexes();
            // for(int i=0; i<selectedIdxList.size(); i++){
            //     cout << "selectedIdxList(" << i << "): " << model.filePath(selectedIdxList.at(i)).toStdString() << endl;
            // }

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
        default:
            cout << "pressed" << endl;
            QTreeView::keyPressEvent(event);
        	break;
        }
	}
};
