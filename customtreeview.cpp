#include <QTreeView>
#include <QKeyEvent>
#include <iostream>
using namespace std;

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomTreeView() {}
    virtual ~CustomTreeView() {}

private:
    void keyPressEvent(QKeyEvent *event){
        switch(event->key()){
        case Qt::Key_Left:
            cout << "left" << endl;
            break;
        case Qt::Key_Up:
            cout << "up" << endl;
            break;
        case Qt::Key_Right:
        	cout << "right" << endl;
            break;
        case Qt::Key_Down:
        	cout << "down" << endl;
            break;
        default:
            cout << "pressed" << endl;
            keyPressEvent(event);
        	break;
        }
	}
};
