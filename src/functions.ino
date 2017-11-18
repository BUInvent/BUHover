
#include "functions.h"

String data_byte;

void gotScores(const char *event, const char *data) {

    static String data_temp = "";

    Serial.println();
    Serial.print("data = ");
    Serial.println(data);

    data_byte = strtok(strdup(data), ",");
    Serial.println("datatemp = " + data_temp);

    // if(data == data_temp || data_byte != "data") {
    if (strcmp(data_byte, "data") != 0){
      Serial.println("nothing happened cuz data_byte != 'data'");
    }

    // else if (strcmp(data, data_temp) == 0) {
    //   Serial.println("nothing happened cuz data == data_temp");
    // }

    else {

      String isUnplayed = strtok(NULL, ",");
  		String isinProgress = strtok(NULL, ",");
  		String isCompleted = strtok(NULL, ",");

      Serial.print("isUnplayed = ");
      Serial.println(isUnplayed);
      Serial.print("isinProgress = ");
      Serial.println(isinProgress);
      Serial.print("isCompleted = ");
      Serial.println(isCompleted);
      Serial.println();

      if (strcmp(isUnplayed, "true") == 0) {
        pregame();
      }

      else if (strcmp(isinProgress, "true") == 0) {
      }

      else if (strcmp(isCompleted, "true") == 0) {
        Serial.println("it's completed");
        postgame(strdup(data));
      }
    }

    data_temp = data;

}


void pregame() {

  Serial.println("data,0,0,0,0,0");

}


void postgame(char *data){

		String nothing = strtok(strdup(data), ",");
		nothing = strtok(NULL, ",");
		nothing = strtok(NULL, ",");
		String home_score = strtok(NULL, ",");
		String away_score = strtok(NULL, ",");

		Serial.println("data," + home_score + "," + away_score + ",F,0,0");

}
