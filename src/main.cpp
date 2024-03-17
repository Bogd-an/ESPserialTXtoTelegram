#include <Arduino.h>   //Видалити, якщо в ArduinoIDE
#include <WiFi.h>
#include <HardwareSerial.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Налаштування Wi-Fi
#define WIFI_SSID     " "
#define WIFI_PASSWORD " "

// Налаштування Telegram
#define BOT_TOKEN " "
#define CHAT_ID " "

#define NAME "ESPserialTX"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  // attempt to connect to Wifi network:
  Serial.print("\nConnecting to Wifi SSID " + String(WIFI_SSID));
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Add root certificate for api.telegram.org
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  while (WiFi.status() != WL_CONNECTED)  {
    Serial.print(".");
    delay(500);
    digitalWrite(2, !digitalRead(2));
  }
  Serial.print("\nWiFi connected. IP address: "+String(WiFi.localIP()));
  bot.sendMessage(CHAT_ID, String(NAME)+"0 online", "");
}

void loop(){
  // Чи прийшли нові данні?
  if (Serial.available() > 0) {
    digitalWrite(2, 1);
    // читання рядка з Serial до символу нового рядка
    String message = Serial.readStringUntil('\n'); 
    // Відправка отриманого повідомлення у Telegram
    bot.sendMessage(CHAT_ID, message, "");
    Serial.println("Bot send: " + message);
  }
  digitalWrite(2, 0);
}


// //Код для ехо
//
// #define BOT_MTBS 1000; // mean time between scan messages
// unsigned long bot_lasttime; // last time messages' scan has been done
// void handleNewMessages(int numNewMessages) {
//   for (int i = 0; i < numNewMessages; i++) {
//     bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
//   }
// }
// void echoLoop(){
//   if (millis() - bot_lasttime > BOT_MTBS) {
//     int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     while (numNewMessages) {
//       Serial.println("got response");
//       handleNewMessages(numNewMessages);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }
//     bot_lasttime = millis();
//   }
// }