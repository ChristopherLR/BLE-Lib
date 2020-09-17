#include "BTInterface.h"

#define BUFFER_SIZE 20
#define BAUD_RATE 38400

bt_interface bt_i = {0, 4, NONERX, NONETX, "INIT", &Serial2};
#include "Helpers.h"

char in = ' ';

void setup() {
  Serial.begin(BAUD_RATE);
  initialise_interface(&bt_i);
}

void loop() {
  // Read from the Serial Monitor and send to the Bluetooth module
  //The will read the message store the value received.
  //This type of values able to be recieved will can be found
  //in BTInterface.h in the msg_rx enums
  int msg_rx = read_msg();

  //The functions send state data can be found in Helpers.h
  //The following is an example how to use them
  send_east(); //This sends a EASTTX to the Control Box
  send_start(); //This sends a STARTTX to the Control Box

  //The following code is used to send Strings via the Serial monitor
  comm_status state = NOP;
  if (Serial.available()) {
    in = Serial.read();
    state = build_frame(&bt_i, in);
    Serial.write(in);
  }
  if(state == TRANSMIT) transmit_frame(&bt_i);
  if(state == OVERFLOW) reset_frame(&bt_i);
}
