#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#define BLYNK_TEMPLATE_ID "TMPL6gmH53mtB"
#define BLYNK_TEMPLATE_NAME "UAP"
#define BLYNK_AUTH_TOKEN "bv0kNmOYxOGAtvnFz79UTQWJpEvZZdar"

// Data koneksi WiFi
char auth[] = "bv0kNmOYxOGAtvnFz79UTQWJpEvZZdar";
char ssid[] = "Faisal";
char password[] = "faisal1409";

Servo myServo;
int ServoPIN = 18;

void setup() {
  myServo.attach(18);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);

  pinMode(ServoPIN, OUTPUT);

  // Inisialisasi nilai default
  digitalWrite(ServoPIN, LOW);

  // Fungsi untuk memanggil BLYNK_WRITE pada saat nilai pin virtual berubah
  Blynk.virtualWrite(V0, digitalRead(ServoPIN));

}

void loop() {
  Blynk.run(0);
  if(Serial.available()){
    int angle = Serial.parseInt();
    myServo.write(angle);
  }
}

void readDoorState() {
  int currentState = digitalRead(ServoPIN);
  Blynk.virtualWrite(V0, currentState);
}

// Fungsi yang dipanggil saat nilai pin virtual berubah di aplikasi Blynk
BLYNK_WRITE(V0) {
  int angle = param.asInt();
  myServo.write(angle);
  Blynk.virtualWrite(V1, angle);
}