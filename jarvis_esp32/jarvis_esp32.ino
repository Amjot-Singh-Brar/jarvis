#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

/////////////////////////////////////
#include <DHT.h>
// Define the DHT22 sensor type and the GPIO pin it is connected to
#define DhtPin_internal 27
#define DhtPin_external 14//OK
#define DHTTYPE DHT22

// Create a DHT object
DHT dht_internal(DhtPin_internal, DHTTYPE);
DHT dht_external(DhtPin_external, DHTTYPE);

// Task handles
TaskHandle_t Task1;
TaskHandle_t Task2;

////////////////////////////////////
#include <U8g2lib.h>
////////////////////////////////////

////////////////////////////////////
// OLED
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
/////////////////////////////////////

char ssid[] = "xxxxxxxxxxxxxx";
char password[] = "xxxxxxxxxxxxx";
#define TELEGRAM_BOT_TOKEN "xxxxxxxxxxxxxxx"
String CHAT_ID = "xxxxxxxxx";
WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);
#define LED_PIN 2
int delayBetweenChecks = 300;
unsigned long lastTimeChecked;

void setup(){
	// Setup the oled display
	u8g2.begin();
  
	// Setup the temperature board
	Serial.begin(115200);

  // Create tasks
xTaskCreatePinnedToCore(
  task1,          // Function to implement the task
  "Task1",        // Name of the task
  10000,          // Stack size in words
  NULL,           // Task input parameter
  1,              // Priority of the task
  &Task1,         // Task handle
  0);             // Core where the task should run

xTaskCreatePinnedToCore(
  task2,          // Function to implement the task
  "Task2",        // Name of the task
  10000,          // Stack size in words
  NULL,           // Task input parameter
  1,              // Priority of the task
  &Task2,         // Task handle
  1);             // Core where the task should run

	dht_internal.begin();
	dht_external.begin();
	Serial.println("DHT22 sensor setup complete.");


	// Setup the Cam board
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);

	pinMode(2, OUTPUT);
	digitalWrite(2, LOW);

	Serial.print("Connecting Wifi: ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	client.setInsecure();
	bot.longPoll = 60;
}

unsigned long previousMillis = 0;   // Stores the last time the code block was executed
const long INTERVAL = 20000;

void message_handling(int numNewMessages){

	for (int i = 0; i < numNewMessages; i++){
		if (bot.messages[i].type ==  F("callback_query")) {
			String text = bot.messages[i].text;
			Serial.print("Call back button pressed with text: ");
			Serial.println(text);
		}
		else{
			String chat_id = String(bot.messages[i].chat_id);
			String text = bot.messages[i].text;
      if (text == "/jarvis"){
        String welcome = "Welcome Sir what may I help you today with\n";
        welcome += "/Turn_ON_PC - Turn on/off PC\n";
        welcome += "/photo - Take a photo\n";
        welcome += "/security_on - Activate security mode\n";
        welcome += "/security_off - Deactivate security mode\n";
        welcome += "/internal_temp - Get the Internal Temperature and Humidity\n";
        welcome += "/external_temp - Get the External Temperature and Humidity\n";
        bot.sendMessage(CHAT_ID, welcome, "");
      }
      // Turn_ON_PC Command
      else if (text == F("/Turn_ON_PC")) {
        unsigned long currentMillis = millis();

        // Check if 20 seconds have passed since the last execution
        if (currentMillis - previousMillis >= INTERVAL) {
          // Save the last execution time
          previousMillis = currentMillis;

          // Execute the code block
          bot.sendMessage(chat_id, "Turning Your PC ON Now Sir", "Markdown");
          digitalWrite(LED_PIN, HIGH);
          delay(500);
          digitalWrite(LED_PIN, LOW);
        }
        else{
          String remainingWaitTime = String((INTERVAL - (currentMillis - previousMillis))/1000);
          bot.sendMessage(CHAT_ID, "Turn On PC cmd recieved already, please wait..." + remainingWaitTime + "s");
        }	
			}
      // internal_temp Command
      else if (text == "/internal_temp"){
        String tH = internal();
        Serial.println(tH);
        bot.sendMessage(chat_id, tH);
      }
      // external_temp Command
      else if (text == "/external_temp"){
        String tH = external();
        Serial.println(tH);
        bot.sendMessage(chat_id, tH);
      }
	}
    Serial.println("doing something with the board and sensors...");
	}

}

void loop() {}

void task1(void * parameter) {
  while(1){
    updateDisplay();
  }
}

void task2(void * parameter) {
  while(1){
    // Check for updates every 5 seconds (adjust as needed)
    static unsigned long lastUpdateTime = 0;
    const unsigned long updateInterval = 2000; // 2 seconds
    if (millis() - lastUpdateTime >= updateInterval) {
      lastUpdateTime = millis();
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

      if (numNewMessages) {
        Serial.println("Got response");
        message_handling(numNewMessages);
      }
    }
  }
}
