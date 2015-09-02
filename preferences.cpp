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
        if (!preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            cout << "Read preference file failed" << endl;
            // Set the initial value
            folderPath = DEFAULT_FOLDER_PATH;
            return false;
        }

        QTextStream inStream(&preferencesFile);
        while (!inStream.atEnd()) {
            QString line = inStream.readLine();
            folderPath = line;
        }
        preferencesFile.close();
        return true;
    }

    static void save(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        if (!preferencesFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            cout << "Write preference file failed" << endl;
            return;
        }
        QTextStream outStream(&preferencesFile);
        outStream << folderPath << endl;
        preferencesFile.close();
    }

    // static QString getInitFolderPath(){
    //     QFile preferencesFile(PREFERENCES_FILE_PATH);
    //     bool isPrefFileExist = preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text);

    //     if(isPrefFileExist == true){
    //         QTextStream inStream(&preferencesFile);
    //         while (!inStream.atEnd()) {
    //             QString line = inStream.readLine();
    //             return line;
    //         }
    //     }
    //     else{
    //         cout << "Preferences file do not exist." << endl;
    //         return DEFAULT_FOLDER_PATH;
    //     }
    // }

private:
    static QStringList 
    // static QString folderPath;
};

#endif // PREFERENCES_CPP
