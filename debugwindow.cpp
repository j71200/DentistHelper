#include "debugwindow.h"
#include "ui_debugwindow.h"
#include "preferences.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Debug Window");

    ui->variableTextBrowser->setFocusPolicy(Qt::NoFocus);
    ui->updateButton->setAutoDefault(true);
    ui->updateButton->setFocusPolicy(Qt::StrongFocus);



    QPixmap pp = QPixmap(APP_FOLDER_PATH + OPEN_FOLDER_ICON_SUFFIX);
    ui->label->setOriginalPixmap(pp);



    updateVariables();
}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::updateVariables(){
    QString variableValues = "";

    variableValues += QString("=============\n")
    			   +  QString("Preferences::\n")
    			   +  QString("=============\n")
				   +  "getHomeFolderPath():\n" + Preferences::getHomeFolderPath() + "\n--\n"
    	           +  "getPatientFolderPath():\n" + Preferences::getPatientFolderPath() + "\n--\n"
    	           +  "getPatientID():\n" + Preferences::getPatientID() + "\n--\n"
    	           +  "getXrayFolderName():\n" + Preferences::getXrayFolderName() + "\n--\n"
    	           +  "getImageFolderName():\n" + Preferences::getImageFolderName() + "\n--\n";
    	           

    ui->variableTextBrowser->setText(variableValues);
}

void DebugWindow::on_updateButton_clicked(){
	updateVariables();
}

//void DebugWindow::on_openDebugWindow
