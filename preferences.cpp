#ifndef PREFERENCES_CPP
#define PREFERENCES_CPP

#include <QString>
#include <iostream>
#include <fstream>
#include "default_setting.h"
#include <QTextStream>
#include <QFile>

using namespace std;

class Preferences{
public:
    Preferences(){
        bool isLoadingSuccessful = load();
        if( !isLoadingSuccessful ){
            // Load fail then use the default setting
            folderPath = "/Users/blue/";
        }
    }
    ~Preferences(){
    }

    void setFolderPath(QString newFolderPath){
        folderPath = newFolderPath;
    }

    QString getFolderPath(){
        return folderPath;
    }

    bool load(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        if (!preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QTextStream inStream(&preferencesFile);
        while (!inStream.atEnd()) {
            QString line = inStream.readLine();
            folderPath = line;
        }
        return true;
    }

    void save(){
        ofstream fout("/Users/blue/QtWorkspace/firstQt/Output/my_preferences.txt");
        if(!fout)
            return;

        // Write folder path
        fout << folderPath.toStdString();

        fout.close();
    }

private:
    QString folderPath;  // static QString folderPath;
    // static int myBir;
};

// int Preferences::myBir = 1108;

#endif // PREFERENCES_CPP
