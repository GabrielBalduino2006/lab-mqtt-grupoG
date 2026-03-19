# Escopo do Projeto — [Grupo G]



## Integrantes

- [Gabriel Balduino dos Santos] — [Técnico em Eletrônica]

- [Luan Cesar Pereira] — [Técnico em Eletrônica]

- [Victor Augusto Barcarollo] — [Técnico em Eletrônica]


## Problema

[2-3 linhas descrevendo o contexto e o risco real do problema]



## O que será monitorado

[Ex.: Temperatura e vibração de um motor de bancada simulado]



## Sensor / Dado

[Ex.: DHT22 real no ESP32 / variação simulada no Wokwi entre 20°C e 90°C]



## Estrutura de Tópicos MQTT

| Tópico | Descrição | Publisher | Subscriber |

|--------|-----------|-----------|------------|

| escola/grupo01/motor/temperatura | Temperatura em °C | ESP32 | Dashboard |

| escola/grupo01/motor/status | ONLINE / OFFLINE (LWT) | ESP32 | Dashboard |

| escola/grupo01/motor/alerta | Alertas críticos | ESP32 | Dashboard |



## Resultado Esperado

[O que será visível ao final — terminal, painel, alertas]



## Hardware / Software planejado

- Publisher: [ESP32 físico / Wokwi simulado]

- Broker: Mosquitto na VPS DigitalOcean (IP: SEU_IP)

- Subscriber: [Terminal / Node-RED / outro]



## Evolução planejada

[Se houver ambição de ir além do mínimo — dashboard visual, histórico, etc.]
