#include "xraywindow.h"
#include "ui_xraywindow.h"
#include <QLabel>
#include "preferences.h"
#include <QDir>
#include "default_setting.h"

XRayWindow::XRayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XRayWindow)
{
    ui->setupUi(this);

	// =====================
    // Initialize parameters
    // =====================
    model = new QFileSystemModel;

    // ======================
    // Initialize image block
    // ======================
    xrayLabel = new QLabel;
    xrayLabel->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(xrayLabel);


    // =====================
    //      TreeView
    // =====================
    changeTreeView(Preferences::getPatientFolderPath() + QDir::separator() + XRAY_TO_XRAY_PATH);

    // =====================
    //     Connecting
    // =====================
    connect(ui->treeView, SIGNAL(fileChangedSignal(QString)), this, SLOT(on_fileChanged(QString)));



}

XRayWindow::~XRayWindow()
{
    delete ui;
    delete model;
    delete xrayLabel;
}


// =========================================== [ Window ] ==
// Window Events
// =========================================================
void XRayWindow::resizeEvent(QResizeEvent *event){
    loadImage(selectedFilePath);
    QWidget::resizeEvent(event);
}

// ========================================= [ TreeView ] ==
// Change the Directory of TreeView
// =========================================================
void XRayWindow::changeTreeView(QString dir){
    if(dir.isEmpty())
        return;

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

// ============================================ [ Image ] ==
// Load image into the label
// =========================================================
void XRayWindow::loadImage(QString imagePath){
    xrayImage = QPixmap(imagePath);
    if(xrayImage.isNull())
        return;

    xrayImageSize = QSize(ui->scrollArea->width(), ui->scrollArea->height());
    xrayImage = xrayImage.scaled(xrayImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    xrayLabel->setPixmap(xrayImage);
}

// ============================================ [ Image ] ==
// Refresh image if folder changed
// =========================================================
void XRayWindow::on_fileChanged(QString newFilePath){
	selectedFilePath = newFilePath;
	loadImage(newFilePath);
}


