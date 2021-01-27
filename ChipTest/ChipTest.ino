#include <SSD1306init.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <xCore.h>
#include <xSL01.h>
#include <xSW01.h>
#include <xSI01.h>
#include <xSN01.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//WiFi connection
const char* ssid = "Sound18";               // your network SSID (name)
const char* pass = "Ding0d0g1";             // your network password

WiFiClient client;

//Initialize Test Chip Variable Names
xSL01 SL01;
xSW01 SW01;
xSI01 SI01;
xSN01 SN01;

void setup() {
  // 'Wire' relates to the I²C interface.
  #ifdef ESP8266
    Wire.pins(2, 14);
  #endif

  Wire.begin();

  Serial.begin(115200);
  delay(1000);
  Serial.println();
  delay(1000);

  //Test Port
  IP01_test();

  //Test WiFi
  CW01_test();

  //Test Light Sensor
  // Start the  SL01 Sensor
  SL01.begin();
  delay(1000);
  SL01_test();

  //Test Humidity Sensor
  SW01.begin();
  delay(5000);
  SW01_test();

  //Test Gyro and Magnetomoeter
  SI01.begin();
  delay(1000);
  SI01_test();

  //Test GPS
  SN01.begin();
  delay(1000);
  SN01_test();
}


void loop() {

}


// Connect to Port
void IP01_test() {
  //Check Port Exists
  if (Serial) {
    Serial.println("Port Connected");
    Serial.println();
    delay(1000);
  }
}

// Connect to WiFi
void CW01_test() {
  //Start Attempt to Connect to WiFi
  Serial.print("Attempting to connect to WiFi");
  delay(1000);

  //Begin WiFi Connection
  WiFi.begin(ssid, pass);

  //Loop Check for WiFi Connection
  while ( WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  //If Successful Connection Obtained
  if (WiFi.status() == WL_CONNECTED) {
    delay(1000);
    Serial.print("Connected to wifi!");
    delay(1000);
  }

  Serial.println();
  delay(1000);
}

void SL01_test() {
   // Poll Sensor for collect data
    SL01.poll();

    //Initialize variables
    float lux;
    lux = 0;
    float uva;
    uva = 0;
    float uvb;
    uvb = 0;
    float uv;
    uv = 0;

    // Request SL01 to return calculated UVB intensity
    lux = SL01.getLUX();
    uva = SL01.getUVA();
    uvb = SL01.getUVB();
    uv = SL01.getUVIndex();

    // Display Data on the Serial monitor
    Serial.print("Ambient Light Level: ");
    Serial.print(lux);
    Serial.print(" LUX; ");
    Serial.print("UVA Intersity: ");
    Serial.print(uv);
    Serial.print(" uW/m^2; ");
    Serial.print("UVB Intensity: ");
    Serial.print(uv);
    Serial.print(" uW/m^2; ");
    Serial.print("UVB Index: ");
    Serial.print(uv);

    Serial.println();
    delay(1000);
}

void SW01_test() {
   // Poll Sensor for collect data
    SW01.poll();

    //Initialize variables
    float alt;
    alt = 0;
    float humidity;
    humidity = 0;
    float pressure;
    pressure = 0;
    float tempC;
    float tempF;
    tempC = tempF = 0;

    // Request SL01 to return calculated UVB intensity
    alt = SW01.getAltitude(101325);
    humidity = SW01.getHumidity();
    pressure = SW01.getPressure();
    tempC = SW01.getTempC(); // Temperature in Celcuis
    tempF = SW01.getTempF(); // Temperature in Farenheit

    // Display Data on the Serial monitor
    Serial.print("Altitude: ");
    Serial.print(alt);
    Serial.print(" m; ");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %; ");
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" Pa; ");
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" C； ");
    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.print(" F");

    Serial.println();
    delay(1000);
}

void SI01_test() {
    //poll data from SI01 once
    SI01.poll();

    //print Gyro
    Serial.print("G: ");
    Serial.print(SI01.getGX(), 2);
    Serial.print(", ");
    Serial.print(SI01.getGY(), 2);
    Serial.print(", ");
    Serial.print(SI01.getGZ(), 2);
    Serial.print("; ");

    //print Accel
    Serial.print("A: ");
    Serial.print(SI01.getAX(), 2);
    Serial.print(", ");
    Serial.print(SI01.getAY(), 2);
    Serial.print(", ");
    Serial.print(SI01.getAZ(), 2);
    Serial.print("; ");

    //print Magnet
    Serial.print("M: ");
    Serial.print(SI01.getMX(), 2);
    Serial.print(", ");
    Serial.print(SI01.getMY(), 2);
    Serial.print(", ");
    Serial.print(SI01.getMZ(), 2);
    Serial.print("; ");

    //print Attitude
    Serial.print("Roll: ");
    Serial.print(SI01.getRoll(), 2);
    Serial.print("; ");
    Serial.print("Pitch :");
    Serial.print(SI01.getPitch(), 2);
    Serial.print("; ");
    Serial.print("GForce :");
    Serial.print(SI01.getGForce(), 2);

    Serial.println();
    delay(1000);
}

void SN01_test() {
    //Poll GPS Sensor once
    SN01.poll();

    //create variables
    String time;
    long latitude = 0;
    long longitude = 0;
    String date;

    //Get Date
    date = SN01.getDate();

    // Get the time from the GPS
    time = SN01.getTime();

    // Get the latitude from GPS
    latitude = SN01.getLatitude();

    // Get the longitude from GPS
    longitude = SN01.getLongitude();

    // Display the recorded data over the serial monitor
    Serial.print("GPS Time: ");
    Serial.print(time);
    Serial.print("; ");
    Serial.print("GPS Date: ");
    Serial.print(date);
    Serial.print("; ");
    Serial.print("GPS Latitude: ");
    Serial.print(latitude);
    Serial.print("; ");
    Serial.print("GPS longitude: ");
    Serial.print(longitude);

    Serial.println();
    delay(1000);
}
