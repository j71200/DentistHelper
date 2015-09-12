#ifndef CUSTOMIMAGELABEL
#define CUSTOMIMAGELABEL

#include <QLabel>
#include <QGestureEvent>
#include <QDebug>
#include <iostream>
#include"default_setting.h"

using namespace std;

class CustomImageLabel : public QLabel{

    Q_OBJECT

public:
    CustomImageLabel(QWidget *parent = 0) : QLabel(parent){

        pinchCounter = 0;
        panCounter = 0;
        swipeCounter = 0;

        this->grabGesture(Qt::PinchGesture);
        this->grabGesture(Qt::PanGesture);
        this->grabGesture(Qt::SwipeGesture);

    }
    virtual ~CustomImageLabel(){}

    void setOriginalPixmap(QPixmap newOrigPixmap){
        originalPixmap = newOrigPixmap;
        this->setPixmap(originalPixmap);
    }


protected:
    bool event(QEvent *event)
    {
        if (event->type() == QEvent::Gesture)
            return gestureEvent(static_cast<QGestureEvent*>(event));
        return QWidget::event(event);
    }

private:
    int pinchCounter, panCounter, swipeCounter;
    QPixmap originalPixmap;

    bool gestureEvent(QGestureEvent *event)
    {
        if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
            swipeTriggered(static_cast<QSwipeGesture *>(swipe));
        else if (QGesture *pan = event->gesture(Qt::PanGesture))
            panTriggered(static_cast<QPanGesture *>(pan));
        if (QGesture *pinch = event->gesture(Qt::PinchGesture))
            pinchTriggered(static_cast<QPinchGesture *>(pinch));
        return true;
    }

    void pinchTriggered(QPinchGesture *gesture)
    {
        // pinchCounter++;
        // cout << "PINCH" + QString::number(pinchCounter).toStdString() << endl;

        QSize ss = this->pixmap()->size();
        if( gesture->scaleFactor() <= 1
            && (ss.width() <= 30 || ss.height() <= 30) )
            return;
        if( gesture->scaleFactor() >= 1
            && (ss.width() >= 1000 || ss.height() >= 1000) )
            return;

        qreal adjustmentFactor = 0.8; // In the intervial (0, 1)
        qreal myScaleFactor;
        myScaleFactor = adjustmentFactor * (gesture->scaleFactor() - 1) + 1;

        QPixmap pp = originalPixmap.scaled(ss*myScaleFactor, Qt::KeepAspectRatio, Qt::FastTransformation);
        this->setPixmap( pp );
        


        // QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
        // if (changeFlags & QPinchGesture::RotationAngleChanged) {
        //     qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
        //     rotationAngle += rotationDelta;
        //     qCDebug(lcExample) << "pinchTriggered(): rotate by" <<
        //         rotationDelta << "->" << rotationAngle;
        // }
        // if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        //     currentStepScaleFactor = gesture->totalScaleFactor();
        //     qCDebug(lcExample) << "pinchTriggered(): zoom by" <<
        //         gesture->scaleFactor() << "->" << currentStepScaleFactor;
        // }
        // if (gesture->state() == Qt::GestureFinished) {
        //     scaleFactor *= currentStepScaleFactor;
        //     currentStepScaleFactor = 1;
        // }
        // update();
    }



    void panTriggered(QPanGesture *gesture)
    {
        // panCounter++;
        // cout << "             PAN" + QString::number(panCounter).toStdString() << endl;

    // #ifndef QT_NO_CURSOR
    //     switch (gesture->state()) {
    //         case Qt::GestureStarted:
    //         case Qt::GestureUpdated:
    //             setCursor(Qt::SizeAllCursor);
    //             break;
    //         default:
    //             setCursor(Qt::ArrowCursor);
    //     }
    // #endif
    //     QPointF delta = gesture->delta();
    //     qCDebug(lcExample) << "panTriggered():" << gesture;
    //     horizontalOffset += delta.x();
    //     verticalOffset += delta.y();
    //     update();

    }


    void swipeTriggered(QSwipeGesture *gesture)
    {
        // swipeCounter++;
        // cout << "                            SWIPE" + QString::number(swipeCounter).toStdString() << endl;
        
        // if (gesture->state() == Qt::GestureFinished) {
        //     if (gesture->horizontalDirection() == QSwipeGesture::Left
        //         || gesture->verticalDirection() == QSwipeGesture::Up) {
        //         qCDebug(lcExample) << "swipeTriggered(): swipe to previous";
        //         goPrevImage();
        //     } else {
        //         qCDebug(lcExample) << "swipeTriggered(): swipe to next";
        //         goNextImage();
        //     }
        //     update();
        // }
    }




};


#endif // CUSTOMIMAGELABEL

