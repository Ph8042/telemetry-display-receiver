# telemetry-display-receiver
MQTT telemetry sub with display feature  
Date: 01-02-2025  

Simple display with microcontroller.    
In my case I have used esp32 alongside tiny OLED display.  
Receiver catches my MQTT publications from telemetry topics.   

Pin connection setup:  
- (display) GND -> GND (ESP32)  
- (display) VDD -> 3.3V (ESP32)  
- (display) SCK(scl) -> GPIO 22 (d22) (ESP32) (default scl pin)  
- (display) SDA -> GPIO 21 (d21) (ESP32) (default sda pin)  

Please don't mind cable colors :D   
![[oled_display_test.png]]

