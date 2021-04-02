#include <WiFi.h>
#include <FirebaseESP32.h>
#define WIFI_SSID "******"
#define WIFI_PASSWORD "*******"
#define FIREBASE_HOST "https://homeautomation-xxxxxxxxxt-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "32SyOLiXu3MkCxDgomrXiwMVcxxxxxxxxxxxxxxx"
#define tubel 3
#define diml 2
#define fanl 14
#define extnsnl 15
#define musicl 13
FirebaseData fbdo;
String tube = "",dim = "", extnsn="" ,fan ="" ,music ="";
void setup()
{

  Serial.begin(115200);
  pinMode(tubel,OUTPUT);
  pinMode(diml,OUTPUT);
  pinMode(fanl,OUTPUT);
  pinMode(extnsnl,OUTPUT);
  pinMode(musicl,OUTPUT);
  digitalWrite(tubel,HIGH);
  digitalWrite(diml,HIGH);
  digitalWrite(fanl,HIGH);
  digitalWrite(extnsnl,HIGH);
  digitalWrite(musicl,HIGH);
  connect_wifi();
  relay_check();
  delay(2000);
}

void loop()
{
  relay_check();
  Serial.println("________________________________________________________________");
  delay(100);
}
void connect_wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  relay_check();
}
void relay_check()
{
  if(Firebase.get(fbdo, "/tube_light"))
  {
      tube = fbdo.stringData();
      Serial.println("Tube:"+tube);
      if(tube == "OFF")
        digitalWrite(tubel,HIGH);
      if(tube == "ON")
        digitalWrite(tubel,LOW);
  }
  if(Firebase.get(fbdo, "/dim_light"))
  {
      dim = fbdo.stringData();
      Serial.println("Dim:"+dim);
      if(dim == "OFF")
        digitalWrite(diml,HIGH);
      if(dim == "ON")
        digitalWrite(diml,LOW);
  }
  if(Firebase.get(fbdo, "/fan"))
  {
      fan = fbdo.stringData();
      Serial.println("Fan:"+fan);
      if(fan == "OFF")
        digitalWrite(fanl,HIGH);
      if(fan == "ON")
        digitalWrite(fanl,LOW);
  }
  if(Firebase.get(fbdo, "/extnsn"))
  {
      extnsn = fbdo.stringData();
      Serial.println("Extnsn:"+extnsn);
      if(extnsn == "OFF")
        digitalWrite(extnsnl,HIGH);
      if(extnsn == "ON")
        digitalWrite(extnsnl,LOW);
  }
  if(Firebase.get(fbdo, "/music"))
  {
      music = fbdo.stringData();
      Serial.println("Music:"+music);
      if(music == "OFF")
        digitalWrite(musicl,HIGH);
      if(music == "ON")
        digitalWrite(musicl,LOW);
  }
}
