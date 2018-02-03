  /*
      Project BUScore by Jason and Kla
      This project file is for the "HoverBoard" (Particle Photon wifi module)
      It is the main function that will  grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                      */

#include "functions.h"

char buf[256];
char date[10];
String league;
String team;

int teamLeague(String teamLeague);

void setup() {

    Particle.function("teamLeague", teamLeague);
    Time.zone(-4);
    // teamLeague("NBA CHI");


}


void loop() {
    static unsigned long nextTrigger = 10 * 1000;

    // pull the webhook every 10 seconds
    if (nextTrigger < millis()) {
        nextTrigger = millis() + 10*1000;
        Particle.publish( league + "Scores", buf, PRIVATE );

    }
}

// this function automagically gets called upon a matching POST request
int teamLeague(String teamLeague)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if(teamLeague != "")
  {

    league = strtok( strdup(teamLeague), " " );
    team = strtok( NULL, "," );

    Particle.subscribe("hook-response/" + league + "Scores", gotScores, MY_DEVICES);
    sprintf(date,  "%d%02d%02d", Time.year(), Time.month(), Time.day());
    snprintf(buf, sizeof(buf), "{\"date\":\"%s\",\"team\":\"%s\"}", date, team.c_str());

    return 1;

  }
  else return -1;
}
