/*
 * Ultrasonic Simple
 * Prints the distance read by an ultrasonic sensor in
 * centimeters. They are supported to four pins ultrasound
 * sensors (liek HC-SC04) and three pins (like PING)))
 * and Seeed Studio sesores).
 *
 * The circuit:
 * * Module HR-SC04 (four pins) or PING))) (and other with
 *   three pins), attached to digital pins as follows:
 * ---------------------    ---------------------
 * | HC-SC04 | Arduino |    | 3 pins  | Arduino |
 * ---------------------    ---------------------
 * |   Vcc   |   5V    |    |   Vcc   |   5V    |
 * |   Trig  |   12    | OR |   SIG   |   13    |
 * |   Echo  |   13    |    |   Gnd   |   GND   |
 * |   Gnd   |   GND   |    ---------------------
 * ---------------------
 * Note: You need not obligatorily use the pins defined above
 * 
 * By default, the distance returned by the distanceRead()
 * method is in centimeters, to get the distance in inches,
 * pass INC as a parameter.
 * Example: ultrasonic.distanceRead(INC)
 *
 * created 3 Apr 2014
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 23 Jan 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 03 Mar 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *
 * This example code is released into the MIT License.
 */

#include <Ultrasonic.h>

int led = 13; // blink

/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic(12, 11);

// Define Pins - added for multicolor LED
#define BLUE 3
#define GREEN 5
#define RED 6

//set boolean variable FAULT
bool FAULT;

void setup() {
  Serial.begin(9600);

  // Added for multicolor LED
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

bool dist_fault_determ(int dist,int limit) {
  //This function determines a fault given a distance
  // and a triggering, "fault" limit
  if (dist > limit) {
    return true;
  }
  else {
    return false;
  }
}

void no_fault() {
  //What to do if there's a fault
  digitalWrite(BLUE,LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
}

void fault() {
  //What to do if there's a fault
  digitalWrite(BLUE,LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
}


void loop() {
  //make variable DISTANCE as integer of distance in cm
  int distance = ultrasonic.distanceRead();

  //threshold variable
  int distance_threshold = 60;
  
  // Pass INC as a parameter to get and print the distance in inches
  Serial.print("Distance in CM: ");
  Serial.println(distance);

  FAULT = dist_fault_determ(distance,distance_threshold);

  if (FAULT) {
    fault();
  }
  else {
    no_fault();
  }
  
  delay(500);
}
