// this class will parse any files we require
#include "fileparsing.h"

FileParsing::FileParsing() {

}

FileParsing::~FileParsing() {

}

//loc_id#location#state#forecast_date#issue_date#issue_time#min_0#max_0#min_1#
//max_1#min_2#max_2#min_3#max_3#min_4#max_4#min_5#max_5#min_6#max_6#min_7#max_7#
//forecast_0#forecast_1#forecast_2#forecast_3#forecast_4#forecast_5#forecast_6#
//forecast_7#
QString FileParsing::ParseWeather() { // parse weather file
   QFile inputFile(QDir::homePath() + "/tempdatadir/weather.txt");
   if (inputFile.open(QIODevice::ReadOnly)) {
      QTextStream in(&inputFile);
      while (!in.atEnd()) {
         QString line = in.readLine();
         if (line.split("#")[1] == ini.ReadIni("location")) {
             for (int x = 0; x < 30; x++) {
                Forecast << line.split("#")[x];
                qDebug() << Forecast.at(x);
             }
         }
      }
      inputFile.close();
      // we now have all the information we need inside Forecast[]
      // it goes up to 30 (0-29)
      return "Current condition: " + Forecast[22];
   }
   return "error parsing..";
}
