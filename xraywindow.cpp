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
    xrayLabel = new QLabel;


    // ======================
    // Initialize image block
    // ======================
    xrayLabel->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(xrayLabel);

    ui->scaleSlider->setMinimum(10);
    ui->scaleSlider->setMaximum(300);
    ui->scaleSlider->setSingleStep(10);
    ui->scaleLabel->setAlignment(Qt::AlignCenter);
    resetScaleTools();
    setScaleToolsVisible(false);

    // ===================
    // Initialize TreeView
    // ===================
    ui->treeView->setMaximumWidth(MAX_TREEVIEW_WIDTH);
    ui->scaleSlider->setMaximumWidth(MAX_TREEVIEW_WIDTH);
    changeTreeView(Preferences::getPatientFolderPath() + QDir::separator() + XRAY_TO_XRAY_PATH);

    // =====================
    // Connecting
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
    setImageSize(event->size());
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

// ========================================= [ TreeView ] ==
// Refresh the TreeView when patient changed
// =========================================================
void XRayWindow::on_patientChanged(QString newPatientFolderPath){
    changeTreeView(newPatientFolderPath + QDir::separator() + XRAY_TO_XRAY_PATH);

    resetImage();
    resetScaleTools();
    setScaleToolsVisible(false);
}


// ============================================ [ Image ] ==
// Load image into the label
// =========================================================
void XRayWindow::loadImage(QString imagePath){
    xrayImage = QPixmap(imagePath);
    if(xrayImage.isNull()){
        return;
    }
    
    xrayImageSize = QSize(ui->scrollArea->width(), ui->scrollArea->height());
    xrayImageSize *= FIT_IMAGE_SIZE_RATIO;
    xrayImage = xrayImage.scaled(xrayImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    xrayLabel->setPixmap(xrayImage);
}

// ============================================ [ Image ] ==
// Refresh image if folder changed
// =========================================================
void XRayWindow::on_fileChanged(QString newFilePath){
	selectedFilePath = newFilePath;
	loadImage(newFilePath);
    resetScaleTools();
    setScaleToolsVisible(true);
}

// ============================================ [ Image ] ==
// Image ratioSlider slot
// =========================================================
void XRayWindow::on_scaleSlider_valueChanged(int value){
    if(xrayImage.isNull())
        return;

    QString newRatioText = QString::number(value) + "%";
    ui->scaleLabel->setText(newRatioText);

    QSize newScaledSize = xrayImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = xrayImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    xrayLabel->setPixmap(newScaledPixmap);
}

// ============================================ [ Image ] ==
// set image size
// =========================================================
void XRayWindow::setImageSize(QSize newImageSize){
    if(xrayImage.isNull())
        return;

    // QString newRatioText = QString::number(value) + "%";
    // ui->scaleLabel->setText(newRatioText);

    // QSize newScaledSize = xrayImageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = xrayImage.scaled(newImageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    xrayLabel->setPixmap(newScaledPixmap);
}


// ============================================ [ Image ] ==
// Reset/Set image block
// =========================================================
void XRayWindow::resetImage(){
    xrayImage = QPixmap();
    xrayLabel->clear();
}

void XRayWindow::resetScaleTools(){
	ui->scaleSlider->setValue(100);
    ui->scaleLabel->setText("100%");
}

void XRayWindow::setScaleToolsVisible(bool isVisible){
    ui->scaleSlider->setVisible(isVisible);
    ui->scaleLabel->setVisible(isVisible);
}




