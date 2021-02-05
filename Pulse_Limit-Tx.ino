#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

//  Variables
const int PulseWire = A7;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
const int touchSensePin = 2;

// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {
  // Initialize ASK Object
  rf_driver.init();
  Serial.begin(9600);          // For Serial Monitor
  pinMode(touchSensePin, INPUT);
}



void loop() {
  Signal = analogRead(PulseWire);  // Read the PulseSensor's value.
  bool touchSense = digitalRead(touchSensePin);

  //Limit/Touch Sensor Code
  if ( touchSense == LOW) {
    Serial.println("Sensor Detected"); // If test is "true", print a message "a heartbeat happened".
    Serial.println(touchSense);                        // Print the value inside of myBPM.
    const char *msg = "Hello World";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    Serial.println("Hello World");
  }

  else
  {
    Serial.println("Wear Helmet");
  }

  delay(20);                    // considered best practice in a simple sketch.
  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

  //Pulse Sensor Code
  if (Signal > Threshold) {                        // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED13, HIGH);
    const char *msg = "Hello World";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
    Serial.println("Hello World");
  } else {
    digitalWrite(LED13, LOW);               //  Else, the sigal must be below "550", so "turn-off" this LED.
    Serial.println("Wear Helmet! Stay Safe");
  }


  delay(10);
  /*
    int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
    // "myBPM" hold this BPM value now.

    if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
      Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
      Serial.print("BPM: ");                        // Print phrase "BPM: "
      Serial.println(myBPM);                        // Print the value inside of myBPM.
      const char *msg = "Hello World";
      delay(10);
      rf_driver.send((uint8_t *)msg, strlen(msg));
      rf_driver.waitPacketSent();
      delay(1000);
      Serial.println("Hello World");
    }
    delay(20);                    // considered best practice in a simple sketch.
  */

}
