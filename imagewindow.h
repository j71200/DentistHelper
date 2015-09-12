#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QLabel>
#include <QPixmap>

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
    void on_fileChanged(QString);
    void on_scaleSlider_valueChanged(int value);
    void on_patientChanged(QString newPatientFolderPath);
    void on_fitWindowSizeButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_tvSpacePressed();
    void closeEvent(QCloseEvent *event);
    void on_scrollAreaDoubleClicked();

signals:
    void imageWindowClosedSignal();

private:
    Ui::ImageWindow *ui;

    // Image
    QLabel *imageLabel;
    QSize imageSize;
    QPixmap image;
    void loadImage(QString imagePath);
    void resetImage();
    void setScaleTools(int value);
    int calculateFitScaleRatio();

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;

};

#endif // IMAGEWINDOW_H
