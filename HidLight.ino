#include <Adafruit_NeoPixel.h>
#include "usb_dev.h"
 
#define N_PIN  23
#define N_LEDS 8

#define STATUS_LED_PIN 13

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, N_PIN, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {    
  Serial.begin(9600);             

  // Initialize NeoPixel strip
  strip.begin();
  strip.setBrightness(128); // 128 seems bright enough

  // Activate the status led (just to give some sign of life when other leds are not going)
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, 100);  

  HIDLight.onUpdate(updateLights, logUsb);
}

// Used for debugging incoming usb packets
void logUsb(usb_packet_t rx_packet) {    
  #ifdef DEBUG
  Serial.println("PACKET -");
  Serial.println("  LEN: " + String(rx_packet.len));
  Serial.println("  INDEX: " + String(rx_packet.index));
  Serial.println("  BUF -");
  for (int i = 0; i < rx_packet.len; i++) {
    Serial.println("    " + String(i) + ") DEC: " + String(rx_packet.buf[i], DEC) + " - HEX: " + String(rx_packet.buf[i], HEX));
  }
  #endif
}

void updateLights(int c[]) {
  // TODO: Have a good way to map physical LEDs to the instances in BT, for instance, a way to have the first 8 R LEDs correspond to a single light in BT 
  // TODO: If no light update is recieved in a certain amount of time, turn off all LEDs
  
  // Right now we assume every LED is a RGB LED, so we simply divide the number of leds with 3.
  for (int pi = 0; pi < HIDLIGHT_NUMBER_OF_LEDS / 3; pi++) {
    int iOffset = (pi * 3);
    uint32_t color = strip.Color(c[iOffset + 0], c[iOffset + 1], c[iOffset + 2]);
    
    strip.setPixelColor(pi, color);
    strip.show();
  }
}

// the loop routine runs over and over again forever:
void loop() {
  delay(25);
}
