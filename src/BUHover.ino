
String home_score, away_score, period, intermission, seconds_remaining;
int minutes, seconds;
int intseconds, intminutes, iseconds;

void gotScores(const char *event, const char *data) {

    home_score = strtok(strdup(data), ",");
    away_score = strtok(NULL, ",");
    period = strtok(NULL, ",");
    intermission = strtok(NULL, ",");
    seconds_remaining = strtok(NULL, ",");

    if(seconds_remaining != ":"){
      intseconds = atoi(strtok(strdup(seconds_remaining), ":"));
      minutes = intseconds / 60;
      seconds = intseconds % 60;
    }
    else minutes = seconds = 0;

    if(home_score == ":") { home_score = "0"; }
      else { home_score = strtok(strdup(home_score), ":"); }

    if(away_score == ":") { away_score = "0"; }
      else { away_score = strtok(strdup(away_score), ":"); }

    if(period != ":") { period = strtok(strdup(period), ":"); }
      else if(intermission != ":"){
        period = strtok(strdup(intermission), ":"); }
      else{ period = "0"; }

    Serial.println("data," + home_score + "," + away_score + "," + period + ","
      + minutes + "," + seconds);

}


void setup() {
    Particle.subscribe("hook-response/NHLscores", gotScores, MY_DEVICES);
}



void loop() {
    static unsigned long nextTrigger = 10 * 1000;

    if (nextTrigger < millis()) {
        nextTrigger = millis() + 5*1000;
        Particle.publish("NHLscores");

    }
}
