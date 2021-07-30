# ESP32-Work_STA.AP_Simultaneously
ESP32 work as STA &amp; AP Mode Simultaneously  , and work as STA (OR) AP to control LED
 <p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127690600-f460dfcb-3c55-4b82-93fe-34dd2ef2eccb.png">
 <br>

# Task description
1.Connect with ESP32 
2.ESP32 will be programmed in order to connect the robot's tablet with the ESP32 
3.connect the ESP32 with an existing network.

so ESP32 will work as Acsses point and SAT mode


# Implementation
I wrote and attached 3 codes
1. ESP32 work as Acsses Point To sontrol LED from Web server , that means it'll be like a router has its own network name and Password , and you have to connect to the network to control it.
 <p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127690230-4bede2d8-d51b-4743-86c4-9269b28c7f4c.png">
 <br>
Figure 1: ESP32 as Acsses Point</p>

2. ESP32 Work in Station mode to control lED from Web server ,  this means that the ESP32 will be defined as the Wi-Fi network in the area, to be controlled by the same Wi-Fi network
<p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127690302-35d16aff-9f8f-40c2-abbf-9990265a2c7e.png">
<br> 
Figure 2: ESP32 Station mode</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127690378-4d9304ab-96b4-41d3-b908-23f46b82b5d0.png">
<br> 
Figure 3: simple ESP32 Web server to control LED</p>

3. The ESP32 will work as STA & AP mode Simultaneously in the same time , so you can connect with ESP32 wifi or the Area network wifi Which you will define in the code.


# Tools used
- ESP32 
- LED and wire 
- Ardiono IDE , installing the board model of esp32 and the libbry wich describe in the code .


# Code 
I added notes and explanation in the code

# Expirement 

1. Code 1 & 2 Video ( AP mode then SAT mode to control 3 LEDs)

<br>


https://user-images.githubusercontent.com/85633958/127688819-203913fd-c70d-4e74-9ea9-f48769c4fe6a.MOV

<br>

2. Code 3 (AP & SAT Simultaneously ) 

On a computer connected to the same WiFi network as the ESP32, open a web browser and type the following URL:


```C++
http://your_ESP_IP/hello
```




<p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127688999-71ee86d1-9296-4add-b8ae-42fa4756bb94.png">
<br> 
Figure 4:  Answer from the HTTP server, when the request comes from the ESP32 station interface.</p>

<p align="center">
<img src="https://user-images.githubusercontent.com/85633958/127689025-9d05a317-0229-4e3a-b006-d7531c8bbffa.png">
<br> 
Figure 5: Answer from the HTTP server, when the request comes from the ESP32 soft AP interface.</p>
