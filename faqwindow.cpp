#include "faqwindow.h"
#include "ui_faqwindow.h"
#include "default_setting.h"

FAQWindow::FAQWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAQWindow)
{
    ui->setupUi(this);

    // Initialize tab
    ui->tabWidget->setTabText(0, FAQ_TAB_TITLE);
    ui->tabWidget->setTabText(1, ABOUT_TAB_TITLE);
    ui->tabWidget->setCurrentIndex(0);

    // Initialize button
    ui->okButton->setText(OK_TEXT);
}

FAQWindow::~FAQWindow()
{
    delete ui;
}

void FAQWindow::on_okButton_clicked(){
    this->close();
}
