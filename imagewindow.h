#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>

namespace Ui {
class ImageWindow;
}

class ImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);
    ~ImageWindow();

private:
    Ui::ImageWindow *ui;
};

#endif // IMAGEWINDOW_H
