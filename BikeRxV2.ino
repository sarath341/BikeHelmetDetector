// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 5000;           // interval at which to blink (milliseconds)
unsigned long currentMillis = interval + 1;

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
const int realayPin = 2;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
  pinMode(realayPin, OUTPUT);
  digitalWrite(realayPin, HIGH); //OFF Relay/Bike
}

void loop()
{

  // Set buffer to size of expected message
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size

  if (rf_driver.recv(buf, &buflen))
  {
    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);
    digitalWrite(realayPin, LOW); //OFF Relay/Bike
    Serial.println("Bike Running");

    // save the last time you blinked the LED
    previousMillis = currentMillis;
  }

  currentMillis = millis(); //Get the current millisecond

  if (currentMillis - previousMillis >= interval) {     //compare with prev detected millis

    // set the LED with the ledState of the variable:
    digitalWrite(realayPin, HIGH); //OFF Relay/Bike
    Serial.println("Bike OFF");
  }
}
