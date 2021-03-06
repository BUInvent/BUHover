
/*
    Project BUScore by Jason
    This project file is for the "HoverBoard" (Particle Photon wifi module)
    It containst the functions that grab data from the webhook, parse it, and send it to the "BattleShip"
                                                                                    */

#include <string.h>
#include <WProgram.h>
#include "functions.h"

using namespace std;

// This function will Serial1 print the data in the format of:
// data,home score,away score,period,minutes,seconds
void got_scores(const char* event, const char* data)
{

    static string data_temp;
    static int data_count = 0;
    string data_byte = strtok(strdup(data), ",");

    // if first data_byte is not "data", or if data is the same as previous then don't print data.
    // Also note that data will print out if it hasn't printed in the last 10 times
    if (strcmp(data_byte.c_str(), "data") != 0 || (strcmp(data, data_temp.c_str()) == 0 && data_count < 10)) {
        data_count++;
        return;
    }

    data_count = 0;
    data_temp = data;
    string isUnplayed = strtok(NULL, ",");
    string isinProgress = strtok(NULL, ",");
    string isCompleted = strtok(NULL, ",");

    // If game has not been played yet display no score or time
    if (strcmp(isUnplayed.c_str(), "true") == 0) {
        Serial1.println("data,00,00,0,00,00");
    }

    // if game is currently in progress
    else if (strcmp(isinProgress.c_str(), "true") == 0) {

        int away_score = atoi(strtok(NULL, ","));
        int home_score = atoi(strtok(NULL, ","));
        int period = atoi(strtok(NULL, ","));
        int seconds_remaining = atoi(strtok(NULL, ","));

        int minutes = seconds_remaining / 60;
        int seconds = seconds_remaining % 60;

        Serial1.printf("data,%02d,%02d,%d,%02d,%02d\n", away_score, home_score, period, minutes, seconds);
    }

    // if game is finished display the final score, the time as 0, and "10" for period
    else {

        int away_score = atoi(strtok(NULL, ","));
        int home_score = atoi(strtok(NULL, ","));
        Serial1.printf("data,%02d,%02d,10,00,00\n", away_score, home_score);
    }
}
