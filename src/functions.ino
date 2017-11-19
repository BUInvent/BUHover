
#include "functions.h"

String data_byte;

void gotScores(const char *event, const char *data) {

  data_byte = strtok(strdup(data), ",");
  String isUnplayed = strtok(NULL, ",");
  String isinProgress = strtok(NULL, ",");
  String isCompleted = strtok(NULL, ",");
  String home_score = strtok(NULL, ",");
  String away_score = strtok(NULL, ",");
  String quarter = strtok(NULL, ",");
  String intermission = strtok(NULL, ",");
  String seconds_remaining = strtok(NULL, ",");

  Serial.println();
  Serial.print("data = ");
  Serial.println(data);
  Serial.print("isUnplayed = ");
  Serial.println(isUnplayed);
  Serial.print("isinProgress = ");
  Serial.println(isinProgress);
  Serial.print("isCompleted = ");
  Serial.println(isCompleted);
  Serial.print("home_score = ");
  Serial.println(home_score);
  Serial.print("away_score = ");
  Serial.println(away_score);
  Serial.print("quarter = ");
  Serial.println(quarter);
  Serial.print("intermission = ");
  Serial.println(intermission);
  Serial.print("seconds_remaining = ");
  Serial.println(seconds_remaining);

    static String data_temp = "";

    Serial.println();
    Serial.print("data = ");
    Serial.println(data);

    data_byte = strtok(strdup(data), ",");

    if ( strcmp(data_byte, "data") != 0 || strcmp(data, data_temp) == 0) {
        Serial.println("no update");
    }

    else {

      String isUnplayed = strtok(NULL, ",");
  		String isinProgress = strtok(NULL, ",");
  		String isCompleted = strtok(NULL, ",");

      if (strcmp(isUnplayed, "true") == 0) {
        pregame();
      }

      else if (strcmp(isinProgress, "true") == 0) {
        livegame(strdup(data));
      }

      else if (strcmp(isCompleted, "true") == 0) {
        postgame(strdup(data));
      }
    }

    data_temp = data;

}


void pregame() {

  Serial.println("data,0,0,0,0,0");

}

void livegame(char *data) {

  String nothing = strtok(strdup(data), ",");
  nothing = strtok(NULL, ",");
  nothing = strtok(NULL, ",");
  nothing = strtok(NULL, ",");
  String home_score = strtok(NULL, ",");
  String away_score = strtok(NULL, ",");
  String period = strtok(NULL, ",");
  String seconds_remaining = strtok(NULL, ",");

  if (strcmp(seconds_remaining, "") == 0) {
    Serial.println("data," + home_score + "," + away_score + "," + period + ",0,0");
  }

  else {

    int int_seconds = atoi( seconds_remaining );
    int minutes = int_seconds / 60;
    int seconds = int_seconds % 60;

    Serial.println("data," + home_score + "," + away_score + "," + period + "," + minutes +
      "," + seconds);
  }

}

void postgame(char *data) {

		String nothing = strtok(strdup(data), ",");
		nothing = strtok(NULL, ",");
		nothing = strtok(NULL, ",");
    nothing = strtok(NULL, ",");
		String home_score = strtok(NULL, ",");
		String away_score = strtok(NULL, ",");

		Serial.println("data," + home_score + "," + away_score + ",F,0,0");

}
