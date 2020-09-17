#include "BTInterface.h"
<<<<<<< Updated upstream
#define BAUD_RATE 38400

bt_interface bt_i = {4, "INIT", &Serial2};
char in = ' ';
char blue_in = ' ';
=======
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
<<<<<<< Updated upstream
  comm_status state = NOP;

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
  if (rx_status == OVERFLOW) reset_frame(&bt_i);

  blue_in = readMsg();
  if(blue_in!=' ')Serial.write(blue_in);
//  if (Serial2.available() > 0) 
//    Serial.write(Serial2.read()); 
}

//function to read from bluetooth
char readMsg(){
  if (blue_serial.available() > 0){
    bin = blue_serial.read();
    return bin;
  } else return ' ';
}

//FUNCTIONS TO SEND STATE DATA
void sendStop(){
  quick_transmit(&bt_i,'s'); 
}

void sendGo(){
  quick_transmit(&bt_i,'g'); 
}

void sendEast(){
  quick_transmit(&bt_i,'e'); 
}

void sendWest(){
  quick_transmit(&bt_i,'w'); 
}

void sendEmergency(){
  quick_transmit(&bt_i,'m'); 
}

void sendNotEmergency(){
  quick_transmit(&bt_i,'n'); 
}

void sendDoorsOpen(){
  quick_transmit(&bt_i,'o'); 
}

void sendDoorsClosed(){
  quick_transmit(&bt_i,'c'); 
}



//BLUETOOTH COMMUNICATION FUNCTIONS
comm_status initialise_interface(bt_interface *frame) {
  frame->ss->begin(BAUD_RATE);
  comm_status status = transmit_frame(frame);
};

comm_status transmit_frame(bt_interface *frame) {
  if (frame->length == 0)
    return NOP;
  for (int i = 0; i < frame->length && i < BUFFER_SIZE; i++) {
    frame->ss->write(frame->msg[i]);
  }
  frame->ss->write("\r\n");
  frame->length = 0;
  return SUCCESS;
}

comm_status build_frame(bt_interface *frame, char c) {
  if (frame->length >= BUFFER_SIZE)
    return OVERFLOW;
  if (c == '\r')
    return TRANSMIT;
  if (c == '\n')
    return NOP;
  frame->msg[frame->length] = c;
  frame->length++;
  return SUCCESS;
}

/*
 * Sends over a single char 
 */
comm_status quick_transmit(bt_interface *frame, char c) {
  frame->ss->write(c);
  frame->ss->write("\n");
  frame->length = 0;
  return SUCCESS;
}

/*
 * Resets the length of the frame to 0 so that messages can be sent again
 */
void reset_frame(bt_interface *frame){
  frame->length = 0;
  if(state == TRANSMIT) transmit_frame(&bt_i);
  if(state == OVERFLOW) reset_frame(&bt_i);
}
