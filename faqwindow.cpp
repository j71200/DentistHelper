#include "faqwindow.h"
#include "ui_faqwindow.h"

FAQWindow::FAQWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAQWindow)
{
    ui->setupUi(this);
}

FAQWindow::~FAQWindow()
{
    delete ui;
}
