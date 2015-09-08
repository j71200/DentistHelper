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

	// ===========================
	//          Listeners
	// ===========================
    void closeEvent(QCloseEvent *event);
    void on_testButton_clicked();

private:
    Ui::MainWindow *ui;

    void initOpenFolderAction();
    void initSettingAction();

    // Note
    void saveNote();

    // Action
    QAction *openFolderAct;
    QAction *settingAct;

    // Folder/File system
    QFileSystemModel *model;
    QString currFolderPath, currFolderName;

    XRayWindow *xrayWindowPtr;
    ImageWindow *imageWindowPtr;

};

#endif // MAINWINDOW_H
