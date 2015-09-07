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
	void on_treeView_clicked(const QModelIndex &index);
	void resizeEvent(QResizeEvent *event);

private:
    Ui::XRayWindow *ui;


    // Image
    QLabel *xrayLabel;
    QSize xrayImageSize;
    QPixmap xrayImage;
    void loadImage(QString imagePath);

    // TreeView
    QFileSystemModel *model;
    void changeTreeView(QString dir);
    QString selectedFilePath;
    

};

#endif // XRAYWINDOW_H
