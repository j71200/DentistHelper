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
    //   Initialize UI
    // ==================
    ui->patientIDLabel->setAlignment(Qt::AlignCenter);
    ui->patientIDLabel->setText("");  // TODO Preference

    // ==================
    // Initialize actions
    // ==================
    initOpenFolderAction();
    initSettingAction();


    // =================================
    // Initialize patient label and note
    // =================================
    ui->noteTextEdit->setPlaceholderText(NOTE_HINT);
    ui->patientIDLabel->setText(Preferences::getPatientID());


    // ===============
    //   Connecting
    // ===============
    connect(this, SIGNAL(patientChangedSignal(QString)), xrayWindowPtr, SLOT(on_patientChanged(QString)));
    connect(this, SIGNAL(patientChangedSignal(QString)), imageWindowPtr, SLOT(on_patientChanged(QString)));

}

MainWindow::~MainWindow(){
    delete ui;
    delete xrayWindowPtr;
    delete imageWindowPtr;
}


// =========================================== [ MainWindow ] ==
// Initilize windows
// =========================================================
void MainWindow::initWindows(){
    QRect rec = QApplication::desktop()->screenGeometry();

    const int SCREEN_WIDTH = rec.width();
    const int SCREEN_HEIGHT = rec.height();

    const QSize DEFAULT_XRAY_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 );
    const QSize DEFAULT_IMAGE_WINDOW_SIZE = QSize( SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 );

    xrayWindowPtr = new XRayWindow();
    xrayWindowPtr->show();
    xrayWindowPtr->resize(DEFAULT_XRAY_WINDOW_SIZE);
    // xrayWindowPtr->setFixedSize(DEFAULT_XRAY_WINDOW_SIZE);
    xrayWindowPtr->move(SCREEN_WIDTH/2 + 1, 0);

    imageWindowPtr = new ImageWindow();
    imageWindowPtr->show();
    imageWindowPtr->resize(DEFAULT_IMAGE_WINDOW_SIZE);
    // imageWindowPtr->setFixedSize(DEFAULT_IMAGE_WINDOW_SIZE);
    imageWindowPtr->move(SCREEN_WIDTH/2 + 1, DEFAULT_XRAY_WINDOW_SIZE.height() + 1);
}

// =========================================== [ MainWindow ] ==
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
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), Preferences::getHomeFolderPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){
        QDir mQDir(dir);
        ui->patientIDLabel->setText(mQDir.dirName());
        emit patientChangedSignal(dir);
        Preferences::setPatientFolderPath(dir);
        Preferences::save();
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


// ============================================= [ Note ] ==
// Refresh Note Content if Folder Changed
// =========================================================
// void MainWindow::on_folderChanged(QString newFolderPath, QString newFolderName){
//     saveNote();

//     currFolderPath = newFolderPath;
//     currFolderName = newFolderName;

//     QString noteFilePath = newFolderPath + QDir::separator() + newFolderName + NOTE_FILE_SUFFIX_NAME;

//     QFile noteFile(noteFilePath);
//     if(!noteFile.open(QIODevice::ReadOnly | QIODevice::Text)){
//         cout << "Read note file failed" << endl;
//     }
//     else{
//         cout << "Read note file successfully" << endl;
//         QTextStream inStream(&noteFile);
//         ui->noteTextEdit->clear();
//         while (!inStream.atEnd()) {
//             ui->noteTextEdit->appendPlainText(inStream.readLine());
//         }
//     }
//     noteFile.close();
// }

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



//    QWindow xRayWindow;
//    QWindow imageWindow;


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




