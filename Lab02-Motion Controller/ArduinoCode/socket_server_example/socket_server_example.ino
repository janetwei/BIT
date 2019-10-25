#include "ESP8266WiFi.h"
#include "WiFiClient.h"

#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//===============================================
// WiFi config
//===============================================
/***** YOUR CODE HERE (START) *****/
const char* ssid = "miyatake";
const char* password = "hogefuga";
IPAddress staticIP(172, 20, 10, 2); // For different devices, change this static ip address
IPAddress gateway(172, 20, 10, 1);
IPAddress subnet(255, 255, 255, 240);
/***** YOUR CODE HERE (END) *****/

//===============================================
// Server
//===============================================
WiFiServer server(80);


int16_t ax, ay, az;
int16_t gx, gy, gz;
MPU6050 accelgyro;

// set the button
int buttonPin = D3;
int buttonVal;

#define OUTPUT_READABLE_ACCELGYRO

//===============================================
// Setup
//===============================================
void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  
  Serial.begin(115200);
  WiFi.disconnect();
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  WiFi.mode(WIFI_STA);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP -> ");
  Serial.println(WiFi.localIP());
  Serial.println();

  server.begin();
  
  // initailize device
  accelgyro.initialize();

  pinMode(buttonPin, INPUT); 
}

//===============================================
// Loop
//===============================================
void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if (!client){
    Serial.println("Wait for client...");
    delay(100);
    return ;
  }


  Serial.println("A new client is connected!");

  String data = "";
  String message;
  while (client.connected()) {
    while (client.available()>0) {
      data += char(client.read());
    }
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    buttonVal = digitalRead(buttonPin);
    if (data != ""){
      //Serial.println(data);
      Serial.print("a/g:\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.print("\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.println(gz);
      //client.print("Hi! I am server~");
      message = String(buttonVal) + " "  + String(ax) + " " + String(ay) + " " + String(az) + " " + String(gx) + " " + String(gy) + " " + String(gz);
      client.print(message);
//      client.print(ax); client.print(" ");
//      client.print(ay); client.print(" ");
//      client.print(az); client.print(" ");
//      client.print(gx); client.print(" ");
//      client.print(gy); client.print(" ");
//      client.println(gz);
      data = "";
    }
    delay(10);
  }
  client.stop();
  Serial.println("Client disconnected");
}
