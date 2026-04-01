# Evidências do Sistema

Esta seção apresenta as evidências do funcionamento do sistema, incluindo a comunicação MQTT e a resposta do dispositivo.

---

## 1. ESP32 em funcionamento

Imagem demonstrando o ESP32 em operação no ambiente de simulação (Wokwi), com o sensor DHT22 e os LEDs conectados.

- Responsável pela leitura da temperatura
- Realiza o envio dos dados via MQTT
- Executa a lógica de controle dos LEDs

---

## 2. Subscriber — Recebimento de Temperatura

Imagens que mostram o subscriber recebendo dados de temperatura em tempo real através do tópico:

escola/grupoG/frigorifico/temperatura

- Os valores são enviados a cada 5 segundos
- O formato do dado é texto simples (string)
- Exemplo: 3.2

---

## 3. Subscriber — Recebimento de Alerta

Imagens que mostram o subscriber recebendo mensagens de alerta através do tópico:

escola/grupoG/frigorifico/alerta

- O alerta é enviado quando a temperatura sai da faixa (1°C a 5°C)
- O envio ocorre apenas uma vez por evento crítico
- Exemplo:
  ALERTA! Temp fora da faixa: 6.5 C

---

## 4. Comportamento do Sistema

As evidências demonstram que:

- O sistema realiza leitura contínua da temperatura
- Os dados são enviados corretamente via MQTT
- O subscriber recebe as informações em tempo real
- O alerta é disparado corretamente em condições críticas
- O sistema evita envio repetido de alertas desnecessários

---

## Considerações

As evidências confirmam o funcionamento completo do sistema, incluindo:

- Coleta de dados
- Processamento local
- Comunicação via rede
- Monitoramento remoto
