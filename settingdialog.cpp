#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "default_setting.h"
#include <QFileDialog>
#include <iostream>
#include "messagedialog.h"
#include <QCloseEvent>

using namespace std;

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    // Home folder
    ui->homeFolderEdit->setText(Preferences::getHomeFolderPath());

    // X-ray folder
    ui->xrayFolderNameLineEdit->setText(Preferences::getXrayFolderName());
    ui->xrayPathPrefixLabel->setText(Preferences::getPatientFolderPath() + QDir::separator());
    ui->xrayCorrectMsgLabel->setText("");

    // Image folder
    ui->imgFolderNameLineEdit->setText(Preferences::getImageFolderName());
    ui->imgPathPrefixLabel->setText(Preferences::getPatientFolderPath() + QDir::separator());
    ui->imgCorrectMsgLabel->setText("");
}

SettingDialog::~SettingDialog(){
    delete ui;
}

void SettingDialog::on_changeFolderButton_clicked(){
	QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(!dir.isEmpty()){
        ui->homeFolderEdit->setText(dir);
	}
}

void SettingDialog::on_saveButton_clicked(){
    QDir tempQDir(ui->homeFolderEdit->text());
    if(tempQDir.isReadable()){
        Preferences::setHomeFolderPath(ui->homeFolderEdit->text());
        Preferences::setXrayFolderName(ui->xrayFolderNameLineEdit->text());
        Preferences::setImageFolderName(ui->imgFolderNameLineEdit->text());
        Preferences::save();
        
        this->accept();
    }
    else{
        MessageDialog mMessageDialog;
        mMessageDialog.setWindowTitle(MESSAGE_DIALOG_TITLE);
        mMessageDialog.setMessage("Wrong folder path!");
        mMessageDialog.setFixedSize(mMessageDialog.size());
        mMessageDialog.exec();
    }
}

void SettingDialog::on_discardButton_clicked(){
    this->reject();
}
