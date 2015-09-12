#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>

class CustomScrollArea : public QScrollArea{

	Q_OBJECT

public:
	CustomScrollArea(QWidget *parent = 0) : QScrollArea(parent){}
    virtual ~CustomScrollArea(){}

signals:
	void doubleClickeScrollAreaSignal();

protected:
	void mouseDoubleClickEvent(QMouseEvent * event){
		emit doubleClickeScrollAreaSignal();
	}


};

#endif // CUSTOMSCROLLAREA_H

