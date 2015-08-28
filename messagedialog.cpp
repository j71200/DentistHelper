#include "messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
}

MessageDialog::~MessageDialog(){
    delete ui;
}

void MessageDialog::setMessage(QString message){
	ui->messageLabel->setText(message);
}
void MessageDialog::on_okButton_clicked(){
    this->accept();
}
