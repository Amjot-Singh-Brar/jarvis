# jarvis
Meet Jarvis your personal assistant 
## Componets used:
	1. ESP 32
	2. ESP 32cam
	3. 2x DHT22
	4. PIR sensor
	5. relay module or optocoupler
	6. 1.3 inch OLED 

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
