
//ESP32 work as STA & AP Mode Simultaneously ~

#include <WiFi.h> //instal before 
#include <ESPAsyncWebServer.h>  // instal before from (https://github.com/me-no-dev/ESPAsyncWebServer)
//^^This library which exposes to us the functions we need to setup the HTTP web server.

//WiFi network to which the ESP32 will connect 
const char* wifi_network_ssid = "YourNetwork";
const char* wifi_network_password = "YourNetworkPassword";

//hold the SSID and the password of the soft AP (defined by us).
const char *soft_ap_ssid = "SMART_METHODE_ESP32";
const char *soft_ap_password = "robot123";

// this class receives the port where the server will be listening for incoming requests. We will use port 80, which corresponds to the default HTTP port 
AsyncWebServer server(80);


 
void setup() {
 
  Serial.begin(115200);    //opening a serial connection, to later output some results from our program.
  WiFi.mode(WIFI_MODE_APSTA);  // call the mode method , set the ESP32 to work in soft AP and station modes simultaneously.
 
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
 
  WiFi.begin(wifi_network_ssid, wifi_network_password);
 
   //poll the status the connection, until it is established.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
 
  Serial.print("ESP32 IP on the WiFi network: ");
  Serial.println(WiFi.localIP());
 
 
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest * request) {
 
    if (ON_STA_FILTER(request)) {
      request->send(200, "text/plain", " Hello 'SmartMethod' You are in STA Mode!");
      Serial.print("ESP32 Connected to WiFi Network");
      return;
 
    } else if (ON_AP_FILTER(request)) {
      request->send(200, "text/plain", "Hello 'SmartMethod' You are in AP Mode");
      return;
    }
 
    request->send(200, "text/plain", "Hello from undefined");
  });
     server.begin();
}


void loop() {}
