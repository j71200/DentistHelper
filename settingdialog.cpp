#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "default_setting.h"
#include <QFileDialog>
#include <iostream>
#include "messagedialog.h"
#include <QCloseEvent>

using namespace std;

// QWidget *parentWidget;

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    // ============
    // Initializing
    // ============
    // parentWidget = parent;


    ui->currentFolderEdit->setText(mPreferences.getFolderPath());
}

SettingDialog::~SettingDialog(){
    delete ui;
}

void SettingDialog::on_changeFolderButton_clicked(){
	QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), DEFAULT_FOLDER_PATH,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if(!dir.isEmpty()){
		mPreferences.setFolderPath(dir);
        ui->currentFolderEdit->setText(dir);

        // parentWidget->test();
	}
}

void SettingDialog::closeEvent(QCloseEvent *event){
    // QDir tempQDir(ui->currentFolderEdit->text());
    // if(tempQDir.isReadable()){
    //     cout << "Readable!!!" << endl;

    //     event->accept();
    // }
    // else{
    //     MessageDialog mMessageDialog;
    //     mMessageDialog.exec();

    //     event->ignore();

    // }
}

void SettingDialog::on_saveButton_clicked(){
    QDir tempQDir(ui->currentFolderEdit->text());
    if(tempQDir.isReadable()){
        mPreferences.setFolderPath(ui->currentFolderEdit->text());
        mPreferences.save();
        
        this->accept();
    }
    else{
        MessageDialog mMessageDialog;
        QString message = QString("Wrong folder path!");
        mMessageDialog.setMessage(message);
        mMessageDialog.exec();
    }
}

void SettingDialog::on_discardButton_clicked(){
    this->reject();
}
