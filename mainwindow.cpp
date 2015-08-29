#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QScrollArea>
#include <QFileDialog>
#include <QFileSystemModel>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "default_setting.h"

//bool Preferences::isLoadingSucc = Preferences::load();
QString Preferences::folderPath = Preferences::getInitFolderPath();

using namespace std;

QLabel *leftImageView, *rightImageView;
QSize stdImageSize;
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

    // Initialize window
    stdImageSize.setWidth(512);
    stdImageSize.setHeight(512);
    QPixmap lena = QPixmap("/Users/blue/Pictures/lena.gif").scaled(stdImageSize);
    QPixmap lenaGray = QPixmap("/Users/blue/Pictures/lena_gray.gif").scaled(stdImageSize);

    leftImageView = new QLabel;
    rightImageView = new QLabel;
    leftImageView->setPixmap(lena);
    rightImageView->setPixmap(lenaGray);

    ui->leftScrollArea->setWidget(leftImageView);
    ui->rightScrollArea->setWidget(rightImageView);

    // Load preferences
//    mPreferences.load();

//    cout << "dsfd: " << Preferences::getFolderPath().toStdString() << endl;

    changeTreeView(mPreferences.getFolderPath());

    // Initialize actions
    initOpenFolderAction();
    initSettingAction();

}

MainWindow::~MainWindow(){
    delete ui;
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
        tr("Open Folder"), mPreferences.getFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){
        changeTreeView(dir);
    }
}

void MainWindow::changeTreeView(QString dir){
    // Set file system model
    QFileSystemModel *model = new QFileSystemModel;
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
void MainWindow::on_changeLeftButton_clicked(){
    QString imageFileName;
    imageFileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/Users/blue/Pictures", tr("Image Files (*.png *.jpg *.bmp *.gif)"));

    if(!imageFileName.isEmpty()){
        QPixmap newImage = QPixmap(imageFileName).scaled(stdImageSize);
        leftImageView->setPixmap(newImage);
    }
}

void MainWindow::on_changeRightButton_clicked(){
    QString imageFileName;
    imageFileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/Users/blue/Pictures", tr("Image Files (*.png *.jpg *.bmp *.gif)"));

    if(!imageFileName.isEmpty()){
        QPixmap newImage = QPixmap(imageFileName).scaled(stdImageSize);
        rightImageView->setPixmap(newImage);
    }
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

// FORTEST
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

}

void MainWindow::test(){
    cout << "TESTESTT" << endl;
}




