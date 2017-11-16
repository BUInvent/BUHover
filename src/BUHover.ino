  /*
      Project BUScore by Jason and Kla
      This project file is for the "hoverboard" (Particle Photon wifi module)
      It will grab data from the webhook, parse it,
      and send it to the "BattleShip"
                                                                */

void gotScores(const char *event, const char *data) {

    // declare variables
    String home_score, away_score, period, intermission, seconds_remaining;
    int minutes, seconds, intseconds;

    // grab the data from the web hook.
    // Each of these variables will have a ":" attached
    home_score = strtok(strdup(data), ",");
    away_score = strtok(NULL, ",");
    period = strtok(NULL, ",");
    intermission = strtok(NULL, ",");
    seconds_remaining = strtok(NULL, ",");


    // below code takes out all ":"s and grabs exactly what we need to send
    // to the BattleShip. Data sent to the ship should be in the format:
    // "data, home score, away score, period, minutes, seconds"

    // convert total seconds to minutes and seconds
    if(seconds_remaining != ":"){

      intseconds = atoi(strtok(strdup(seconds_remaining), ":"));
      minutes = intseconds / 60;
      seconds = intseconds % 60;

    } else {
      // set seconds and minutes to 0 if no time is left in the period(":")
      minutes = seconds = 0;
    }

    
    // if the game has not started yet, home_score and away_score will get set
    // to 0. otherwise, take out the ":"
    if(home_score == ":") {
      home_score = "0";

    } else {
      home_score = strtok(strdup(home_score), ":");
    }

    if(away_score == ":") {
      away_score = "0";

    } else {
      away_score = strtok(strdup(away_score), ":");
    }


    if(period != ":") { // grab period when game is in progress
      period = strtok(strdup(period), ":");

    // if period == ":" and intermission != ":", get the intermission period
    // this will be during intermission
    } else if(intermission != ":") {
        period = strtok(strdup(intermission), ":");

    } else {
      period = "0"; // if both period and intermission = ":"
    }

    // send data to the BattleShip
    Serial.println("data," + home_score + "," + away_score + "," + period + ","
      + minutes + "," + seconds);

}


void setup() {
    // subscribe to the webhook
    Particle.subscribe("hook-response/NHLscores", gotScores, MY_DEVICES);
}



void loop() {
    static unsigned long nextTrigger = 10 * 1000;

    // pull the webhook every 5 seconds
    if (nextTrigger < millis()) {
        nextTrigger = millis() + 5*1000;
        Particle.publish("NHLscores");

    }
}
