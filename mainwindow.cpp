/*
There are several classes in my classification, like
[MainWindow]
[Action]
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
#include "messagedialog.h"


QString Preferences::homeFolderPath = DEFAULT_FOLDER_PATH;
QString Preferences::patientFolderPath = "";
QString Preferences::patientID = "";
QString Preferences::inStreamBuffer = "";
QString Preferences::xrayFolderName = DEFAULT_XRAY_FOLDER_NAME;
QString Preferences::imageFolderName = DEFAULT_IMAGE_FOLDER_NAME;


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

    // ======================================
    // Debug window
    // Remember toe delete the debugWindowPtr
    // ======================================
    // debugWindowPtr = new DebugWindow();
    // debugWindowPtr->move(0, SCREEN_HEIGHT * 3 / 2);
    // debugWindowPtr->show();

    // ==================
    // Initialize actions
    // ==================
    initOpenFolderAction();
    initOpenXRayWindowAction();
    initOpenImageWindowAction();
    initSettingAction();
    initSwitchToolBarVisibleAction();
    initFAQAction();


    // ==================
    // Initialize some UI
    // ==================
    ui->patientIDLabel->setAlignment(Qt::AlignCenter);
    ui->noteTextEdit->setPlaceholderText(NOTE_HINT);


    // ===============
    //   Connecting
    // ===============
    connect(this, SIGNAL(patientChangedSignal(QString)), xrayWindowPtr, SLOT(on_patientChanged(QString)));
    connect(this, SIGNAL(patientChangedSignal(QString)), imageWindowPtr, SLOT(on_patientChanged(QString)));


    // Load last patient data if it is readable
    QString xrayRootPath = Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getXrayFolderName();
    QString imageRootPath = Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getImageFolderName();
    bool isXRayRootPathExist = QDir(xrayRootPath).isReadable();
    bool isImageRootPathExist = QDir(imageRootPath).isReadable();
    
    if( !Preferences::getPatientID().isEmpty()
        && isXRayRootPathExist && isImageRootPathExist){
        ui->patientIDLabel->setText(Preferences::getPatientID());
        refreshNote();
        xrayWindowPtr->show();
        xrayAct->setEnabled(true);
        xrayAct->setChecked(true);
        imageWindowPtr->show();
        imageAct->setEnabled(true);
        imageAct->setChecked(true);
    }
    else{
        ui->patientIDLabel->setText("");
        ui->noteTextEdit->setEnabled(false);
        Preferences::setPatientFolderPath("");
        Preferences::setPatientID("");
        xrayAct->setEnabled(false);
        imageAct->setEnabled(false);
    }

}

MainWindow::~MainWindow(){
    delete ui;
    delete openFolderAct, settingAct, xrayAct, imageAct;
    delete xrayWindowPtr, imageWindowPtr, faqWindowPtr;
    // delete debugWindowPtr;
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
    xrayWindowPtr->resize(DEFAULT_XRAY_WINDOW_SIZE);
    // xrayWindowPtr->setFixedSize(DEFAULT_XRAY_WINDOW_SIZE);
    xrayWindowPtr->move(SCREEN_WIDTH/2 + 1, 0);

    imageWindowPtr = new ImageWindow();
    imageWindowPtr->resize(DEFAULT_IMAGE_WINDOW_SIZE);
    // imageWindowPtr->setFixedSize(DEFAULT_IMAGE_WINDOW_SIZE);
    imageWindowPtr->move(SCREEN_WIDTH/2 + 1, DEFAULT_XRAY_WINDOW_SIZE.height() * 1.2);

    // Setting titles
    this->setWindowTitle(MAIN_WINDOW_TITLE);
    if(Preferences::getPatientID().isEmpty()){
        xrayWindowPtr->setWindowTitle(XRAY_WINDOW_TITLE);
        imageWindowPtr->setWindowTitle(IMAGE_WINDOW_TITLE);
    }
    else{
        xrayWindowPtr->setWindowTitle(XRAY_WINDOW_TITLE + HYPHEN + Preferences::getPatientID());
        imageWindowPtr->setWindowTitle(IMAGE_WINDOW_TITLE + HYPHEN + Preferences::getPatientID());
    }

    // Initialize the FAQ window
    faqWindowPtr = NULL;

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
    QString iconPath(APP_FOLDER_PATH + OPEN_FOLDER_ICON_SUFFIX);
    openFolderAct = new QAction(QIcon( iconPath ), OPEN_FOLDER_TIP_TEXT, this);
    openFolderAct->setShortcuts(QKeySequence::Open);
    openFolderAct->setStatusTip(OPEN_FOLDER_TIP_TEXT);
    connect(openFolderAct, SIGNAL(triggered()), this, SLOT(on_openFolder_active()));

    ui->menuFile->addAction(openFolderAct);
    ui->mainToolBar->addAction(openFolderAct);
}

void MainWindow::on_openFolder_active(){
    // Open a file dialog and ask for a new directory
    QString newPatientPath = QFileDialog::getExistingDirectory(this,
        OPEN_FOLDER_TIP_TEXT, Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(newPatientPath.isEmpty())
        return;

    QString xrayRootPath = newPatientPath + QDir::separator() + Preferences::getXrayFolderName();
    QString imageRootPath = newPatientPath + QDir::separator() + Preferences::getImageFolderName();
    bool isXRayRootPathExist = QDir(xrayRootPath).isReadable();
    bool isImageRootPathExist = QDir(imageRootPath).isReadable();

    if(isXRayRootPathExist && isImageRootPathExist){
        saveNote();

        QDir newPatientQDir(newPatientPath);
        Preferences::setPatientID(newPatientQDir.dirName());
        Preferences::setPatientFolderPath(newPatientPath);
        Preferences::save();

        ui->noteTextEdit->setEnabled(true);
        refreshNote();
        ui->patientIDLabel->setText(Preferences::getPatientID());

        if(xrayWindowPtr->isHidden()){
            xrayWindowPtr->show();
            xrayAct->setChecked(true);
        }
        if(imageWindowPtr->isHidden()){
            imageWindowPtr->show();
            imageAct->setChecked(true);
        }

        emit patientChangedSignal(newPatientPath);
    }
    else if(!isXRayRootPathExist && isImageRootPathExist){
        MessageDialog mMessageDialog;
        mMessageDialog.setMessage(
            WRONG_XRAY_FOLDER_MESSAGE_1
            + QDir(newPatientPath).dirName()
            + WRONG_XRAY_FOLDER_MESSAGE_2
            + Preferences::getXrayFolderName()
            + WRONG_XRAY_FOLDER_MESSAGE_3
            + Preferences::getXrayFolderName()
            + WRONG_XRAY_FOLDER_MESSAGE_4);
        mMessageDialog.exec();
    }
    else if(isXRayRootPathExist && !isImageRootPathExist){
        MessageDialog mMessageDialog;
        mMessageDialog.setMessage(
            WRONG_IMAGE_FOLDER_MESSAGE_1
            + QDir(newPatientPath).dirName()
            + WRONG_IMAGE_FOLDER_MESSAGE_2
            + Preferences::getImageFolderName()
            + WRONG_IMAGE_FOLDER_MESSAGE_3
            + Preferences::getImageFolderName()
            + WRONG_IMAGE_FOLDER_MESSAGE_4);
        mMessageDialog.exec();
    }
    else{
        MessageDialog mMessageDialog;
        mMessageDialog.setMessage(
            WRONG_XRAY_IMAGE_FOLDER_MESSAGE_1
            + QDir(newPatientPath).dirName()
            + WRONG_XRAY_IMAGE_FOLDER_MESSAGE_2
            + Preferences::getXrayFolderName()
            + WRONG_XRAY_IMAGE_FOLDER_MESSAGE_3
            + Preferences::getImageFolderName()
            + WRONG_XRAY_IMAGE_FOLDER_MESSAGE_4
            + Preferences::getXrayFolderName()
            + WRONG_XRAY_IMAGE_FOLDER_MESSAGE_5
            + Preferences::getImageFolderName()
            + WRONG_XRAY_IMAGE_FOLDER_MESSAGE_6);
        mMessageDialog.exec();
    }
}

// =========================================== [ Action ] ==
// Initialize Setting Action
// =========================================================
void MainWindow::initSettingAction(){
    QString iconPath(APP_FOLDER_PATH + SETTING_ICON_SUFFIX);
    settingAct = new QAction(QIcon( iconPath ), SETTING_TIP_TEXT, this);
    settingAct->setStatusTip(SETTING_TIP_TEXT);
    settingAct->setShortcuts(QKeySequence::Preferences);
    connect(settingAct, SIGNAL(triggered()), this, SLOT(on_setting_active()));

    ui->menuHelp->addAction(settingAct);
    ui->mainToolBar->addAction(settingAct);
}

void MainWindow::on_setting_active(){
    SettingDialog mSettingDialog;
    mSettingDialog.setWindowTitle(SETTING_DIALOG_TITLE);
    mSettingDialog.setFixedSize(mSettingDialog.size());
    mSettingDialog.exec();
}


// =========================================== [ Action ] ==
// Initialize open x-ray window action
// =========================================================
void MainWindow::initOpenXRayWindowAction(){
    QString iconPath(APP_FOLDER_PATH + XRAY_WINDOW_ICON_SUFFIX);
    xrayAct = new QAction(QIcon( iconPath ), XRAY_WINDOW_TIP_TEXT, this);
    xrayAct->setStatusTip(XRAY_WINDOW_TIP_TEXT);
    connect(xrayAct, SIGNAL(triggered()), this, SLOT(on_xray_active()));

    xrayAct->setCheckable(true);

    ui->menuWindow->addAction(xrayAct);
    ui->mainToolBar->addAction(xrayAct);
}

void MainWindow::on_xray_active(){
    if(Preferences::getPatientID().isEmpty()){
        return;
    }

    xrayWindowPtr->setVisible(!xrayWindowPtr->isVisible());

    // if( !Preferences::getPatientID().isEmpty() && xrayWindowPtr->isHidden() ){
    //     xrayWindowPtr->show();
    //     xrayAct->setChecked(true);
    // }
    // else{
    //     xrayWindowPtr->raise();
    //     xrayWindowPtr->activateWindow();
    // }
}

// =========================================== [ Action ] ==
// Initialize open image window action
// =========================================================
void MainWindow::initOpenImageWindowAction(){
    QString iconPath(APP_FOLDER_PATH + IMAGE_WINDOW_ICON_SUFFIX);
    imageAct = new QAction(QIcon( iconPath ), IMAGE_WINDOW_TIP_TEXT, this);
    imageAct->setStatusTip(IMAGE_WINDOW_TIP_TEXT);
    connect(imageAct, SIGNAL(triggered()), this, SLOT(on_image_active()));

    imageAct->setCheckable(true);

    ui->menuWindow->addAction(imageAct);
    ui->mainToolBar->addAction(imageAct);
}

void MainWindow::on_image_active(){
    if( !Preferences::getPatientID().isEmpty() && imageWindowPtr->isHidden() ){
        imageWindowPtr->show();
        imageAct->setChecked(true);
    }
    else{
        imageWindowPtr->raise();
        imageWindowPtr->activateWindow();
    }
}


// =========================================== [ Action ] ==
// Show/Hide main toolbar
// =========================================================
void MainWindow::initSwitchToolBarVisibleAction(){
    switchToolBarVisibleAct = new QAction(SWITCH_TOOLBAR_VISIBLE_TIP_TEXT, this);
    switchToolBarVisibleAct->setStatusTip(SWITCH_TOOLBAR_VISIBLE_TIP_TEXT);
    connect(switchToolBarVisibleAct, SIGNAL(triggered()), this, SLOT(on_switch_toolbar_active()));

    switchToolBarVisibleAct->setCheckable(true);
    switchToolBarVisibleAct->setChecked(true);
    ui->menuWindow->addAction(switchToolBarVisibleAct);
}

void MainWindow::on_switch_toolbar_active(){
    ui->mainToolBar->setVisible(!ui->mainToolBar->isVisible());
}


// =========================================== [ Action ] ==
// Initialize FAQ/About action
// =========================================================
void MainWindow::initFAQAction(){
    QString iconPath(APP_FOLDER_PATH + FAQ_ICON_SUFFIX);
    faqAct = new QAction(QIcon( iconPath ), FAQ_TIP_TEXT, this);
    faqAct->setStatusTip(FAQ_TIP_TEXT);
    connect(faqAct, SIGNAL(triggered()), this, SLOT(on_faq_active()));

    ui->menuHelp->addAction(faqAct);
    ui->mainToolBar->addAction(faqAct);
}

void MainWindow::on_faq_active(){
    if(faqWindowPtr == NULL){
        faqWindowPtr = new FAQWindow();
        faqWindowPtr->setWindowTitle(FAQ_WINDOW_TITLE);
        faqWindowPtr->show();
    }
    else{
        if(faqWindowPtr->isHidden()){
            faqWindowPtr->show();
        }
        else{
            faqWindowPtr->raise();
            faqWindowPtr->activateWindow();
        }
    }
}


// ============================================= [ Note ] ==
// Save note
// =========================================================
void MainWindow::saveNote(){
    QFile noteFile(Preferences::getPatientFolderPath() + QDir::separator()
        + Preferences::getPatientID() + NOTE_FILE_SUFFIX_NAME);

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

    QFile noteFile(Preferences::getPatientFolderPath() + QDir::separator()
        + Preferences::getPatientID() + NOTE_FILE_SUFFIX_NAME);

    if(!noteFile.open(QIODevice::ReadOnly | QIODevice::Text) ){
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




