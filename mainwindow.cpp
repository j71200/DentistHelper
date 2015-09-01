#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollArea>
#include <QFileDialog>
#include <QFileSystemModel>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "default_setting.h"

QString Preferences::folderPath = Preferences::getInitFolderPath();

using namespace std;

// File I/O
bool isSavedFileExist, isNoteDirty;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // =====================
    // Initialize parameters
    // =====================
    isNoteDirty = false;
    isSavedFileExist = false;
    model = new QFileSystemModel;

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
    changeTreeView(Preferences::getFolderPath());

    // Initialize actions
    initOpenFolderAction();
    initSettingAction();

    currFolderQDir = new QDir(Preferences::getFolderPath());

    // Connecting
    connect(ui->treeView, SIGNAL(zKeyPressedSignal(QString)), this, SLOT(on_zKeyPressed(QString)));
    connect(ui->treeView, SIGNAL(xKeyPressedSignal(QString)), this, SLOT(on_xKeyPressed(QString)));
    connect(ui->treeView, SIGNAL(folderChangedSignal(QString, QString)), this, SLOT(on_folderChanged(QString, QString)));

}

MainWindow::~MainWindow(){
    delete ui;
    delete model;
    delete currFolderQDir;
    delete leftImageLabel, rightImageLabel;
}

// ================================
// Initialize Open Folder Action
// ================================
void MainWindow::initOpenFolderAction(){
    QAction *openFolderAct;

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
        tr("Open Folder"), Preferences::getFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){
        changeTreeView(dir);
    }
}

void MainWindow::changeTreeView(QString dir){
    // Set file system model
    model->setRootPath(dir);
    
    ui->treeView->setModel(model);
    
    // Set the treeView so that it will only show particular folder
    ui->treeView->setRootIndex(model->index(dir));
    // Hide the useless columns, like file size, kind and date modified
    for(int i = 1; i < model->columnCount(); i++){
        ui->treeView->setColumnHidden(i, true);
    }
}

// =========================
// Initialize Setting Action
// =========================
void MainWindow::initSettingAction(){
    QAction *settingAct;

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

void MainWindow::closeEvent(QCloseEvent *event){
    if(isNoteDirty){

        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Save:
                // Save was clicked
                if(isSavedFileExist){
                    // TODO Directly save
                }
                else{
                    // TODO Open save as dialog
                }
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                event->accept();
                break;
            case QMessageBox::Cancel:
                // Cancel was clicked
                event->ignore();
                break;
            default:
                // should never be reached
                break;
        }

    }
}

void MainWindow::on_testButton_clicked(){


    // ============== Open Directory function ==============
    // QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/Users/blue", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


    // ============== Save function ==============    
    // QFile noteFile(currFolderQDir->path() + QDir::separator() + currFolderQDir->dirName() + "_note.txt");
    // if(!noteFile.exists()){
    //     cout << "File do not exist" << endl;
    //     return;
    // }

    // QFile noteFile(currFolderPath + QDir::separator() + currFolderName + "_note.txt");

    // if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text)){
    //     cout << "Open note file for writing fail" << endl;
    //     return;
    // }

    // QString noteText = ui->noteTextEdit->toPlainText();
    // QTextStream outStream(&noteFile);
    // outStream << noteText;
    // noteFile.close();

}

void MainWindow::on_plainTextEdit_textChanged(){
    isNoteDirty = true;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index){
    ui->patientNameLabel->setText(model->fileName(index));
    model->fileInfo(index);  // TODO Delete it

    currFolderQDir->setPath(model->filePath(index));
    QStringList imgFileList = currFolderQDir->entryList(QDir::Files);

    leftImageSize = QSize(ui->leftScrollArea->width(), ui->leftScrollArea->height());
    rightImageSize = QSize(ui->rightScrollArea->width(), ui->rightScrollArea->height());

    switch (imgFileList.size()) {
    case 0:
        // cout << "No image in folder: " << currFolderQDir->path().toStdString() << endl;
        break;

    case 1:
        leftImgFilePath = currFolderQDir->path() + QDir::separator() + imgFileList.at(0);
        leftImage = QPixmap(leftImgFilePath).scaled(leftImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        leftImageLabel->setPixmap(leftImage);
        setLeftImgToolsVisible(true);
        resetLeftImgTools();

        setRightImgToolsVisible(false);
        resetRightImgTools();
        rightImageLabel->clear();
        break;

    case 2:
        leftImgFilePath = currFolderQDir->path() + QDir::separator() + imgFileList.at(0);
        leftImage = QPixmap(leftImgFilePath).scaled(leftImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        leftImageLabel->setPixmap(leftImage);
        setLeftImgToolsVisible(true);
        resetLeftImgTools();

        rightImgFilePath = currFolderQDir->path() + QDir::separator() + imgFileList.at(1);
        rightImage = QPixmap(rightImgFilePath).scaled(rightImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        rightImageLabel->setPixmap(rightImage);
        setRightImgToolsVisible(true);
        resetRightImgTools();
        break;
        
    default:
        
        break;
    }
}

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

void MainWindow::on_zKeyPressed(QString newImagePath){
    leftImage = QPixmap(newImagePath);
    if(leftImage.isNull())
        return;
    leftImage = leftImage.scaled(leftImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    leftImageLabel->setPixmap(leftImage);
    setLeftImgToolsVisible(true);
    resetLeftImgTools();
}

void MainWindow::on_xKeyPressed(QString newImagePath){
    rightImage = QPixmap(newImagePath);
    if(rightImage.isNull())
        return;
    rightImage = rightImage.scaled(rightImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rightImageLabel->setPixmap(rightImage);
    setRightImgToolsVisible(true);
    resetRightImgTools();
}

void MainWindow::on_folderChanged(QString newFolderPath, QString newFolderName){
    saveNote();

    currFolderPath = newFolderPath;
    currFolderName = newFolderName;

    QString noteFilePath = newFolderPath + QDir::separator() + newFolderName + "_note.txt";

    QFile noteFile(noteFilePath);
    if(!noteFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        cout << "Read note file failed" << endl;
        ui->noteTextEdit->setPlainText("How about taking some note");
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

void MainWindow::saveNote(){
    QFile noteFile(currFolderPath + QDir::separator() + currFolderName + "_note.txt");

    if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout << "Open note file for writing fail" << endl;
        return;
    }

    QString noteText = ui->noteTextEdit->toPlainText();
    QTextStream outStream(&noteFile);
    outStream << noteText;
    noteFile.close();
}
