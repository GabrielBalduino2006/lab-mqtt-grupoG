# Especificação Técnica

## Visão Geral

Este documento define os parâmetros técnicos utilizados no sistema de monitoramento de temperatura, garantindo consistência na coleta, transmissão e interpretação dos dados.

## Variável Monitorada

- Grandeza: Temperatura
- Unidade: Graus Celsius (°C)
- Sensor: DHT22

## Faixa de Operação

- Faixa ideal: 1°C a 5°C
- Condição crítica:
  - Abaixo de 1°C
  - Acima de 5°C

Valores fora da faixa são considerados anormais e acionam o mecanismo de alerta.

## Frequência de Coleta

- Intervalo de leitura: 5 segundos

Esse intervalo foi definido para garantir monitoramento contínuo sem gerar tráfego excessivo na rede.

## Formato dos Dados (Payload)

Os dados são enviados no formato JSON, permitindo estruturação e fácil interpretação.

Exemplo — Temperatura normal:

{
  "temperatura": 3.2
}

Exemplo — Alerta:

{
  "temperatura": 6.5,
  "alerta": "fora_da_faixa"
}

## Comunicação MQTT

- Protocolo: MQTT sobre TCP/IP
- QoS: Nível 1

O QoS 1 garante que as mensagens sejam entregues ao menos uma vez, evitando perda de dados críticos.

## Tópicos Utilizados

- "escola/grupoG/frigorifico/temperatura"
  → envio contínuo dos dados de temperatura

- "escola/grupoG/frigorifico/alerta"
  → envio de mensagens de alerta quando há condição crítica

## Lógica de Funcionamento

- Temperatura dentro da faixa:
  
  - Publicação no tópico de temperatura
  - LED verde ativo

- Temperatura fora da faixa:
  
  - Publicação no tópico de temperatura
  - Publicação no tópico de alerta
  - LED vermelho ativo
