#include <ESP8266WiFi.h>
#include <MQ2.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define led 4
#define mq2Pin A0
#define sensorPin_d 12

// ---- WIFI Connection ---------------
WiFiClientSecure client;

String ssid  = "KONZ";
String pass  = "CINGDOGAN2019";
// ---- end ---------------------------

// ----- to Telegram -------------
#define my_id "1208499416"
String token  = "1927620122:AAG_Lq6LyXBU1-0nhFLVOqfEv-XgrlfsGMk";
const char* bot_start = "/start";
const char* bot_info = "/info";
const char* bot_status = "/status";
int delay_bot = 1;
long t_lasttime;
MQ2 mq2(mq2Pin);
float asap;
int sensorValue_d;
UniversalTelegramBot myBot(token, client);
// ----- end ---------------------

// ------- variable nodeMCU Communication -------
unsigned long prevMillis = 0;
const long interval = 1000;
String arrData[2];
int data1, data2;
// ------------------- END ----------------------

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  mq2.begin();
  //================ Connect to WIFI ============
  WiFi.begin(ssid, pass);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  client.setInsecure();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //============ END ==========================
}

void loop() {
  asap = mq2.readSmoke();
  sensorValue_d = digitalRead(sensorPin_d);
  Serial.print("asap : "); Serial.println(asap);
  Serial.print("flame : "); Serial.println(sensorValue_d);

  // for Telegram Menu's ==============================
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
  // end ==============================================
  if (asap > 1 and sensorValue_d == 0) {
    digitalWrite(led, HIGH);
    myBot.sendMessage(my_id, "Api terdeteksi pada Ruangan 1");
  }
  else {
    digitalWrite(led, LOW);
  }
}
