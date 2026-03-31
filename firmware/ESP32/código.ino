#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ── Pinos ─────────────────────────────
const int DHT_PIN = 15;
const int LED_VERDE = 18;
const int LED_VERMELHO = 23;

// ── WiFi ─────────────────────────────
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ── MQTT (SUA VPS) ───────────────────
const char* mqtt_server = "134.199.142.253";
const int mqtt_port = 1883;
const char* client_id = "escola/grupoG";

// ── Tópicos ──────────────────────────
const char* topico_temp = "escola/grupoG/frigorifico/temperatura";
const char* topico_alerta = "escola/grupoG/frigorifico/alerta";

// ── Objetos ──────────────────────────
WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dht;

// ── Controle ─────────────────────────
bool alertaAtivo = false;
unsigned long lastMsg = 0;

// ── WiFi ─────────────────────────────
void setup_wifi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

// ── MQTT ─────────────────────────────
void reconnect() {
  if (client.connected()) return;

  Serial.print("Conectando ao MQTT...");

  String clientId = client_id;
  clientId += String(random(1000, 9999)); // evita conflito

  if (client.connect(clientId.c_str())) {
    Serial.println(" conectado!");
  } else {
    Serial.print(" erro=");
    Serial.println(client.state());
  }
}

// ── Setup ────────────────────────────
void setup() {
  Serial.begin(115200);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
}

// ── Loop ─────────────────────────────
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();

  if (now - lastMsg > 5000) { // a cada 5 segundos
    lastMsg = now;

    TempAndHumidity data = dht.getTempAndHumidity();

    if (isnan(data.temperature)) {
      Serial.println("Erro ao ler sensor!");
      return;
    }

    float temp = data.temperature;

    Serial.println("Temperatura: " + String(temp) + " °C");

    // ── Controle de faixa ────────────
    bool foraFaixa = (temp < 1 || temp > 5);

    if (!foraFaixa) {
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      alertaAtivo = false;

    } else {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);

      if (!alertaAtivo) {
        String alerta = "ALERTA! Temp fora da faixa: " + String(temp) + " C";
        client.publish(topico_alerta, alerta.c_str());

        Serial.println(">>> ALERTA ENVIADO <<<");
        alertaAtivo = true;
      }
    }

    // ── Publicação MQTT ─────────────
    char bufTemp[8];
    dtostrf(temp, 4, 1, bufTemp);
    client.publish(topico_temp, bufTemp);

    Serial.printf("MQTT → Temp: %s °C\n", bufTemp);
  }
}
