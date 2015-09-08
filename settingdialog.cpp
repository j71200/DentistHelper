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


    ui->currentFolderEdit->setText(Preferences::getHomeFolderPath());
}

SettingDialog::~SettingDialog(){
    delete ui;
}

void SettingDialog::on_changeFolderButton_clicked(){
	QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(!dir.isEmpty()){
        ui->currentFolderEdit->setText(dir);
	}
}

void SettingDialog::on_saveButton_clicked(){
    QDir tempQDir(ui->currentFolderEdit->text());
    if(tempQDir.isReadable()){
        Preferences::setHomeFolderPath(ui->currentFolderEdit->text());
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
