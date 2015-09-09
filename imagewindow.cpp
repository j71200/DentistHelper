#include "imagewindow.h"
#include "ui_imagewindow.h"
#include <QLabel>
#include "preferences.h"
#include <QDir>
#include "default_setting.h"
#include "messagedialog.h"

ImageWindow::ImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWindow)
{
    ui->setupUi(this);

	// =====================
    // Initialize parameters
    // =====================
    model = new QFileSystemModel;
    imageLabel = new QLabel;


    // ======================
    // Initialize image block
    // ======================
    imageLabel->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(imageLabel);

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
    changeTreeView(Preferences::getPatientFolderPath() + QDir::separator() + Preferences::getImageFolderName());

    // =====================
    // Connecting
    // =====================
    connect(ui->treeView, SIGNAL(fileChangedSignal(QString)), this, SLOT(on_fileChanged(QString)));
    connect(ui->treeView, SIGNAL(tvSpacePressedSignal()), this, SLOT(on_tvSpacePressed()));

}

ImageWindow::~ImageWindow()
{
    delete ui;
    delete model;
    delete imageLabel;
}


// =========================================== [ Window ] ==
// Window Events
// =========================================================
// void ImageWindow::resizeEvent(QResizeEvent *event){
//     loadImage(selectedFilePath);
//     QWidget::resizeEvent(event);
// }


// =========================================== [ Window ] ==
// Window key press event
// =========================================================
void ImageWindow::keyPressEvent(QKeyEvent *event){
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
void ImageWindow::changeTreeView(QString rootPath){
    if(rootPath.isEmpty())
        return;

    // if(!QDir(rootPath).isReadable()){
    //     MessageDialog mMessageDialog;
    //     mMessageDialog.setWindowTitle(MESSAGE_DIALOG_TITLE);
    //     mMessageDialog.setMessage(WRONG_IMAGE_FOLDER_MESSAGE);
    //     mMessageDialog.setFixedSize(mMessageDialog.size());
    //     mMessageDialog.exec();
    // }

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
void ImageWindow::on_patientChanged(QString newPatientFolderPath){
    this->setWindowTitle(IMAGE_WINDOW_TITLE + HYPHEN + Preferences::getPatientID());

    changeTreeView(newPatientFolderPath + QDir::separator() + Preferences::getImageFolderName());

    resetImage();
    setScaleTools(0);
}


// ============================================ [ Image ] ==
// Load image into the label
// =========================================================
void ImageWindow::loadImage(QString imagePath){
    image = QPixmap(imagePath);
    if(image.isNull()){
        return;
    }

    int fitScaleRatio = calculateFitScaleRatio();
    if(ui->scaleSlider->value() == fitScaleRatio){  // If you don't need to set the scale slider
        QSize newScaledSize = imageSize * (fitScaleRatio / 100.0);
        QPixmap newScaledPixmap = image.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::FastTransformation);
        imageLabel->setPixmap(newScaledPixmap);
    }
    else{
        setScaleTools(fitScaleRatio);
    }
}


// ============================================ [ Image ] ==
// Calculate the fit scale ratio
// =========================================================
int ImageWindow::calculateFitScaleRatio(){
    if(image.isNull()){
        return 0;
    }

    imageSize = image.size();
    QSize scrollAreaSize = ui->scrollArea->size();
    scrollAreaSize *= FIT_IMAGE_SIZE_RATIO;

    qreal scrollAreaHWRatio = scrollAreaSize.height() / (qreal) scrollAreaSize.width();
    qreal imageHWRatio = imageSize.height() / (qreal) imageSize.width();

    int fitScaleRatio;
    if( imageHWRatio > scrollAreaHWRatio )
        fitScaleRatio = 100 * scrollAreaSize.height() / imageSize.height();
    else
        fitScaleRatio = 100 * scrollAreaSize.width() / imageSize.width();
    return fitScaleRatio;
}


// ============================================ [ Image ] ==
// Refresh image if folder changed
// =========================================================
void ImageWindow::on_fileChanged(QString newFilePath){
	selectedFilePath = newFilePath;
	loadImage(newFilePath);
}


// ============================================ [ Image ] ==
// Key pressed in TreeView
// =========================================================
void ImageWindow::on_tvSpacePressed(){
    loadImage(selectedFilePath);
}


// ============================================ [ Image ] ==
// Image ratioSlider slot
// =========================================================
void ImageWindow::on_scaleSlider_valueChanged(int value){
    if(image.isNull())
        return;

    QString newRatioText = QString::number(value) + "%";
    ui->scaleLabel->setText(newRatioText);

    QSize newScaledSize = imageSize * (value / 100.0);
    QPixmap newScaledPixmap;
    newScaledPixmap = image.scaled(newScaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(newScaledPixmap);
}

// ============================================ [ Image ] ==
// Reset/Set image block
// =========================================================
void ImageWindow::resetImage(){
    image = QPixmap();
    imageLabel->clear();
}

// ============================================ [ Image ] ==
// Set image scale tools
// Let the parameter "value" be 0, the tools will diappear
// =========================================================
void ImageWindow::setScaleTools(int value){
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
void ImageWindow::on_fitWindowSizeButton_clicked(){
    loadImage(selectedFilePath);
}


