/* Screaming Soft Toy / DingDuino
   Chooses a .mp4 file to play if the light level from two inputs are sufficiently low.
   Created 5th December, 2020, by Jake Ireland
*/

#include<MD_YX5300.h>
#include <SoftwareSerial.h>

// Connections for serial interface to the YX5300 module
const uint8_t ARDUINO_RX = 10;    // connect to TX of MP3 Player module
const uint8_t ARDUINO_TX = 11;    // connect to RX of MP3 Player module

SoftwareSerial  MP3Stream(ARDUINO_RX, ARDUINO_TX);  // MP3 player serial stream for comms
MD_YX5300 mp3(MP3Stream);

//The setup() method runs once, when the sketch starts
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(10000);
  // initialize global libraries
  MP3Stream.begin(MD_YX5300::SERIAL_BPS);
  mp3.begin();
}


// The loop() method runs over and over again, as long as the Arduino has power
void loop(void) {
  int eyeOne = analogRead(A0);
  int eyeTwo = analogRead(A5);
  if ((eyeOne < 50) && (eyeTwo < 50)) {
    mp3.queryFilesCount();
    const uint8_t track = (rand() % (mp3.getStsData())) + 1; // getStsData() gets the value from queryFilesCount()
    mp3.playTrack(track);
    delay(1000);
  }
}
