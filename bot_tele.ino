#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define sensorPin_a A0
#define LED D2
#define my_id "1208499416"

WiFiClientSecure client;

String ssid  = "TAHU BULAT";
String pass  = "cingdogan2019";
String token  = "1927620122:AAG_Lq6LyXBU1-0nhFLVOqfEv-XgrlfsGMk";

const char* bot_start = "/start";
const char* bot_info = "/info";
const char* bot_status = "/status";

int sensorValue_a = 0;
int delay_bot = 10;
long t_lasttime;

UniversalTelegramBot myBot(token, client);

void handleNewMsg(int numNewMsg) {
//  Serial.println("handleNewMsg");
  Serial.println(String(numNewMsg));

  for (int i = 0; i < numNewMsg; i++) {
    String chat_id = String(myBot.messages[i].chat_id);
    String pesan = myBot.messages[i].text;
    String from_name = myBot.messages[i].from_name;
    String welcome, info_bot, fire_status, info_status;

    if (from_name == "") {
      from_name = "Guest";
    }

    else if (pesan == (bot_info)) {
      info_bot = "fireBot merupakan bot Telegram yang digunakan untuk ";
      info_bot += "melaporkan titik api yang dapat memicu terjadinya kebakaran.\n";
      info_bot += "Project ini dibuat untuk menyelesaikan tugas pada mata kuliah Mikrokontroller 2.\n";
      info_bot += "Kelompok : Rizky Andhika A & M. Zaky Al-Farish";
      myBot.sendMessage(chat_id, info_bot, "");
    }

    else if (pesan == (bot_start)) {
      welcome = "Selamat datang di bot kami, " + from_name + "!\n";
      welcome += "Pendeteksi titik api dengan peringatan dini melalui Telegram.\n";
      welcome += (bot_info);
      welcome += " <-- info mengenai Bot\n";
      welcome += (bot_status);
      welcome += " <-- status kondisi saat ini";
      myBot.sendMessage(chat_id, welcome, "Markdown");
    }

    if (sensorValue_a < 100) {
      fire_status = "Api kecil terdeteksi pada ruangan 1 \n";
      myBot.sendMessage(fire_status, "");
      String pesan = myBot.messages[i].text;
      if (pesan == (bot_status)) {
        info_status = "Ruangan 1 status TIDAK AMAN";
        myBot.sendMessage(chat_id, info_status, "");
      }
      delay(100);
    }

    else if (sensorValue_a > 1023) {
      String pesan = myBot.messages[i].text;
      if (pesan == (bot_status)) {
        info_status = "Ruangan 1 status AMAN";
        myBot.sendMessage(chat_id, info_status, "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, pass);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setInsecure();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensorValue_a = analogRead(sensorPin_a);
  Serial.print("Sensor value analog : "); Serial.println(sensorValue_a);
  if (millis() > t_lasttime + delay_bot) {
    int numNewMsg = myBot.getUpdates(myBot.last_message_received + 1);
    while (numNewMsg) {
      //      Serial.println("Got response");
      handleNewMsg(numNewMsg);
      //      Serial.println(numNewMsg);
      numNewMsg = myBot.getUpdates(myBot.last_message_received + 1);
    }
    t_lasttime = millis();
  }
  if (sensorValue_a < 100) {
    digitalWrite(LED, HIGH);
    myBot.sendMessage(my_id, "Api kecil terdeteksi pada Ruangan 1");
    delay(1);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
