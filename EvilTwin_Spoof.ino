#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
}

const char* ssidList[] = {
  "Fake_AP_1", "Fake_AP_2", "Fake_AP_3",
  "Fake_AP_4", "Fake_AP_5", "Fake_AP_6", "Fake_AP_7"
};

uint8_t beaconPacket[109] = {
  0x80, 0x00, 0x00, 0x00,                          // Frame Control & Duration
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,              // Destination Address (Broadcast)
  0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,              // Source Address (Randomized MAC)
  0xde, 0xad, 0xbe, 0xef, 0xde, 0xad,              // BSSID (Same as Source Address)
  0x00, 0x00,                                      // Sequence Control
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Timestamp (Set Later)
  0xff, 0xff,                                      // Beacon Interval
  0x01, 0x04,                                      // Capabilities
  0x00, 0x00,                                      // SSID Parameter Set (Set Later)
  0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c,  // Supported Rates
  0x03, 0x01, 0x01,                                // Channel
  0x05, 0x04, 0x00, 0x02, 0x00, 0x00               // Traffic Indication Map
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
