#include "BTInterface.h"
#define BUFFER_SIZE 20
#define BAUD_RATE 38400

bt_interface bt_i = {4, "INIT", &Serial2};
#include "Helpers.h"

char in = ' ';
char blue_in = ' ';
char bin = ' ';

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
  if(state == OVERFLOW) reset_frame(&bt_i);

  blue_in = read_msg();
  if(blue_in!=' ')Serial.write(blue_in);
//  if (Serial2.available() > 0) 
//    Serial.write(Serial2.read()); 
}

//function to read from bluetooth
char read_msg(){
  if (Serial2.available() > 0){
    bin = Serial2.read();
    return bin;
  } else return ' ';
}
