#include <Wire.h>
#include <Adafruit_TMP117.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

Adafruit_TMP117 tmp117;
SoftwareSerial BTSerial(2, 3); // RX, TX

bool sendingData = false;
unsigned long lastSendTime = 0;
const unsigned long sendInterval = 1000; // Send data every 1000ms (1 second)

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); // HC-06 default baud rate
  
  // Initialize the sensor
  if (!tmp117.begin()) {
    Serial.println("Failed to find TMP117 chip");
    while (1) { delay(10); }
  }
  Serial.println("TMP117 Found!");
  
  Serial.println("Sensor Unit Ready. Waiting for commands...");
}

void loop() {
  // Check for incoming Bluetooth commands
  if (BTSerial.available()) {
    String command = BTSerial.readStringUntil('\n');
    command.trim();
    
    if (command == "send") {
      sendingData = true;
      Serial.println("Start sending data");
    } 
    else if (command == "stop") {
      sendingData = false;
      Serial.println("Stop sending data");
    }
  }
  
  // If we're in sending mode and it's time to send data
  if (sendingData && (millis() - lastSendTime >= sendInterval)) {
    sensors_event_t temp; // Create an event to hold the data
    tmp117.getEvent(&temp); // Read the temperature
    
    // Send temperature data via Bluetooth
    BTSerial.print("Temp: ");
    BTSerial.print(temp.temperature);
    BTSerial.println(" °C");
    
    // Also print to serial for debugging
    Serial.print("Temp: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");
    
    lastSendTime = millis();
  }
  
  // Small delay to prevent overwhelming the system
  delay(10);
}