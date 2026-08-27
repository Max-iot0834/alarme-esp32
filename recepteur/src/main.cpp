#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURATION PIN ---
const int BUZZER_PIN = 23; 
const int BTN_PIN = 27; 

Adafruit_SSD1306 display(128, 64, &Wire, -1);

RTC_DATA_ATTR bool alarmeActive = true; 
bool alarmeEnCours = false;

// LOGIQUE ROBUSTE : 
// Si etat = true (ALERTE) -> Mode OUTPUT + LOW (Active le buzzer)
// Si etat = false (REPOS) -> Mode INPUT (Désactive physiquement la broche)
void commandeBuzzer(bool etat) {
  if (etat) {
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    pinMode(BUZZER_PIN, INPUT);
  }
}

void majEcran() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("ALARME");
  display.setTextSize(2);
  display.println(alarmeActive ? "ACTIVE" : "DESACTIV.");
  display.display();
}

void miseEnSommeil() {
  commandeBuzzer(false); // Coupure physique
  display.clearDisplay();
  display.println("EXTINCTION...");
  display.display();
  delay(1000);
  display.ssd1306_command(SSD1306_DISPLAYOFF);
  
  while(digitalRead(BTN_PIN) == LOW); 
  
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BTN_PIN, 0); 
  esp_deep_sleep_start();
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  if (alarmeActive && !alarmeEnCours) {
    alarmeEnCours = true;
    commandeBuzzer(true); // Active le buzzer
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("!!! ALERTE !!!");
    display.display();
  }
}

void setup() {
  // Initialisation au repos
  pinMode(BUZZER_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  Wire.begin(21, 22);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.ssd1306_command(SSD1306_DISPLAYON);
  
  majEcran();

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  if (digitalRead(BTN_PIN) == LOW) {
    unsigned long debutAppui = millis();
    while (digitalRead(BTN_PIN) == LOW) {
      if (millis() - debutAppui > 5000) miseEnSommeil();
      delay(10);
    }

    if (alarmeEnCours) {
      alarmeEnCours = false;
      commandeBuzzer(false); // Coupe le buzzer (passe en INPUT)
    } else {
      alarmeActive = !alarmeActive;
    }
    majEcran();
  }
}