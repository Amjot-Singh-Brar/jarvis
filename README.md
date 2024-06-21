# Jarvis

## Meet Jarvis your personal assistant 
Telegram bot based personal assitant, it can help you 'turn on/off your PC' or you can take photos, turn on/off the security mode, and get to know the weather using 2 different  temperature/humidity sensors.

## Componets used:
	1. ESP 32
	2. ESP 32cam
	3. 2x DHT22
	4. PIR sensor
	5. relay module or optocoupler
	6. 128x64 (1.3 inch) OLED 

## Wiring:
	ESP32:
		GPIO 27 --> Out (DHT22 internal)*
		GPIO 14 --> Out (DHT22 external)*
		GPIO 2  --> IN (relay module)*
		GPIO 22 --> SCL (OLED)*
		GPIO 21 --> SDA (OLED)*

	ESP32cam:
		GPIO 13 --> OUT (PIR sensor)*

	relay module with your PC:
		front panel power switch connections --> NO and COM (relay module)

	*connect the power and ground pins accordingly.

## Features:
1. Turn on/off your PC
2. Capture a Photo
3. Turn on/off security mode
4. Get to know the temperature and humidity:
 inside your home or even outside!!

## How to use it:
--> Enter your bot_ID and chat_ID in the code.

--> Provide the wifi credentials as well.

--> Upload jarvis_esp32 and jarvis_esp32Cam to corresponding microcontrollers.

--> type **/jarvis** to get to know all the commands in telegram 

--> Various commands present in this assitant:

	○ /Turn_ON_PC - Turn on/off PC
    ○ /photo - Take a photo
    ○ /security_on - Activate security mode
    ○ /security_off - Deactivate security mode
    ○ /internal_temp - Get the Internal Temperature and Humidity


