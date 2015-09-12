#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QTouchEvent>

class CustomScrollArea : public QScrollArea{

	Q_OBJECT

public:
    CustomScrollArea(QWidget *parent = 0) : QScrollArea(parent){
        this->setAttribute(Qt::WA_AcceptTouchEvents, true);
        this->viewport()->setAttribute(Qt::WA_AcceptTouchEvents, true);
    }
    virtual ~CustomScrollArea(){}

signals:
	void doubleClickeScrollAreaSignal();

protected:
	void mouseDoubleClickEvent(QMouseEvent * event){
		emit doubleClickeScrollAreaSignal();
	}


    void gggtouchEvent(QTouchEvent *event){
        qDebug("WWWWW");
    }
};

#endif // CUSTOMSCROLLAREA_H

