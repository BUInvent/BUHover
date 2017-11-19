
/*
    Project BUScore by Jason and Kla
    This project file is for the "HoverBoard" (Particle Photon wifi module)
    It containst the functions that grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                    */

#include "functions.h"

void gotScores(const char *event, const char *data) {

    static String data_temp;
    static int data_count = 0;
    String data_byte = strtok(strdup(data), ",");

    // if first data_byte is not "data", or if data is the same as previous then don't print data.
    // Also note that data will print out if it hasn't printed in the last 10 times
    if ( strcmp(data_byte, "data") != 0 || ( strcmp(data, data_temp) == 0 && data_count < 10 )) {
      data_count ++;
    }

    else {

      data_count = 0;
      data_temp = data;
      String isUnplayed = strtok(NULL, ",");
  		String isinProgress = strtok(NULL, ",");
  		String isCompleted = strtok(NULL, ",");


      // If game has not been played yet display no score or time
      if (strcmp(isUnplayed, "true") == 0) {
        Serial.println("data,0,0,0,0,0");
      }


      // if game is currently in progress
      else if (strcmp(isinProgress, "true") == 0) {

        String home_score = strtok(NULL, ",");
        String away_score = strtok(NULL, ",");
        String period = strtok(NULL, ",");
        String seconds_remaining = strtok(NULL, ",");
        Serial.println(livegame(home_score, away_score, period, seconds_remaining));

      }


      // if game is finished display the final score the time as 0 and "F" for period
      else if (strcmp(isCompleted, "true") == 0) {

        String home_score = strtok(NULL, ",");
        String away_score = strtok(NULL, ",");
        Serial.println("data," + home_score + "," + away_score + ",F,0,0");

      }

    }

}


String livegame( String home_score, String away_score, String period, String seconds_remaining ) {

  // if empty seconds remaining then there is an intermission and time should be 0
  if (strcmp(seconds_remaining, "") == 0) {
    return("data," + home_score + "," + away_score + "," + period + ",0,0");
  }


  // if there are seconds remaining then the game is in progress and time needs to be displayed
  else {

    // convert total seconds to minutes and seconds
    int int_seconds = atoi( seconds_remaining );
    int minutes = int_seconds / 60;
    int seconds = int_seconds % 60;

    return("data," + home_score + "," + away_score + "," + period + "," + minutes + "," + seconds);

  }
  
}
