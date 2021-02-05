// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
const int touchSensePin = 2;

void setup() {
  // Initialize ASK Object
  rf_driver.init();
  Serial.begin(9600);          // For Serial Monitor
  pinMode(touchSensePin, INPUT);
}



void loop() {
  bool touchSense = digitalRead(touchSensePin);
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
}
