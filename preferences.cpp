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

    static bool load(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        if (!preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            cout << "Read preference file failed" << endl;
            // Set the initial value
            homeFolderPath = DEFAULT_FOLDER_PATH;
            return false;
        }

        QTextStream inStream(&preferencesFile);
        int i = 0;
        while(!inStream.atEnd()) {
            switch(i){
                case 0:
                    homeFolderPath = inStream.readLine();
                    break;
                case 1:
                    patientFolderPath = inStream.readLine();
                    break;
                default:
                    inStreamBuffer = inStream.readLine();
                    break;
            }
            i++;
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
        outStream << homeFolderPath << endl
                  << patientFolderPath << endl;
        preferencesFile.close();
    }


    // ========================================= [ TreeView ] ==
    // Home Folder Path
    // =========================================================
    static void setHomeFolderPath(QString newHomeFolderPath){
        homeFolderPath = newHomeFolderPath;
    }
    static QString getHomeFolderPath(){
        return homeFolderPath;
    }

    // ========================================= [ TreeView ] ==
    // Last Patient Folder Path
    // =========================================================
    static void setPatientFolderPath(QString newPatientFolderPath){
        patientFolderPath = newPatientFolderPath;
    }
    static QString getPatientFolderPath(){
        return patientFolderPath;
    }
    

private:
    static QString homeFolderPath, patientFolderPath;
    static QString inStreamBuffer;
};

#endif // PREFERENCES_CPP
