// this function will control the ini read/write functions
#include "inifunctions.h"

IniFunctions::IniFunctions() {
    IniFileName = QDir::homePath() + "/tempdatadir/settings.ini";
    TempFile = QDir::homePath() + "/tempdatadir/temp.ini";
}

IniFunctions::~IniFunctions() {
}

QString IniFunctions::ReadIni(QString Option) { // read the ini
    QFile inputFile(IniFileName);
    if (inputFile.open(QIODevice::ReadOnly)) {
       QTextStream in(&inputFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          if (line.split("=")[0] == Option)
              ToReturn = line.split("=")[1];
       }
       inputFile.close();
       return ToReturn;
    }
    inputFile.close();
    return "ini error: option not set";
}

void IniFunctions::WriteIni(QString Option, QString Value) { // write to the ini
    QFile file(TempFile);
    QFile inputFile(IniFileName);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    if (inputFile.open(QIODevice::ReadWrite)) {
       QTextStream in(&inputFile);
       while (!in.atEnd()) {
          QString line = in.readLine();
          if (line.split("=")[0] == Option) {
                 stream << Option << "=" << Value << "\n";

          } else {
               stream << line << "\n";
          }
       }
       file.close();
       inputFile.close();
       // delete old file and replace it
       QFile::remove(IniFileName);
       QFile::rename(TempFile, IniFileName);
       QFile::remove(TempFile);
    }
}
