#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemModel>

namespace Ui {
class ImageWindow;
}

class ImageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);
    ~ImageWindow();

private slots:
	void resizeEvent(QResizeEvent *event);
	void on_fileChanged(QString);
	void on_scaleSlider_valueChanged(int value);

private:
    Ui::ImageWindow *ui;

    // Image
    QLabel *imageLabel;
    QSize imageSize;
    QPixmap image;
    void loadImage(QString imagePath);
    void resetScaleTools();
    void setScaleToolsVisible(bool isVisible);

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;

};

#endif // IMAGEWINDOW_H
