
#define WIFI_SSID "wifi"
#define WIFI_PASS "pass"
#define VERSION "LiTec.SSH.(Bot.0.0.3v)&(Web.0.0.1v)"

#define BOT_TOKEN "5256737385:AAHlQd83rrsgc5vwjL0k-6mDYfsz7J_ZD7I"
#define PIN_TRANSMIT 1
#define MAX_USERS 10
#define MAX_ADMINS 2

#include <setting.h>
#include <FastBot.h>
#include <RCSwitch.h>
#include <GyverPortal.h>

FastBot bot(BOT_TOKEN);
RCSwitch mySwitch = RCSwitch();
GyverPortal portal;
bool m1, m2, m3;

String user_chatID[MAX_USERS] = { "1763784965", "707106984" };
byte count;
bool use_all = false;
bool updateFlag = false;
int sendMessageAll = 0;
String IPaddress;

bool kyx_A;
bool kyx_B;
bool kop_A;
bool kom_A;
bool kop_moveSensor;
int kop_moveSensorInterval = 10;

void setup() {
  
  delay(2000);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() > 15000) ESP.restart();
  }
  Serial.read();
  IPaddress = WiFi.localIP().toString();
  Serial.println("Connected");

  bot.attach(newMsg);
  portal.attachBuild(build);
  portal.attach(action);
  portal.start();
  
  mySwitch.enableTransmit(PIN_TRANSMIT);

  for(int i = MAX_ADMINS; i < MAX_USERS; i++){
    user_chatID[i] = "NaN";
  }
}

void loop() {
  portal.tick();
  bot.tick();
}
