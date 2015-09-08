#ifndef XRAYWINDOW_H
#define XRAYWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class XRayWindow;
}

class XRayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit XRayWindow(QWidget *parent = 0);
    ~XRayWindow();

private slots:
	void resizeEvent(QResizeEvent *event);
	void on_fileChanged(QString);
	void on_scaleSlider_valueChanged(int value);

private:
    Ui::XRayWindow *ui;

    // Image
    QLabel *xrayLabel;
    QSize xrayImageSize;
    QPixmap xrayImage;
    void loadImage(QString imagePath);
    void resetScaleTools();
    void setScaleToolsVisible(bool isVisible);

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;
    
};

#endif // XRAYWINDOW_H