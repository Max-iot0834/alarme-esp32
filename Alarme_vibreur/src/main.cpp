#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x48, 0x9D, 0x31, 0x04, 0x8F, 0xD4}; // MAC Récepteur
const int CAPTEUR_PIN = 4;
bool etatPrecedent = LOW; // Au départ, porte fermée = LOW

void setup() {
  pinMode(CAPTEUR_PIN, INPUT_PULLUP); // Important pour le 3.3V quand opto éteint
  WiFi.mode(WIFI_STA);
  esp_now_init();
  
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  bool etatActuel = digitalRead(CAPTEUR_PIN);

  // Si l'état passe de LOW (fermé) à HIGH (ouvert) -> Porte ouverte !
  if (etatPrecedent == LOW && etatActuel == HIGH) {
    esp_now_send(broadcastAddress, (uint8_t *) "ALERTE", 6);
    delay(500); 
  }
  
  etatPrecedent = etatActuel;
}