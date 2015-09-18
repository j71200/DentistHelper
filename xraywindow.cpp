#include "xraywindow.h"
#include "ui_xraywindow.h"
#include <QLabel>
#include "preferences.h"
#include <QDir>
#include "default_setting.h"
#include "messagedialog.h"

XRayWindow::XRayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XRayWindow)
{
    ui->setupUi(this);

    // =====================
    // Initialize parameters
    // =====================
    model = new QFileSystemModel;
    xrayLabel = new CustomImageLabel;
    scaleImageWhenSliding = true;


    // =================
    // Initialize layout
    // =================
    ui->treeView->setMaximumWidth(MAX_TREEVIEW_WIDTH);
    ui->scaleSlider->setMaximumWidth(MAX_TREEVIEW_WIDTH);


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
    if(Preferences::getPatientID().isEmpty())
        ui->treeView->setEnabled(false);
    else
        changeTreeView(Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getXrayFolderName());

    // =====================
    // Connecting
    // =====================
    connect(ui->treeView, SIGNAL(fileChangedSignal(QString)), this, SLOT(on_fileChanged(QString)));
    connect(ui->treeView, SIGNAL(tvSpacePressedSignal()), this, SLOT(on_tvSpacePressed()));
    connect(ui->scrollArea, SIGNAL(doubleClickeScrollAreaSignal()), this, SLOT(on_scrollAreaDoubleClicked()));

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
void XRayWindow::closeEvent(QCloseEvent *event){
    emit xrayWindowClosedSignal();
    QWidget::closeEvent(event);
}


// =========================================== [ Window ] ==
// Window key press event
// =========================================================
void XRayWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Space:
            loadImage(selectedFilePath);
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
    }
}


// ========================================= [ TreeView ] ==
// Change the Directory of TreeView
// =========================================================
void XRayWindow::changeTreeView(QString rootPath){
    if(rootPath.isEmpty())
        return;
    
    // Set file system model
    model->setRootPath(rootPath);
    model->setNameFilters(READABLE_IMAGE_LIST);
    model->setNameFilterDisables(false);
    ui->treeView->setModel(model);
    
    // Set the treeView so that it will only show particular folder
    ui->treeView->setRootIndex(model->index(rootPath));
    // Hide the useless columns, like file size, kind and date modified
    for(int i = 1; i < model->columnCount(); i++){
        ui->treeView->setColumnHidden(i, true);
    }
}

// ========================================= [ TreeView ] ==
// Refresh the TreeView when patient changed
// =========================================================
void XRayWindow::on_patientChanged(QString newPatientFolderPath){
    this->setWindowTitle(XRAY_WINDOW_TITLE + HYPHEN + Preferences::getPatientID());

    ui->treeView->setEnabled(true);
    changeTreeView(newPatientFolderPath + QDir::separator() + Preferences::getXrayFolderName());

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

    xrayLabel->setOriginalPixmap(xrayImage);


    QFile file(imagePath);
    cout << "name: " << file.fileName().toStdString() << endl;
    cout << "origin file size: " << (file.size()/100000) / 10.0 << "MB" << endl;
    cout << "origin image size: " << xrayImage.width() << " x " << xrayImage.height() << " x " << xrayImage.depth() << endl;

    int fitScalePercentage = calculateFitScaleRatio();
    xrayLabel->scaleImage(fitScalePercentage);
    
    // scaleImageWhenSliding = false;
    // setScaleTools(fitScalePercentage);
    // scaleImageWhenSliding = true;


    // if(ui->scaleSlider->value() == fitScaleRatio){  // If you don't need to set the scale slider
    //     // QSize newScaledSize = xrayImageSize * (fitScaleRatio / 100.0);
    //     // QPixmap newScaledPixmap = xrayImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    //     // xrayLabel->setOriginalPixmap(newScaledPixmap);
    //     xrayLabel->scaleImage(fitScaleRatio);
    // }
    // else{
    //     setScaleTools(fitScaleRatio);
    // }
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
// Key pressed in TreeView
// =========================================================
void XRayWindow::on_tvSpacePressed(){
    loadImage(selectedFilePath);
}


// ============================================ [ Image ] ==
// Image ratioSlider slot
// =========================================================
void XRayWindow::on_scaleSlider_valueChanged(int value){
    if(xrayImage.isNull())
        return;

    QString newRatioText = QString::number(value) + "%";
    ui->scaleLabel->setText(newRatioText);

    if(scaleImageWhenSliding)
        xrayLabel->scaleImage(value / 100.0);
    

    // QSize newScaledSize = xrayImageSize * (value / 100.0);
    // QPixmap newScaledPixmap;
    // newScaledPixmap = xrayImage.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    // xrayLabel->setOriginalPixmap(newScaledPixmap);
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
        ui->scaleSlider->setValue(value);
        QString newRatioText = QString::number(ui->scaleSlider->value()) + "%";
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


// ============================================ [ Image ] ==
// Fit windows size tool when user double click scroll area
// =========================================================
void XRayWindow::on_scrollAreaDoubleClicked(){
    if(this->windowState() == Qt::WindowMaximized)
        this->setWindowState(Qt::WindowNoState);
    else
        this->setWindowState(Qt::WindowMaximized);

    loadImage(selectedFilePath);

}




