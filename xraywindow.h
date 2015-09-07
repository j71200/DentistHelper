#ifndef XRAYWINDOW_H
#define XRAYWINDOW_H

#include <QWidget>

namespace Ui {
class XRayWindow;
}

class XRayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit XRayWindow(QWidget *parent = 0);
    ~XRayWindow();

private:
    Ui::XRayWindow *ui;
};

#endif // XRAYWINDOW_H
