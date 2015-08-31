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

    // Initialize parameters
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

    ui->leftImgRatioLabel->setAlignment(Qt::AlignRight);
    ui->rightImgRatioLabel->setAlignment(Qt::AlignRight);

    changeTreeView(Preferences::getFolderPath());


    // Initialize actions
    initOpenFolderAction();
    initSettingAction();

    mQDir = new QDir(Preferences::getFolderPath());

}

MainWindow::~MainWindow(){
    delete ui;
    delete model;
    delete mQDir;
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


// =========================
//          Slots
// =========================
// void MainWindow::on_changeLeftButton_clicked(){
//     QString imgFileName;
//     imgFileName = QFileDialog::getOpenFileName(this,
//     tr("Open Image"), "/Users/blue/Pictures", tr("Image Files (*.png *.jpg *.bmp *.gif)"));

//     if(!imgFileName.isEmpty()){
//         QPixmap newImage = QPixmap(imgFileName).scaled(stdImageSize);
//         leftImageLabel->setPixmap(newImage);
//     }
// }

// void MainWindow::on_changeRightButton_clicked(){
//     QString imgFileName;
//     imgFileName = QFileDialog::getOpenFileName(this,
//     tr("Open Image"), "/Users/blue/Pictures", tr("Image Files (*.png *.jpg *.bmp *.gif)"));

//     if(!imgFileName.isEmpty()){
//         QPixmap newImage = QPixmap(imgFileName).scaled(stdImageSize);
//         rightImageLabel->setPixmap(newImage);
//     }
// }

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
    // QString noteText = ui->noteTextEdit->toPlainText();

    // ofstream fout("/Users/blue/Pictures/temp.txt");
    // if(!fout)
    //     return;
    // fout << noteText.toStdString();
    // fout.close();

}

void MainWindow::on_plainTextEdit_textChanged(){
    isNoteDirty = true;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index){
    ui->patientNameLabel->setText(model->fileName(index));
    model->fileInfo(index);

    mQDir->setPath(model->filePath(index));
    QStringList imgFileList = mQDir->entryList(QDir::Files);

    leftImageSize = QSize(ui->leftScrollArea->width(), ui->leftScrollArea->height());
    rightImageSize = QSize(ui->rightScrollArea->width(), ui->rightScrollArea->height());

    switch (imgFileList.size()) {
    case 1:
        leftImgFilePath = mQDir->path() + QDir::separator() + imgFileList.at(0);
        leftImage = QPixmap(leftImgFilePath).scaled(leftImageSize);

        leftImageLabel->setPixmap(leftImage);
        rightImageLabel->clear();
        break;
    case 2:
        leftImgFilePath = mQDir->path() + QDir::separator() + imgFileList.at(0);
        leftImage = QPixmap(leftImgFilePath).scaled(leftImageSize);
        leftImageLabel->setPixmap(leftImage);

        rightImgFilePath = mQDir->path() + QDir::separator() + imgFileList.at(1);
        rightImage = QPixmap(rightImgFilePath).scaled(rightImageSize);
        rightImageLabel->setPixmap(rightImage);
        break;
    default:
        // TODO
        break;
    }
}

// void MainWindow::on_zoomInLeftButton_clicked(){
    
//     if(imgRatioListIdx + 1 < IMAGE_RATIO_LIST.size()){
//         imgRatioListIdx++;
//         ui->leftImgRatioLabel->setText(IMAGE_RATIO_LIST.at(imgRatioListIdx));

//         leftImageSize *= ZOOM_IN_FACTOR;
//         leftImage = leftImage.scaled(leftImageSize);
//         leftImageLabel->setPixmap(leftImage);
//     }
    
// }

// void MainWindow::on_zoomOutLeftButton_clicked(){
    
//     if(imgRatioListIdx - 1 >= 0){
//         imgRatioListIdx--;
//         ui->leftImgRatioLabel->setText(IMAGE_RATIO_LIST.at(imgRatioListIdx));

//         leftImageSize *= ZOOM_OUT_FACTOR;
//         leftImage = leftImage.scaled(leftImageSize);
//         leftImageLabel->setPixmap(leftImage);
//     }
    
// }


void MainWindow::on_leftImgRatioSlider_valueChanged(int value){
    QString newRatioText = QString::number(value) + "%";
    ui->leftImgRatioLabel->setText(newRatioText);

    QSize newScaledSize = leftImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = leftImage.scaled(newScaledSize);
    leftImageLabel->setPixmap(newScaledPixmap);
}

void MainWindow::on_rightImgRatioSlider_valueChanged(int value){
    QString newRatioText = QString::number(value) + "%";
    ui->rightImgRatioLabel->setText(newRatioText);

    QSize newScaledSize = rightImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = rightImage.scaled(newScaledSize);
    rightImageLabel->setPixmap(newScaledPixmap);
}
