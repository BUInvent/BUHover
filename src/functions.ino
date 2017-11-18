
#include "functions.h"

// String data_temp = "";

// void gotScores(const char *event, const char *data) {
//
//     if(data == data_temp) {}
//
//     else {
//
//       isUnplayed = strtok(strdup(data), ",");
//   		isinProgress = strtok(NULL, ",");
//   		isCompleted = strtok(NULL, ",");
//
//       if (isUnplayed == "true") {
//         pregame();
//       }
//
//       else if (isinProgress == "true") {
//
//       }
//
//       else if (isCompleted == "true") {
//         postgame(data);
//       }
//     }
//
//     data_temp = data;
//
// }


void pregame() {

  Serial.println("data,0,0,0,0,0");

}


void postgame(char *data){

    Serial.println("hello 2");

		String nothing = strtok(strdup(data), ",");
		nothing = strtok(NULL, ",");
		nothing = strtok(NULL, ",");
		String home_score = strtok(NULL, ",");
		String away_score = strtok(NULL, ",");

		Serial.println("data," + home_score + "," + away_score + ",F,0,0");

}
