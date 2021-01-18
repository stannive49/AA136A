#include <SSD1306init.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <xOD01.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//initialize variable
xOD01 OD01;

//WiFi connection
const char* ssid = "Sound18";               // your network SSID (name)
const char* pass = "Ding0d0g1";             // your network password
char servername[]="celestrak.com";           // Celestrak Server

WiFiClient client;

void setup() {
  // 'Wire' relates to the I²C interface.
#ifdef ESP8266
  Wire.pins(2, 14);
#endif
  Wire.begin();
  OD01.begin();
  
   // start the OD01 OLED display
  OD01.println("Starting I2C commu-");
  OD01.print("nication");
  delay(2000);
  OD01.clear();
  delay(1000);
  OD01.print("Starting the OD01");
  delay(2000);
  // clear the OLED display
  OD01.clear();
  
  Serial.begin(115200);
  delay(1000);
  OD01.println("Attempting to connect");
  OD01.print("to WiFi");
  delay(1000);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(1000);
    OD01.println("...");
  }

  OD01.clear();
  delay(1000);
  OD01.print("Connected to wifi");
  delay(1000);
  OD01.clear();
  OD01.println("\nStarting connection");
  OD01.print("with server...");
  delay(1000);
  OD01.clear();
  makeRequest();
}

void loop() {
}

void makeRequest(){
    // if you get a connection, report back via serial:
    if (client.connect(servername, 80)) {
    OD01.println("connected to server");
    OD01.print("");
    OD01.print("TLE for: NOAA 15");
    delay(2000);
    // Make HTTP request for weather.txt:
    client.println("GET /NORAD/elements/weather.txt HTTP/1.0");     // rest of url for your chosen txt file, i.e extension following celestrak.com , Replace everything EXCEPT: GET HTTP/1.0
    client.println();                                                         
    } else {
      OD01.println("connection failed");
    }
    
    
   // if there are incoming bytes available
   // from the server, read them and print them:
  char c;
  int lineCounter=0; 
 while (!client.available()){
  // while loop runs while waiting for server availability
 }

// Skip HTTP headers
 char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    OD01.println(F("Invalid response"));
    return;
  }

 while (client.available()) {
    c = client.read();
    Serial.print(c);
    
    if (c == '\n'){
      lineCounter = lineCounter+1;
    }

    if (lineCounter==3){
      client.stop();
      break;
    }
  }

  // if the server becomes disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    OD01.clear();
    delay(1000);
    OD01.println("disconnecting from server");
    client.stop();
  }
}
