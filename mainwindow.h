#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingdialog.h"
#include "preferences.h"
#include <QFileSystemModel>
#include <QLabel>
#include "xraywindow.h"
#include "imagewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void patientChangedSignal(QString);

private slots:
	// =====================
	//        Actions
	// =====================
	void on_openFolder_active();
	void on_setting_active();
    void on_xray_active();
    void on_image_active();

	// ===========================
	//          Listeners
	// ===========================
    void closeEvent(QCloseEvent *event);
    void on_testButton_clicked();

private:
    Ui::MainWindow *ui;

    void initWindows();
    void initOpenFolderAction();
    void initSettingAction();
    void initOpenXRayWindowAction();
    void initOpenImageWindowAction();

    // Note
    void saveNote();
    void refreshNote();

    // Action
    QAction *openFolderAct, *settingAct, *xrayAct, *imageAct;

    // Folder/File system
    QFileSystemModel *model;
    QString currFolderPath, currFolderName;

    XRayWindow *xrayWindowPtr;
    ImageWindow *imageWindowPtr;

};

#endif // MAINWINDOW_H
