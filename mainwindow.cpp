/*
There are several classes in my classification, like
[MainWindow]
[Action]
--[TreeView]
[X-ray]
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
#include <QDesktopServices>
#include <QRect>
#include <QDesktopWidget>


QString Preferences::homeFolderPath = DEFAULT_FOLDER_PATH;
QString Preferences::patientFolderPath = "";
QString Preferences::patientID = "";
QString Preferences::inStreamBuffer = "";

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ==================
    // Initialize windows
    // ==================
    initWindows();

    // ==================
    // Initialize actions
    // ==================
    initOpenFolderAction();
    initSettingAction();
    initOpenXRayWindowAction();
    initOpenImageWindowAction();


    // ========================
    // Initialize patient label
    // ========================
    ui->patientIDLabel->setAlignment(Qt::AlignCenter);
    ui->patientIDLabel->setText(Preferences::getPatientID());


    // ===============
    // Initialize note
    // ===============
    ui->noteTextEdit->setPlaceholderText(NOTE_HINT);
    refreshNote();


    // ===============
    //   Connecting
    // ===============
    connect(this, SIGNAL(patientChangedSignal(QString)), xrayWindowPtr, SLOT(on_patientChanged(QString)));
    connect(this, SIGNAL(patientChangedSignal(QString)), imageWindowPtr, SLOT(on_patientChanged(QString)));

}

MainWindow::~MainWindow(){
    delete ui;
    delete openFolderAct, settingAct, xrayAct, imageAct;
    delete xrayWindowPtr, imageWindowPtr;
}


// ======================================= [ MainWindow ] ==
// Initilize windows
// =========================================================
void MainWindow::initWindows(){
    QRect rec = QApplication::desktop()->screenGeometry();

    const int SCREEN_WIDTH = rec.width();
    const int SCREEN_HEIGHT = rec.height();

    const QSize DEFAULT_XRAY_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2.5 );
    const QSize DEFAULT_IMAGE_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2.5 );

    xrayWindowPtr = new XRayWindow();
    xrayWindowPtr->show();
    xrayWindowPtr->resize(DEFAULT_XRAY_WINDOW_SIZE);
    // xrayWindowPtr->setFixedSize(DEFAULT_XRAY_WINDOW_SIZE);
    xrayWindowPtr->move(SCREEN_WIDTH/2 + 1, 0);

    imageWindowPtr = new ImageWindow();
    imageWindowPtr->show();
    imageWindowPtr->resize(DEFAULT_IMAGE_WINDOW_SIZE);
    // imageWindowPtr->setFixedSize(DEFAULT_IMAGE_WINDOW_SIZE);
    imageWindowPtr->move(SCREEN_WIDTH/2 + 1, DEFAULT_XRAY_WINDOW_SIZE.height() * 1.2);

    // Setting titles
    this->setWindowTitle(MAIN_WINDOW_TITLE);
    xrayWindowPtr->setWindowTitle(XRAY_WINDOW_TITLE);
    imageWindowPtr->setWindowTitle(IMAGE_WINDOW_TITLE);
}

// ======================================= [ MainWindow ] ==
// Window events
// =========================================================
void MainWindow::closeEvent(QCloseEvent *event){
    saveNote();
    Preferences::save();
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
    QString newPatientPath = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!newPatientPath.isEmpty()){
        QDir newPatientQDir(newPatientPath);
        
        ui->patientIDLabel->setText(newPatientQDir.dirName());
        saveNote();

        Preferences::setPatientID(newPatientQDir.dirName());
        Preferences::setPatientFolderPath(newPatientPath);
        Preferences::save();

        refreshNote();

        emit patientChangedSignal(newPatientPath);
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


// =========================================== [ Action ] ==
// Initialize open x-ray window action
// =========================================================
void MainWindow::initOpenXRayWindowAction(){
    QString iconPath(APP_FOLDER_PATH + QString("icons/xray_icon.png"));
    xrayAct = new QAction(QIcon( iconPath ), tr("X-ray window"), this);
    xrayAct->setStatusTip(tr("X-ray window"));
    connect(xrayAct, SIGNAL(triggered()), this, SLOT(on_xray_active()));

    ui->menuFile->addAction(xrayAct);
    ui->mainToolBar->addAction(xrayAct);
}

void MainWindow::on_xray_active(){
    if(xrayWindowPtr->isHidden()){
        xrayWindowPtr->show();
    }
    else{
        xrayWindowPtr->raise();
        xrayWindowPtr->activateWindow();
    }
}

// =========================================== [ Action ] ==
// Initialize open image window action
// =========================================================
void MainWindow::initOpenImageWindowAction(){
    QString iconPath(APP_FOLDER_PATH + QString("icons/image_icon.png"));
    imageAct = new QAction(QIcon( iconPath ), tr("Image window"), this);
    imageAct->setStatusTip(tr("Image window"));
    connect(imageAct, SIGNAL(triggered()), this, SLOT(on_image_active()));

    ui->menuFile->addAction(imageAct);
    ui->mainToolBar->addAction(imageAct);
}

void MainWindow::on_image_active(){
    if(imageWindowPtr->isHidden()){
        imageWindowPtr->show();
    }
    else{
        imageWindowPtr->raise();
        imageWindowPtr->activateWindow();
    }
}


// ============================================= [ Note ] ==
// Save note
// =========================================================
void MainWindow::saveNote(){
    QFile noteFile(Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getPatientID() + NOTE_FILE_SUFFIX_NAME);

    if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout << "Open note file for writing fail" << endl;
        return;
    }

    QString noteText = ui->noteTextEdit->toPlainText();
    QTextStream outStream(&noteFile);
    outStream << noteText;
    noteFile.close();
}

// ============================================= [ Note ] ==
// Refresh note
// =========================================================
void MainWindow::refreshNote(){
    ui->noteTextEdit->clear();

    QFile noteFile(Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getPatientID() + NOTE_FILE_SUFFIX_NAME);
    if(!noteFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        cout << "Read note file failed" << endl;
    }
    else{
        cout << "Read note file successfully" << endl;
        QTextStream inStream(&noteFile);
        while (!inStream.atEnd()) {
            ui->noteTextEdit->appendPlainText(inStream.readLine());
        }
    }
    noteFile.close();
}

// ====================================== [ Development ] ==
// Test Button
// =========================================================
void MainWindow::on_testButton_clicked(){

    // QDesktopServices::openUrl(QUrl("file:///Users/blue/aaa.pdf", QUrl::TolerantMode));
    // QDesktopServices::openUrl(QUrl("file:///Users/blue/Desktop/實數的建構.pdf", QUrl::TolerantMode));


    // QString filename = "/Users/blue/aaa.pdf";
    // Poppler::Document* document = Poppler::Document::load(filename);
    // if (!document || document->isLocked()) {
    //     // ... error message ....
    //     delete document;
    //     return;
    // }
    // delete document;
}




