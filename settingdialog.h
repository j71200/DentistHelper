#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "preferences.h"

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

    void on_saveButton_clicked();

    void on_discardButton_clicked();

    void on_homeFolderEdit_textChanged(const QString &newHomeFolderPath);

    void on_xrayFolderNameLineEdit_textChanged(const QString &newHomeFolderPath);

    void on_imgFolderNameLineEdit_textChanged(const QString &newHomeFolderPath);

    void on_autoOpenCheckBox_stateChanged(int newState);

private:
    Ui::SettingDialog *ui;
    QPixmap legalIcon;
    QPixmap illegalIcon;

    void checkHomeFolder(QString newHomeFolderPath);
    void checkXRayFolderName(QString newFolderName);
    void checkImageFolderName(QString newFolderName);

};

#endif // SETTINGDIALOG_H
