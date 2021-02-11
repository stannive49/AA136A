//*************************************************************
  This is an examples for the RL01-02-03 Radio Range

  You can buy one on our store!
  -----> https://xinabox.cc/products/RL01/
  -----> https://xinabox.cc/products/RL02/
  -----> https://xinabox.cc/products/RL03/

  This example requests the Alcohol sensor to measure
  the Breath Alcohol Level

  Currently Supported on the following ☒CHIPs:
  - CW01
  - CR01/02/03

  The sensor communicates over the I2C Bus.

*************************************************************/

#include <xCore.h>
#include <xRL0x.h>

#define RL03_FREQ 915.0

void setup() {
   // Start the I2C Comunication
   #ifdef ESP8266
    Wire.pins(2, 14);
    Wire.setClockStretchLimit(15000);
  #endif
  Wire.begin();

  // Start the Serial Monitor
  SerialUSB.begin(115200);
  // Set the RGB Pin directions
  //pinMode(LED_RED, OUTPUT);
  //pinMode(LED_GREEN, OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);

  if (!RL0X.begin()) {
    SerialUSB.println("Check the connector to CW01");
    while (1) {
      // Flash RED to indicate failure
      SerialUSB.print("Not connecting to CW01");
      digitalWrite(LED_RED, HIGH);
      delay(100);
      digitalWrite(LED_RED, LOW);
      delay(100);
    }
  } else {
    // RL0X Initialized correctly
    SerialUSB.print("Connected to CW01");
    RL0X.setModemConfig(RL0X.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
  }
}

void loop() {
  SerialUSB.println("Sending to RL0X Server");

  digitalWrite(LED_GREEN, HIGH);

  uint8_t data[] = "Hello World!";
  delay(100);
  RL0X.send(data, sizeof(data));

  uint8_t buf[195];
  uint8_t len = sizeof(buf);

  if (RL0X.waitAvailableTimeout(3000)) {
    if (RL0X.recv(buf, &len)) {
      SerialUSB.print("got reply: ");
      SerialUSB.println((char*)buf);
      SerialUSB.print("RSSI: ");
      SerialUSB.println(RL0X.lastRssi(), DEC);
    } else {
      SerialUSB.println("recv failed");
    }
  } else {
    digitalWrite(LED_GREEN, LOW);
    SerialUSB.println("No reply, is the RL03 server running ?");
  }
}
