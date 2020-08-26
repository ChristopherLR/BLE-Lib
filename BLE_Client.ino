#include "BTInterface.h"
#define BAUD_RATE 38400

bt_interface bt_i = {4, "INIT", &Serial2};
char in = ' ';

void setup() {
  Serial.begin(BAUD_RATE);
  initialise_interface(&bt_i);
}

void loop() {
  comm_status state = NOP;

  // Read from the Serial Monitor and send to the Bluetooth module
  if (Serial.available()) {
    in = Serial.read();
    state = build_frame(&bt_i, in);
    Serial.write(in);
  }

  if(state == TRANSMIT) transmit_frame(&bt_i);
  
  if (Serial2.available() > 0) 
    Serial.write(Serial2.read()); 
}
