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

    // ============================================== [ I/O ] ==
    // Load and Save User's Prefeerences
    // =========================================================
    static bool load(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        if (!preferencesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            cout << "Read preference file failed" << endl;
            return false;
        }

        QTextStream inStream(&preferencesFile);
        int i = 0;
        while(!inStream.atEnd() && i < PREFERENCE_FILE_WARNING_LINES.size()){
            inStream.readLine();
            i++;
        }

        i = -1;
        QString line;
        while(!inStream.atEnd()) {
            i++;
            line = inStream.readLine();
            if(line.isEmpty())
                continue;

            switch(i){
                case 0:
                    homeFolderPath = line;
                    break;
                case 1:
                    patientFolderPath = line;
                    break;
                case 2:
                    patientID = line;
                    break;
                case 3:
                    xrayFolderName = line;
                    break;
                case 4:
                    imageFolderName = line;
                    break;
                case 5:
                    isAutoOpenWindows = line;
                    break;
                default:
                    inStreamBuffer = line;
                    break;
            }
        }
        preferencesFile.close();
        return true;
    }

    static void save(){
        QFile preferencesFile(PREFERENCES_FILE_PATH);
        preferencesFile.setPermissions(QFileDevice::WriteOwner);
        if (!preferencesFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            cout << "Write preference file failed" << endl;
            return;
        }
        
        QTextStream outStream(&preferencesFile);
        for(int i = 0; i < PREFERENCE_FILE_WARNING_LINES.size(); i++){
            outStream << PREFERENCE_FILE_WARNING_LINES.at(i);
        }
        outStream << homeFolderPath << endl
                  << patientFolderPath << endl
                  << patientID << endl
                  << xrayFolderName << endl
                  << imageFolderName << endl
                  << isAutoOpenWindows << endl;
        preferencesFile.setPermissions(QFileDevice::ReadOwner);
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

    // ======================================= [ MainWindow ] ==
    // Last Patient Folder Path
    // =========================================================
    static void setPatientID(QString newPatientID){
        patientID = newPatientID;
    }
    static QString getPatientID(){
        return patientID;
    }

    // ========================================== [ Setting ] ==
    // X-ray folder name
    // =========================================================
    static void setXrayFolderName(QString newFolderName){
        xrayFolderName = newFolderName;
    }
    static QString getXrayFolderName(){
        return xrayFolderName;
    }

    // ========================================== [ Setting ] ==
    // Image folder name
    // =========================================================
    static void setImageFolderName(QString newFolderName){
        imageFolderName = newFolderName;
    }
    static QString getImageFolderName(){
        return imageFolderName;
    }

    // ========================================== [ Setting ] ==
    // Is auto-open x-ray window and image window
    // =========================================================
    static void setIsAutoOpenWindows(bool isAutoOpen){
        if(isAutoOpen)
            isAutoOpenWindows = PREFERENCE_FILE_AUTO_OPEN_TEXT;
        else
            isAutoOpenWindows = PREFERENCE_FILE_NOT_AUTO_OPEN_TEXT;
    }
    static bool getIsAutoOpenWindows(){
        if(isAutoOpenWindows == PREFERENCE_FILE_AUTO_OPEN_TEXT)
            return true;
        else
            false;
    }


private:
    static QString homeFolderPath, patientFolderPath, patientID;
    static QString inStreamBuffer;
    static QString xrayFolderName, imageFolderName;
    static QString isAutoOpenWindows;
};

#endif // PREFERENCES_CPP
