#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"

//===============================================
// WiFi config
//===============================================
/***** YOUR CODE HERE (START) *****/
const char* ssid = "miyatake";
const char* password = "hogefuga";
IPAddress staticIP(172, 20, 10, 2); // For different devices, change this static ip address
IPAddress gateway(172, 20, 10, 1);
IPAddress subnet(255, 255, 255, 240);
/****** YOUR CODE HERE (END) ******/

//===============================================
// Server
//===============================================
ESP8266WebServer server(80);

//===============================================
// Functions
//===============================================
// For checking whether this WiFi board has been assigned to a static ip address

void handleCheckConnection(){
  Serial.println("Connect Successfully");
  server.send(200, "text/html", "success");
}
// Test - How arduino gets the paremeters
void handleGetArgTest(){
  for (int i = 0 ; i < server.args() ; i++){
    Serial.print("Arg ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(server.arg(i));
  }
  server.send(200, "text/html", "success");
}
// Example - You can copy this function for implementation.
void handleExampleFunction(){
  server.send(200, "text/html", "Hello World!");
}

//===============================================
// Setup
//===============================================
void setup() { 
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
  Serial.println(WiFi.localIP());

  server.on("/", handleCheckConnection);
  server.on("/GetArgTest", handleGetArgTest);
  server.on("/ExampleFunction", handleExampleFunction);
  //------- Add new function in this block -------//
  // Your function here
  
  //----------------------------------------------//
  server.begin();
}

//===============================================
// Loop
//===============================================
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
