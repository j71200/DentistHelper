#include "faqwindow.h"
#include "ui_faqwindow.h"
#include "default_setting.h"
#include <QKeyEvent>

FAQWindow::FAQWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAQWindow)
{
    ui->setupUi(this);

    // Initialize window
    this->setFixedSize(this->size());

    // Initialize tab
    ui->tabWidget->setTabText(0, FAQ_TAB_TITLE);
    ui->tabWidget->setTabText(1, ABOUT_TAB_TITLE);
    ui->tabWidget->setCurrentIndex(0);

    // Initialize button
    ui->okButton->setText(OK_TEXT);
    ui->okButton->setAutoDefault(true);
    ui->okButton->setFocusPolicy(Qt::StrongFocus);

    // Initialize FAQ
    ui->faqTextBrowser->setFocusPolicy(Qt::NoFocus);
    ui->aboutTextBrowser->setFocusPolicy(Qt::NoFocus);
}

FAQWindow::~FAQWindow()
{
    delete ui;
}

void FAQWindow::on_okButton_clicked(){
    this->close();
}

void FAQWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Escape:
            this->close();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
    }
}
