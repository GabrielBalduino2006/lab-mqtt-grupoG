# Firmware ESP32 — Versão 1

## Data de desenvolvimento

21 de Março de 2026

## Objetivo

Implementar a leitura da temperatura utilizando o sensor DHT22 no ESP32 e fornecer uma indicação visual simples do estado da temperatura por meio de LEDs.

## Funcionamento

O sistema utiliza um sensor DHT22 conectado ao pino 15 do ESP32 para realizar a leitura da temperatura.

A cada ciclo de execução:

- O sensor coleta a temperatura do ambiente
- O valor é validado para evitar leituras inválidas
- A temperatura é exibida no monitor serial
- O valor é comparado com o limite de 5°C

Com base nessa comparação:

- Se a temperatura for maior que 5°C:
  
  - LED vermelho é ativado
  - LED verde é desligado

- Caso contrário:
  
  - LED verde é ativado
  - LED vermelho é desligado

O ciclo se repete continuamente com intervalo de 2 segundos entre leituras.

## Problemas Identificados

### 1. Tratamento incompleto da faixa de temperatura

O sistema considera apenas temperaturas acima de 5°C como condição crítica.

Problema:
Temperaturas abaixo de 1°C também são críticas no contexto do projeto, mas não são tratadas.

### 2. Possibilidade de leitura inválida (NaN)

O sensor DHT22 pode retornar valores inválidos.

Impacto:
Quando isso ocorre, o sistema apenas exibe uma mensagem de erro e interrompe o ciclo atual, sem tentativa de recuperação.

### 3. Frequência de leitura 

O uso de "delay(2000)" fixa o intervalo de leitura em 2 segundos.

Problema:

- Pode ser mais rápido do que o necessário

4. Ausência de comunicação externa

O sistema funciona apenas localmente.

Limitação:
Não há envio de dados para rede ou integração com outros sistemas, o que impede monitoramento remoto.

## Possíveis Melhorias

### Ajuste da lógica de faixa

Implementar verificação completa:

- Temperatura < 1°C → crítico
- Temperatura > 5°C → crítico

### Tratamento de erro mais robusto

- Repetir leitura em caso de erro
- Evitar perda de ciclo
- Implementar tentativa de recuperação

### Frequência de envios de dados mais lenta

Aumentar o intervalo de tempo em que os dados são enviados.

### Integração com MQTT

Adicionar:

- Conexão Wi-Fi
- Publicação de dados
- Envio de alertas

## Evolução

Esta versão representa a base funcional do sistema, validando:

- Leitura do sensor
- Processamento de dados
- Resposta local via LEDs

A partir desta etapa, o sistema deve evoluir para:

- Comunicação MQTT
- Monitoramento remoto
- Estrutura completa de IoT

### Considerações Finais

Esta versão foi fundamental para validar o funcionamento do hardware e da lógica básica do sistema.

Apesar das limitações, ela estabelece a base necessária para as próximas etapas do desenvolvimento.


# Código do sistema:

```cpp
#include "DHTesp.h"

const int DHT_PIN = 15;
const int LED_VERDE = 18;
const int LED_VERMELHO = 23;

DHTesp dht;

void setup() {
  Serial.begin(115200);
  dht.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();

  if (isnan(data.temperature)) {
    Serial.println("Erro ao ler o sensor!");
    return;
  }

  float temp = data.temperature;

  Serial.println("Temperatura: " + String(temp) + " °C");


  if (temp > 5) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  delay(2000);
}
