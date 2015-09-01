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
            folderPath = DEFAULT_FOLDER_PATH;
        }
    }
    ~Preferences(){
    }

    static void setFolderPath(QString newFolderPath){
        folderPath = newFolderPath;
    }

    static QString getFolderPath(){
        return folderPath;
    }

    static bool load(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        if (!preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QTextStream inStream(&preferencesFile);
        while (!inStream.atEnd()) {
            QString line = inStream.readLine();
            folderPath = line;
        }
        preferencesFile.close();
        return true;
    }

    static void save(){
        ofstream fout(PREFERENCES_FILE_PATH.toStdString().c_str());
        if(!fout)
            return;

        // Write folder path
        fout << folderPath.toStdString();

        fout.close();
    }

    static QString getInitFolderPath(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        bool isPrefFileExist = preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text);

        if(isPrefFileExist == true){
            QTextStream inStream(&preferencesFile);
            while (!inStream.atEnd()) {
                QString line = inStream.readLine();
                return line;
            }
        }
        else{
            cout << "Preferences file do not exist." << endl;
            return DEFAULT_FOLDER_PATH;
        }
    }

private:
    static QString folderPath;
};

#endif // PREFERENCES_CPP
