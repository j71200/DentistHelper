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

    // Initialize variables
    legalIcon = QPixmap(APP_FOLDER_PATH + CHECK_ICON_SUFFIX).scaled(DEFAULT_ICON_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    illegalIcon = QPixmap(APP_FOLDER_PATH + CROSS_ICON_SUFFIX).scaled(DEFAULT_ICON_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Home folder
    ui->homeFolderEdit->setText(Preferences::getHomeFolderPath());
    ui->homeCorrectMsgLabel->setText("");

    // X-ray folder
    ui->xrayPathPrefixLabel->setText(Preferences::getPatientFolderPath() + QDir::separator());
    ui->xrayFolderNameLineEdit->setText(Preferences::getXrayFolderName());
    ui->xrayCorrectMsgLabel->setText("");

    // Image folder
    ui->imgPathPrefixLabel->setText(Preferences::getPatientFolderPath() + QDir::separator());
    ui->imgFolderNameLineEdit->setText(Preferences::getImageFolderName());
    ui->imgCorrectMsgLabel->setText("");

}

SettingDialog::~SettingDialog(){
    delete ui;
}


// =========================================== [ Window ] ==
// Save button
// =========================================================
void SettingDialog::on_saveButton_clicked(){
    if(ui->homeFolderEdit->text().isEmpty()
        || ui->xrayFolderNameLineEdit->text().isEmpty()
        || ui->imgFolderNameLineEdit->text().isEmpty()){
        MessageDialog mMessageDialog;
        mMessageDialog.setMessage("There is at least one empty slot");
        mMessageDialog.exec();
        return;
    }

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
        mMessageDialog.setMessage("Wrong folder path!");
        mMessageDialog.exec();
    }
}


// =========================================== [ Window ] ==
// Discard button
// =========================================================
void SettingDialog::on_discardButton_clicked(){
    this->reject();
}


// ============================================= [ Home ] ==
// Open a dialog to change the path of home folder
// =========================================================
void SettingDialog::on_changeFolderButton_clicked(){
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){
        ui->homeFolderEdit->setText(dir);
    }
}


// ============================================= [ Home ] ==
// Check home folder
// =========================================================
void SettingDialog::checkHomeFolder(QString newHomeFolderPath){
    if( !newHomeFolderPath.isEmpty() && QDir(newHomeFolderPath).isReadable() )
        ui->homeCorrectMsgLabel->setPixmap(legalIcon);
    else
        ui->homeCorrectMsgLabel->setPixmap(illegalIcon);
}

// ============================================= [ Home ] ==
// Check home folder when it changed
// =========================================================
void SettingDialog::on_homeFolderEdit_textChanged(const QString &newHomeFolderPath){
    checkHomeFolder(newHomeFolderPath);
}


// ============================================ [ X-ray ] ==
// Check xray folder
// =========================================================
void SettingDialog::checkXRayFolderName(QString newFolderName){
    QString xrayRootPath = Preferences::getPatientFolderPath() + QDir::separator() + newFolderName;

    if( !newFolderName.isEmpty() && QDir(xrayRootPath).isReadable() )
        ui->xrayCorrectMsgLabel->setPixmap(legalIcon);
    else
        ui->xrayCorrectMsgLabel->setPixmap(illegalIcon);
}

// ============================================ [ X-ray ] ==
// Check xray folder when it changed
// =========================================================
void SettingDialog::on_xrayFolderNameLineEdit_textChanged(const QString &newFolderName){
    checkXRayFolderName(newFolderName);
}

// ============================================ [ Image ] ==
// Check image folder
// =========================================================
void SettingDialog::checkImageFolderName(QString newFolderName){
    QString imageRootPath = Preferences::getPatientFolderPath() + QDir::separator() + newFolderName;

    if( !newFolderName.isEmpty() && QDir(imageRootPath).isReadable() )
        ui->imgCorrectMsgLabel->setPixmap(legalIcon);
    else
        ui->imgCorrectMsgLabel->setPixmap(illegalIcon);
}

// ============================================ [ Image ] ==
// Check image folder when it changed
// =========================================================
void SettingDialog::on_imgFolderNameLineEdit_textChanged(const QString &newFolderName){
    checkImageFolderName(newFolderName);
}


