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
	void on_fileChanged(QString);
	void on_scaleSlider_valueChanged(int value);
    void on_patientChanged(QString newPatientFolderPath);
    void on_fitWindowSizeButton_clicked();

private:
    Ui::XRayWindow *ui;

    // Image
    QLabel *xrayLabel;
    QSize xrayImageSize;
    QPixmap xrayImage;
    void loadImage(QString imagePath);
    void resetImage();
    void setScaleTools(int value);

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;
    
};

#endif // XRAYWINDOW_H
