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

    // ======================
    // Initialize image tools
    // ======================
    ui->scaleSlider->setMinimum(MIN_SCALE_RATIO);
    ui->scaleSlider->setMaximum(MAX_SCALE_RATIO);
    ui->scaleSlider->setSingleStep(SLIDER_SINGLE_STEP);
    ui->scaleLabel->setAlignment(Qt::AlignCenter);
    ui->fitWindowSizeButton->setText(FIT_WINDOW_TEXT);
    setScaleTools(0);

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
// void XRayWindow::resizeEvent(QResizeEvent *event){
//     // assignImageSize(event->size());
//     QWidget::resizeEvent(event);
// }

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
    setScaleTools(0);
}


// ============================================ [ Image ] ==
// Load image into the label
// =========================================================
void XRayWindow::loadImage(QString imagePath){
    xrayImage = QPixmap(imagePath);
    if(xrayImage.isNull()){
        return;
    }

    int fitScaleRatio = calculateFitScaleRatio();
    if(ui->scaleSlider->value() == fitScaleRatio){  // If you don't need to set the scale slider
        QSize newScaledSize = xrayImageSize * (fitScaleRatio / 100.0);
        QPixmap newScaledPixmap = xrayImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::FastTransformation);
        xrayLabel->setPixmap(newScaledPixmap);
    }
    else{
        setScaleTools(fitScaleRatio);
    }
}


// ============================================ [ Image ] ==
// Calculate the fit scale ratio
// =========================================================
int XRayWindow::calculateFitScaleRatio(){
    if(xrayImage.isNull()){
        return 0;
    }

    xrayImageSize = xrayImage.size();
    QSize scrollAreaSize = ui->scrollArea->size();
    scrollAreaSize *= FIT_IMAGE_SIZE_RATIO;

    qreal scrollAreaHWRatio = scrollAreaSize.height() / (qreal) scrollAreaSize.width();
    qreal xrayImageHWRatio = xrayImageSize.height() / (qreal) xrayImageSize.width();

    int fitScaleRatio;
    if( xrayImageHWRatio > scrollAreaHWRatio )
        fitScaleRatio = 100 * scrollAreaSize.height() / xrayImageSize.height();
    else
        fitScaleRatio = 100 * scrollAreaSize.width() / xrayImageSize.width();
    return fitScaleRatio;
}


// ============================================ [ Image ] ==
// Refresh image if folder changed
// =========================================================
void XRayWindow::on_fileChanged(QString newFilePath){
	selectedFilePath = newFilePath;
	loadImage(newFilePath);
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
    newScaledPixmap = xrayImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    xrayLabel->setPixmap(newScaledPixmap);
}


// ============================================ [ Image ] ==
// Reset image block
// =========================================================
void XRayWindow::resetImage(){
    xrayImage = QPixmap();
    xrayLabel->clear();
}


// ============================================ [ Image ] ==
// Set image scale tools
// Let the parameter "value" be 0, the tools will diappear
// =========================================================
void XRayWindow::setScaleTools(int value){
    if(value > 0){
        QString newRatioText = QString::number(value) + "%";
        ui->scaleSlider->setValue(value);
        ui->scaleLabel->setText(newRatioText);

        ui->scaleSlider->setVisible(true);
        ui->scaleLabel->setVisible(true);
        ui->fitWindowSizeButton->setVisible(true);
    }
    else{
        ui->scaleSlider->setVisible(false);
        ui->scaleLabel->setVisible(false);
        ui->fitWindowSizeButton->setVisible(false);
    }
}


// ============================================ [ Image ] ==
// Fit windows size tool
// =========================================================
void XRayWindow::on_fitWindowSizeButton_clicked(){
    loadImage(selectedFilePath);
}

void XRayWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Space:
            loadImage(selectedFilePath);
            break;
        default:
            break;
    }
    QWidget::keyPressEvent(event);
}



