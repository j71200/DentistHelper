#include "faq.h"
#include "ui_faq.h"

FAQ::FAQ(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAQ)
{
    ui->setupUi(this);
}

FAQ::~FAQ()
{
    delete ui;
}
