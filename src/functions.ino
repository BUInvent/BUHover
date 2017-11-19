
/*
    Project BUScore by Jason and Kla
    This project file is for the "HoverBoard" (Particle Photon wifi module)
    It containst the functions that grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                    */

#include "functions.h"
String data_byte;

void gotScores(const char *event, const char *data) {

    static String data_temp;
    data_byte = strtok(strdup(data), ",");

    if ( strcmp(data_byte, "data") != 0 || strcmp(data, data_temp) == 0) {}

    else {

      String isUnplayed = strtok(NULL, ",");
  		String isinProgress = strtok(NULL, ",");
  		String isCompleted = strtok(NULL, ",");

      if (strcmp(isUnplayed, "true") == 0) {
        pregame();
      }

      else if (strcmp(isinProgress, "true") == 0) {

        String home_score = strtok(NULL, ",");
        String away_score = strtok(NULL, ",");
        String period = strtok(NULL, ",");
        String seconds_remaining = strtok(NULL, ",");
        livegame(home_score, away_score, period, seconds_remaining);

      }

      else if (strcmp(isCompleted, "true") == 0) {

        String home_score = strtok(NULL, ",");
        String away_score = strtok(NULL, ",");
        postgame(home_score, away_score);

      }

      data_temp = data;

    }
}


void pregame() {

  Serial.println("data,0,0,0,0,0");

}


void livegame( String home_score, String away_score, String period, String seconds_remaining ) {

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

void postgame( String home_score, String away_score ) {

		Serial.println("data," + home_score + "," + away_score + ",F,0,0");

}
