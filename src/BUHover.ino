// ------------
// Blink an LED - Modified for Connected-Displays.com Photon Rain LED Tutorial - Step 2
// ------------

/*-------------
We've heavily commented this code for you. If you're a pro, feel free to ignore it.
Comments start with two slashes or are blocked off by a slash and a star.
You can read them, but your device can't.
It's like a secret message just for you.
Every program based on Wiring (programming language used by Arduino, and Particle devices) has two essential parts:
setup - runs once at the beginning of your program
loop - runs continuously over and over
You'll see how we use these in a second.
This program will blink an led on and off every second.
It blinks the D7 LED on your Particle device. If you have an LED wired to D0, it will blink that LED as well.
-------------*/


// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

String home_score, away_score, period, intermission, seconds_remaining;

void gotScores(const char *event, const char *data) {

    Serial.print("data: ");
    if (data)
        Serial.println(data);
    else
        Serial.println("NULL");

    home_score = strtok(strdup(data), ",");
    Serial.print("home_score = ");
    Serial.println(home_score);

    away_score = strtok(NULL, ",");
    Serial.print("away_score = ");
    Serial.println(away_score);

    period = strtok(NULL, ",");
    Serial.print("period = ");
    Serial.println(period);

    intermission = strtok(NULL, ",");
    Serial.print("intermission = ");
    Serial.println(intermission);

    seconds_remaining = strtok(NULL, ",");
    Serial.print("seconds_remaining = ");
    Serial.println(seconds_remaining);

}

// Having declared these variables, let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {

    // We are going to tell our device that D0 and D7 (which we named led1 and led2 respectively) are going to be output
    // (That means that we will be sending voltage to them, rather than monitoring voltage that comes from them)

    // It's important you do this here, inside the setup() function rather than outside it or in the loop function.

    if (Particle.subscribe("hook-response/NHLscores", gotScores, MY_DEVICES)) {
        Serial.println("subscribed!");
    } else {
        Serial.println("error: subscription failed");
    }
}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
    // wait 10 seconds after reset before sending the first trigger
    static unsigned long nextTrigger = 10 * 1000;

    if (nextTrigger < millis()) {
        // polling Webhook every 5 seconds is 720 API calls/day
        nextTrigger = millis() + 5*1000;

        Serial.println("Requesting Score");
        Particle.publish("NHLscores");

    }
}
