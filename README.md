﻿# ESP32-RemoteControl
Program allow control ESP32 module GPIO pins via html page.
Module has been configured as an access point and an http server.
Server return a really ugly http page to control gpio's by 4 buttons or keyboard.

#How it works:
After the module is powered, it starts the Access Point WiFi with the name specified in main.c as EXAMPLE_ESP_WIFI_SSID parameter.
the connection requires authorization with the password - EXAMPLE_ESP_WIFI_PASS.
When connection is established, DHCP assigns us an IP address and we can connect to the HTTP server by typing 'my-esp32.local' in the browser. 
All stages and necessary information (IP addresses) are logged in the serial monitor with speed 115200 b/s.
