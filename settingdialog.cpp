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

    ui->homeFolderEdit->setText(Preferences::getHomeFolderPath());
    ui->xrayFolderNameLineEdit->setText(Preferences::getXrayFolderName());
    ui->xrayCorrectMsgLabel->setText("");
    ui->imageFolderNameLineEdit->setText(Preferences::getImageFolderName());
    ui->imageCorrectMsgLabel->setText("");
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
        Preferences::setImageFolderName(ui->imageFolderNameLineEdit->text());
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
