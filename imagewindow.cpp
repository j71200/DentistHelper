#include "imagewindow.h"
#include "ui_imagewindow.h"

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

    ui->scaleSlider->setMinimum(MIN_SCALE_RATIO);
    ui->scaleSlider->setMaximum(MAX_SCALE_RATIO);
    ui->scaleSlider->setSingleStep(SLIDER_SINGLE_STEP);
    ui->scaleLabel->setAlignment(Qt::AlignCenter);
    resetScaleTools();
    setScaleToolsVisible(false);


    // ===================
    // Initialize TreeView
    // ===================
    ui->treeView->setMaximumWidth(MAX_TREEVIEW_WIDTH);
    ui->scaleSlider->setMaximumWidth(MAX_TREEVIEW_WIDTH);
    changeTreeView(Preferences::getPatientFolderPath() + QDir::separator() + PHOTO_TO_PHOTO_PATH);

    // =====================
    // Connecting
    // =====================
    connect(ui->treeView, SIGNAL(fileChangedSignal(QString)), this, SLOT(on_fileChanged(QString)));


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
void ImageWindow::resizeEvent(QResizeEvent *event){
    loadImage(selectedFilePath);
    QWidget::resizeEvent(event);
}

// ========================================= [ TreeView ] ==
// Change the Directory of TreeView
// =========================================================
void ImageWindow::changeTreeView(QString dir){
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
void ImageWindow::on_patientChanged(QString newPatientFolderPath){
    changeTreeView(newPatientFolderPath + QDir::separator() + PHOTO_TO_PHOTO_PATH);

    resetImage();
    resetScaleTools();
    setScaleToolsVisible(false);
}

// ============================================ [ Image ] ==
// Load image into the label
// =========================================================
void ImageWindow::loadImage(QString imagePath){
    image = QPixmap(imagePath);
    if(image.isNull()){
        return;
    }
    
    imageSize = QSize(ui->scrollArea->width(), ui->scrollArea->height());
    imageSize *= FIT_IMAGE_SIZE_RATIO;
    image = image.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(image);

    resetScaleTools();
	setScaleToolsVisible(true);
}

// ============================================ [ Image ] ==
// Refresh image if folder changed
// =========================================================
void ImageWindow::on_fileChanged(QString newFilePath){
	selectedFilePath = newFilePath;
	loadImage(newFilePath);
	resetScaleTools();
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

void ImageWindow::resetScaleTools(){
	ui->scaleSlider->setValue(100);
    ui->scaleLabel->setText("100%");
}

void ImageWindow::setScaleToolsVisible(bool isVisible){
    ui->scaleSlider->setVisible(isVisible);
    ui->scaleLabel->setVisible(isVisible);
}
