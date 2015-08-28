#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "preferences.cpp"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_changeFolderButton_clicked();

    void closeEvent(QCloseEvent *event);

    void on_saveButton_clicked();

    void on_discardButton_clicked();

private:
    Ui::SettingDialog *ui;

    Preferences mPreferences;
};

#endif // SETTINGDIALOG_H
