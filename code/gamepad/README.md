# Gamepad controls for ESP8266

## Usage
- Open `web/index.html` in your browser
- Open the JavaScript console to observe the logs
- Connect a gamepad to your computer, make sure a connection confirmation has been logged in the console
- Open `gamepad.ino` in Arduino IDE and modify your WiFi credentials
- Upload the script to your ESP8266
- Open the serial monitor on 115200 baud to observe the logs of the microcontroller
- Extract its IP address from the logs and enter it in the input field on top of the web page

Pressing a button on your gamepad should send the related data to the ESP8266. Both sending and receiving should appear in their respective logs.