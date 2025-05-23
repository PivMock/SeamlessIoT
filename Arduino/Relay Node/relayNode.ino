#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400); // HC-05 default baud rate for AT commands
  
  // Enter AT command mode
  delay(1000);
  BTSerial.print("AT\r\n");
  delay(500);
  while(BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  
  // Set to master mode
  BTSerial.print("AT+ROLE=1\r\n"); // 1 = master mode
  delay(500);
  while(BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  
  // Set connection mode to specify address
  BTSerial.print("AT+CMODE=0\r\n"); // 0 = connect to specific address
  delay(500);
  while(BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  
  // Replace with your HC-06's address (get it with AT+ADDR? on HC-06)
  BTSerial.print("AT+BIND=98D3,91,FE51B4\r\n"); // Example address, CHANGE THIS
  delay(500);
  while(BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  
  // Reset module to apply changes
  BTSerial.print("AT+RESET\r\n");
  delay(2000); // Give time to reset
  
  
  // Switch to communication mode
  BTSerial.begin(9600); // Switch to normal communication baud rate
}

void loop() {
  // Check for user input from Serial Monitor
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command == "send" || command == "stop") {
      // Send the command to the sensor unit
      BTSerial.println(command);
    }
    else if (command.startsWith("AT")) {
      // Allow manual AT commands for debugging
      BTSerial.begin(38400); // Switch back to AT mode baud rate
      BTSerial.print(command + "\r\n");
      delay(500);
      while(BTSerial.available()) {
        Serial.write(BTSerial.read());
      }
      BTSerial.begin(9600); // Switch back to communication mode
    }
  }
  
  // Check for incoming data from the sensor unit
  if (BTSerial.available()) {
    String data = BTSerial.readStringUntil('\n');
    Serial.println(data);
  }
  
  // Small delay to prevent overwhelming the system
  delay(10);
}