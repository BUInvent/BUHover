  /*
      Project BUScore by Jason
      This project file is for the "HoverBoard" (Particle Photon wifi module)
      It is the main function that will  grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                      */

#include "functions.h"

// declare global variables
int team_league(String team_league);
char date_team[256];
String league;


void setup() {

  // expose the team_league function so that the app can call it
  // and set the time zone for when we get the date
  Particle.function("team_league", team_league);
  Time.zone(-7);

}


void loop() {

    // pull the webhook every 10 seconds
    Particle.publish( league + "Scores", date_team, PRIVATE );
    delay(10000);

}


// the input will be a string in the format: "league team"
// This function will grab the league and team by parsing the string and will
// subscribe to the leagues specified webhook
// it will send the date and team to the webhook so it knows what URL path to use
// for the specified game
int team_league(String team_league) {

  char date[10];
  String team;

  league = strtok( strdup(team_league), " " );
  team = strtok( NULL, "," );

  Particle.subscribe("hook-response/" + league + "Scores", got_scores, MY_DEVICES);
  sprintf(date,  "%d%02d%02d", Time.year(), Time.month(), Time.day());
  snprintf(date_team, sizeof(date_team), "{\"date\":\"%s\",\"team\":\"%s\"}", date, team.c_str());

  return 1;

}
