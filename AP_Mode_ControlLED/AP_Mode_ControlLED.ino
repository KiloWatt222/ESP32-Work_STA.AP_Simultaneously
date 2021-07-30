
//ESP32 Work on AP Mode to Control LED

 #include <WiFi.h>  
   
 #define A_LED  2  
 #define B_LED  16  
 #define C_LED   18  
   
 // Create the objects for server and client  
 WiFiServer server(80);  
 WiFiClient client;  
   
 const char* ssid   = "ESP32-AP-Simple";// This is the SSID that ESP32 will broadcast  
 const char* password = "12345678";     // password should be atleast 8 characters to make it work  
   
 // Create the global variable  
 String http;  
 String aLedState = "off";  
 String bLedState = "off";  
 String cLedState = "off";  
   
 void setup() {  
  Serial.begin(115200);  
  pinMode(A_LED, OUTPUT);  
  pinMode(B_LED, OUTPUT);  
  pinMode(C_LED, OUTPUT);  
  digitalWrite(A_LED, LOW);  
  digitalWrite(B_LED, LOW);  
  digitalWrite(C_LED, LOW);  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
   
  // Create the ESP32 access point  

  WiFi.softAP(ssid, password);  
   
  Serial.println( "" );  
  Serial.println( "WiFi AP is now running" );  
  Serial.println( "IP address: " );  
  Serial.println( WiFi.softAPIP() );  
   
  // Start our ESP32 server  
  server.begin();  
 }  
   
 void loop(){  
    
  if ( client = server.available() ) {  // Checks if a new client tries to connect to our server  
   Serial.println("New Client.");  
   String clientData = "";  
   while ( client.connected() ) {    // Wait until the client finish sending HTTP request  
    if ( client.available() ) {     // If there is a data,  
     char c = client.read();      //  read one character  
     http += c;            //  then parse it  
     Serial.write(c);    
     if (c == '\n') {         // If the character is carriage return,   
                      //  it means end of http request from client  
      if (clientData.length() == 0) { //  Now that the clientData is cleared,  
       sendResponse();        //    perform the necessary action  
       updateLED();  
       updateWebpage();  
       break;  
      } else {  
       clientData = "";       //  First, clear the clientData  
      }  
     } else if (c != '\r') {      // Or if the character is NOT new line  
      clientData += c;        //  store the character to the clientData variable  
     }  
    }  
   }   
   http = "";  
   client.stop();            // Disconnect the client.  
   Serial.println("Client disconnected.");  
   Serial.println("");  
  }  
 }  
   
 void sendResponse() {  
  // Send the HTTP response headers  
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-type:text/html");  
  client.println("Connection: close");  
  client.println();   
 }  
   
 void updateWebpage() {  
  // In here we will display / update the webpage by sending the HTML   
  //  to the connected client  
  // In order for us to use the HTTP GET functionality,  
  //  the HTML hyperlinks or href is use in the buttons.   
  //  So that, when you press the buttons, it will send a request to the   
  //  web server with the href links by which our ESP32 web server will  
  //  be check using HTTP GET and execute the equivalent action  
    
  // Send the whole HTML  
  client.println("<!DOCTYPE html><html>");  
  client.println("<head>");  
  client.println("<title>ESP32 WiFi Station</title>");  
  client.println("</head>");  
    
  // Web Page Heading  
  client.println("<body><h1>'SmartMethode' simple ESP32 AP Web server</h1>");  
   
  // Display buttons for A LED  
  client.println("<p>1. A LED is " + aLedState + "</p>");    
  if (aLedState == "off") {  
   client.println("<p><a href=\"/A_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/A_LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
    
  // Display buttons for B LED  
  client.println("<p>2. B LED is " + bLedState + "</p>");    
  if (bLedState == "off") {  
   client.println("<p><a href=\"/B_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/B_LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
      
  // Display buttons for C LED  
  client.println("<p>3. C LED is " + cLedState + "</p>");    
  if (cLedState == "off") {  
   client.println("<p><a href=\"/C_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/C_LED/off\"><button>Turn OFF</button></a></p>");  
  }  
   
  client.println("</body></html>");  
  client.println();  
 }  
   
 void updateLED() {  
  // In here we will check the HTTP request of the connected client  
  //  using the HTTP GET function,  
  //  Then turns the LED on / off according to the HTTP request  
  if    (http.indexOf("GET /A_LED/on") >= 0) {  
   Serial.println("A LED on");  
   aLedState = "on";  
   digitalWrite(A_LED, HIGH);  
  } else if (http.indexOf("GET /A_LED/off") >= 0) {  
   Serial.println("A LED off");  
   aLedState = "off";  
   digitalWrite(A_LED, LOW);  
  } else if (http.indexOf("GET /B_LED/on") >= 0) {  
   Serial.println("B LED on");  
   bLedState = "on";  
   digitalWrite(B_LED, HIGH);  
  } else if (http.indexOf("GET /B_LED/off") >= 0) {  
   Serial.println("B LED off");  
   bLedState = "off";  
   digitalWrite(B_LED, LOW);  
  } else if (http.indexOf("GET /C_LED/on") >= 0) {  
   Serial.println("C LED on");  
   cLedState = "on";  
   digitalWrite(C_LED, HIGH);  
  } else if (http.indexOf("GET /C_LED/off") >= 0) {  
   Serial.println("C LED off");  
   cLedState = "off";  
   digitalWrite(C_LED, LOW);  
  }  
 }  
