/*
There are several classes in my classification, like
[MainWindow]
[Action]
[TreeView]
[Image]
[Development]
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QFileDialog>
#include <QFileSystemModel>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "default_setting.h"

QString Preferences::homeFolderPath = DEFAULT_FOLDER_PATH;
QString Preferences::patientFolderPath = DEFAULT_FOLDER_PATH;
QString Preferences::inStreamBuffer = "";

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // =====================
    // Initialize parameters
    // =====================
    model = new QFileSystemModel;
    Preferences::load();

    // ======================
    // Initialize image block
    // ======================
    leftImageLabel = new QLabel;
    rightImageLabel = new QLabel;
    leftImageLabel->setAlignment(Qt::AlignCenter);
    rightImageLabel->setAlignment(Qt::AlignCenter);
    ui->leftScrollArea->setWidget(leftImageLabel);
    ui->rightScrollArea->setWidget(rightImageLabel);

    ui->leftImgRatioSlider->setMinimum(10);
    ui->leftImgRatioSlider->setMaximum(300);
    ui->leftImgRatioSlider->setSingleStep(10);
    ui->rightImgRatioSlider->setMinimum(10);
    ui->rightImgRatioSlider->setMaximum(300);
    ui->rightImgRatioSlider->setSingleStep(10);

    ui->leftImgRatioSlider->setValue(100);
    ui->rightImgRatioSlider->setValue(100);

    ui->leftImgRatioLabel->setAlignment(Qt::AlignRight);
    ui->rightImgRatioLabel->setAlignment(Qt::AlignRight);

    setLeftImgToolsVisible(false);
    setRightImgToolsVisible(false);


    // Initialize TreeView
    changeTreeView(Preferences::getHomeFolderPath());

    // Initialize actions
    initOpenFolderAction();
    initSettingAction();

    // ===============
    // Initialize note
    // ===============
    ui->noteTextEdit->setPlaceholderText(PLAIN_TEXT_EDIT_HINT);

    // Connecting
    connect(ui->treeView, SIGNAL(zKeyPressedSignal(QString)), this, SLOT(on_zKeyPressed(QString)));
    connect(ui->treeView, SIGNAL(xKeyPressedSignal(QString)), this, SLOT(on_xKeyPressed(QString)));
    connect(ui->treeView, SIGNAL(folderChangedSignal(QString, QString)), this, SLOT(on_folderChanged(QString, QString)));

}

MainWindow::~MainWindow(){
    delete ui;
    delete model;
    delete leftImageLabel, rightImageLabel;
}

// ======================================= [ MainWindow ] ==
// Window Events
// =========================================================
void MainWindow::closeEvent(QCloseEvent *event){
    saveNote();
    QMainWindow::closeEvent(event);
}

// =========================================== [ Action ] ==
// Initialize Open Folder Action
// =========================================================
void MainWindow::initOpenFolderAction(){
    QString iconPath(APP_FOLDER_PATH + QString("icons/open_folder.png"));
    openFolderAct = new QAction(QIcon( iconPath ), tr("Open Folder"), this);
    openFolderAct->setShortcuts(QKeySequence::Open);
    openFolderAct->setStatusTip(tr("Open an folder"));
    connect(openFolderAct, SIGNAL(triggered()), this, SLOT(on_openFolder_active()));

    ui->menuFile->addAction(openFolderAct);
    ui->mainToolBar->addAction(openFolderAct);
}

void MainWindow::on_openFolder_active(){
    // Open a file dialog and ask for a new directory
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){
        changeTreeView(dir);
        Preferences::setPatientFolderPath(dir);
    }
}

// =========================================== [ Action ] ==
// Initialize Setting Action
// =========================================================
void MainWindow::initSettingAction(){
    QString iconPath(APP_FOLDER_PATH + QString("icons/setting.png"));
    settingAct = new QAction(QIcon( iconPath ), tr("Setting"), this);
    // settingAct->setShortcuts(QKeySequence::Preferences);
    settingAct->setStatusTip(tr("Setting"));
    connect(settingAct, SIGNAL(triggered()), this, SLOT(on_setting_active()));

    ui->menuFile->addAction(settingAct);
    ui->mainToolBar->addAction(settingAct);
}

void MainWindow::on_setting_active(){
    SettingDialog mSettingDialog;
    mSettingDialog.setFixedSize(mSettingDialog.size());  // Fix the size of setting dialog
    mSettingDialog.exec();
}

// ========================================= [ TreeView ] ==
// Change the Directory of TreeView
// =========================================================
void MainWindow::changeTreeView(QString dir){
    // Set file system model
    model->setRootPath(dir);
    model->setNameFilters(READABLE_IMAGE_LIST);
    model->setNameFilterDisables(false);
    ui->treeView->setModel(model);
    
    // Set the treeView so that it will only show particular folder
    ui->treeView->setRootIndex(model->index(dir));
    // Hide the useless columns, like file size, kind and date modified
    for(int i = 1; i < model->columnCount(); i++){
        ui->treeView->setColumnHidden(i, true);
    }
}

// ========================================= [ TreeView ] ==
// Shortcuts
// =========================================================
void MainWindow::on_zKeyPressed(QString newImagePath){
    leftImage = QPixmap(newImagePath);
    if(leftImage.isNull())
        return;
    leftImageSize = QSize(ui->leftScrollArea->width(), ui->leftScrollArea->height());
    leftImage = leftImage.scaled(leftImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    leftImageLabel->setPixmap(leftImage);
    setLeftImgToolsVisible(true);
    resetLeftImgTools();
}

void MainWindow::on_xKeyPressed(QString newImagePath){
    rightImage = QPixmap(newImagePath);
    if(rightImage.isNull())
        return;
    rightImageSize = QSize(ui->rightScrollArea->width(), ui->rightScrollArea->height());
    rightImage = rightImage.scaled(rightImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rightImageLabel->setPixmap(rightImage);
    setRightImgToolsVisible(true);
    resetRightImgTools();
}

// ============================================ [ Image ] ==
// Set/Reset Image Tools
// =========================================================
void MainWindow::resetLeftImgTools(){
    ui->leftImgRatioLabel->setText("100%");
    ui->leftImgRatioSlider->setValue(100);
}

void MainWindow::resetRightImgTools(){
    ui->rightImgRatioLabel->setText("100%");
    ui->rightImgRatioSlider->setValue(100);
}

void MainWindow::setLeftImgToolsVisible(bool isVisible){
    ui->leftImgRatioLabel->setVisible(isVisible);
    ui->leftImgRatioSlider->setVisible(isVisible);
}

void MainWindow::setRightImgToolsVisible(bool isVisible){
    ui->rightImgRatioLabel->setVisible(isVisible);
    ui->rightImgRatioSlider->setVisible(isVisible);
}

// ============================================ [ Image ] ==
// Image RatioSlider Slot
// =========================================================
void MainWindow::on_leftImgRatioSlider_valueChanged(int value){
    if(leftImage.isNull())
        return;

    QString newRatioText = QString::number(value) + "%";
    ui->leftImgRatioLabel->setText(newRatioText);

    QSize newScaledSize = leftImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = leftImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    leftImageLabel->setPixmap(newScaledPixmap);
}

void MainWindow::on_rightImgRatioSlider_valueChanged(int value){
    if(rightImage.isNull())
        return;

    QString newRatioText = QString::number(value) + "%";
    ui->rightImgRatioLabel->setText(newRatioText);

    QSize newScaledSize = rightImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = rightImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rightImageLabel->setPixmap(newScaledPixmap);
}

// ============================================= [ Note ] ==
// Refresh Note Content if Folder Changed
// =========================================================
void MainWindow::on_folderChanged(QString newFolderPath, QString newFolderName){
    saveNote();

    currFolderPath = newFolderPath;
    currFolderName = newFolderName;

    QString noteFilePath = newFolderPath + QDir::separator() + newFolderName + NOTE_FILE_SUFFIX_NAME;

    QFile noteFile(noteFilePath);
    if(!noteFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        cout << "Read note file failed" << endl;
    }
    else{
        cout << "Read note file successfully" << endl;
        QTextStream inStream(&noteFile);
        ui->noteTextEdit->clear();
        while (!inStream.atEnd()) {
            ui->noteTextEdit->appendPlainText(inStream.readLine());
        }
    }
    noteFile.close();
}

// ============================================= [ Note ] ==
// Function for Saving Note
// =========================================================
void MainWindow::saveNote(){
    QFile noteFile(currFolderPath + QDir::separator() + currFolderName + NOTE_FILE_SUFFIX_NAME);

    if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout << "Open note file for writing fail" << endl;
        return;
    }

    QString noteText = ui->noteTextEdit->toPlainText();
    QTextStream outStream(&noteFile);
    outStream << noteText;
    noteFile.close();
}

// ====================================== [ Development ] ==
// Test Button
// =========================================================
void MainWindow::on_testButton_clicked(){

}




