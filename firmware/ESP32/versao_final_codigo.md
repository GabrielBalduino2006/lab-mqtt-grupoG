#  Firmware ESP32 — Versão Final

## Data de desenvolvimento

25 de Março de 2026

## Objetivo

Integrar o sistema de leitura de temperatura com comunicação MQTT, permitindo monitoramento remoto em tempo real e envio de alertas automáticos.

## Funcionamento

O sistema utiliza um sensor DHT22 conectado ao pino 15 do ESP32 para realizar a leitura da temperatura.

A cada ciclo de execução:

- O sensor coleta a temperatura do ambiente
- O valor é validado para evitar leituras inválidas
- A temperatura é exibida no monitor serial
- O valor é comparado com a faixa segura (1°C a 5°C)

Com base nessa comparação:

- Se a temperatura estiver dentro da faixa:
  
  - LED verde é ativado
  - LED vermelho é desligado
  - O estado de alerta é resetado

- Se a temperatura estiver fora da faixa:
  
  - LED vermelho é ativado
  - LED verde é desligado
  
  - Um alerta MQTT é enviado apenas uma vez até a condição normalizar

Além disso:

- O ESP32 conecta-se a uma rede Wi-Fi
- Estabelece comunicação com um broker MQTT hospedado em uma VPS
- Publica continuamente a temperatura a cada 5 segundos
- Envia alertas quando há condição crítica

## Problemas Identificados

### 1. Dependência de conexão com rede

O sistema depende de Wi-Fi para envio de dados.

Impacto:
Em caso de falha na rede, o monitoramento remoto deixa de funcionar.

---

### 2. Reconexão MQTT simples

A lógica de reconexão é básica e não trata múltiplas falhas consecutivas.

Problema:

- Pode haver demora na recuperação da conexão
- Não há estratégia avançada de reconexão

---

### 3. Uso de IA na integração

Parte da integração entre leitura do sensor e comunicação MQTT foi realizada com auxílio de IA.

Impacto:

- A lógica foi adaptada e validada manualmente
- Pode haver trechos não totalmente otimizados

---

## Possíveis Melhorias

### Reconexão mais robusta

- Implementar tentativas com intervalo progressivo
- Garantir maior estabilidade da conexão

---

### Tratamento de falhas de rede

- Armazenar dados localmente em caso de falha
- Enviar posteriormente quando a conexão retornar

---

### Otimização do código

- Revisar lógica gerada com apoio de IA
- Melhorar organização e modularização

---

## Evolução

Esta versão representa a integração completa do sistema, unindo:

- Leitura do sensor
- Controle de faixa de temperatura
- Indicação visual com LEDs
- Comunicação via MQTT

O sistema passa a operar como uma solução IoT funcional, permitindo monitoramento remoto em tempo real.

---

### Considerações Finais

Esta versão consolida todas as etapas anteriores, transformando um sistema local em uma solução conectada.

Apesar de funcional, ainda existem melhorias possíveis para tornar o sistema mais robusto, escalável e adequado para aplicações reais.

O uso de IA contribuiu para acelerar a integração, mas exigiu validação manual para garantir coerência com o projeto.

# Código do sistema:

```cpp
#include <WiFi.h>  
#include <PubSubClient.h>  
#include "DHTesp.h"  

const int DHT_PIN = 15;  
const int LED_VERDE = 18;  
const int LED_VERMELHO = 23;  

const char* ssid = "Wokwi-GUEST";  
const char* password = "";  

const char* mqtt_server = "134.199.142.253";  
const int mqtt_port = 1883;  
const char* client_id = "escola/grupoG";  

const char* topico_temp = "escola/grupoG/frigorifico/temperatura";  
const char* topico_alerta = "escola/grupoG/frigorifico/alerta";  

WiFiClient espClient;  
PubSubClient client(espClient);  
DHTesp dht;  

bool alertaAtivo = false;  
unsigned long lastMsg = 0;  

void setup_wifi() {  
  Serial.print("Conectando ao WiFi...");  
  WiFi.begin(ssid, password);  

  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);  
    Serial.print(".");  
  }  

  Serial.println("\nWiFi conectado!");  
}  

void reconnect() {  
  if (client.connected()) return;  

  Serial.print("Conectando ao MQTT...");  

  String clientId = client_id;  
  clientId += String(random(1000, 9999));  

  if (client.connect(clientId.c_str())) {  
    Serial.println(" conectado!");  
  } else {  
    Serial.print(" erro=");  
    Serial.println(client.state());  
  }  
}  

void setup() {  
  Serial.begin(115200);  

  dht.setup(DHT_PIN, DHTesp::DHT22);  

  pinMode(LED_VERDE, OUTPUT);  
  pinMode(LED_VERMELHO, OUTPUT);  

  setup_wifi();  

  client.setServer(mqtt_server, mqtt_port);  
}  

void loop() {  
  if (!client.connected()) reconnect();  
  client.loop();  

  unsigned long now = millis();  

  if (now - lastMsg > 5000) {  
    lastMsg = now;  

    TempAndHumidity data = dht.getTempAndHumidity();  

    if (isnan(data.temperature)) {  
      Serial.println("Erro ao ler sensor!");  
      return;  
    }  

    float temp = data.temperature;  

    Serial.println("Temperatura: " + String(temp) + " °C");  

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

    char bufTemp[8];  
    dtostrf(temp, 4, 1, bufTemp);  
    client.publish(topico_temp, bufTemp);  

    Serial.printf("MQTT → Temp: %s °C\n", bufTemp);  
  }  
      }
