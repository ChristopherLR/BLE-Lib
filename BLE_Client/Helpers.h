#pragma once

//Reads the msg from rx
char read_msg(){
  int in = NONERX;
  if (Serial2.available() > 0) in = Serial2.read();
  return in;
}

//Update message with what needs to be sent each cycle
void send_east() { quick_transmit(&bt_i, EASTTX); }
void send_west() { quick_transmit(&bt_i, WESTTX);  }
void send_start() { quick_transmit(&bt_i, STARTTX); }
void send_stop() { quick_transmit(&bt_i, STOPTX); }
void send_doors_open() { quick_transmit(&bt_i, OPENTX); }
void send_doors_closed() { quick_transmit(&bt_i, CLOSETX); }
void send_emergency() { quick_transmit(&bt_i, EMERGENCYTX); }
void send_not_emergency() { quick_transmit(&bt_i, NONETX); }
