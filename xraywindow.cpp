#include "xraywindow.h"
#include "ui_xraywindow.h"

XRayWindow::XRayWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XRayWindow)
{
    ui->setupUi(this);
}

XRayWindow::~XRayWindow()
{
    delete ui;
}
