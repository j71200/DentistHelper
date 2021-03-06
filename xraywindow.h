#ifndef XRAYWINDOW_H
#define XRAYWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include "customimagelabel.h"
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
	void on_fileChanged(QString);
	void on_scaleSlider_valueChanged(int value);
    void on_patientChanged(QString newPatientFolderPath);
    void on_fitWindowSizeButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_tvSpacePressed();
    void closeEvent(QCloseEvent *event);
    void on_scrollAreaDoubleClicked();

signals:
    void xrayWindowClosedSignal();

private:
    Ui::XRayWindow *ui;

    // Image
    CustomImageLabel *xrayLabel;
    QSize xrayImageSize;
    QPixmap xrayImage;
    void loadImage(QString imagePath);
    void resetImage();
    void setScaleTools(int value);
    int calculateFitScaleRatio();
    bool scaleImageWhenSliding;

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;
    
};

#endif // XRAYWINDOW_H
