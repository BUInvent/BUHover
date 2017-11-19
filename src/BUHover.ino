  /*
      Project BUScore by Jason and Kla
      This project file is for the "HoverBoard" (Particle Photon wifi module)
      It is the main function that will  grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                      */

#include "functions.h"

void setup() {
    // subscribe to the webhook
    Particle.subscribe("hook-response/NHLscores2", gotScores, MY_DEVICES);
}


void loop() {
    static unsigned long nextTrigger = 10 * 1000;

    // pull the webhook every 10 seconds
    if (nextTrigger < millis()) {
        nextTrigger = millis() + 10*1000;
        Particle.publish("NHLscores2");

    }
}
