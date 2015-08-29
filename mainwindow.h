#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingdialog.h"
#include "preferences.cpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void test();

private slots:
	// =====================
	//        Actions
	// =====================
	void on_openFolder_active();
	void on_setting_active();
	

	// ===========================
	//          Listeners
	// ===========================
    void on_changeLeftButton_clicked();
    void on_changeRightButton_clicked();
    void closeEvent(QCloseEvent *event);
    void on_testButton_clicked();
    void on_plainTextEdit_textChanged();
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    void initOpenFolderAction();
    void initSettingAction();
    void changeTreeView(QString dir);
};

#endif // MAINWINDOW_H
