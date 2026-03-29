# Tópicos MQTT

## Visão Geral

Os tópicos MQTT são responsáveis por organizar a comunicação entre o ESP32 (publisher) e o subscriber, permitindo a separação entre dados de monitoramento contínuo e eventos críticos.

## Estrutura dos Tópicos

O padrão utilizado segue uma hierarquia organizada:

escola/grupoG/frigorifico/"tipo"

Onde:

- "escola" → escola representa o contexto institucional do projeto
- "grupoG" → identificação do grupo
- "frigorifico" → aplicação do sistema
- "tipo" → tipo de informação transmitida

## Tópico de Temperatura

escola/grupoG/frigorifico/temperatura

- Publisher: ESP32
- Subscriber: Dashboard / terminal

Descrição:

Utilizado para envio contínuo dos dados de temperatura coletados pelo sensor DHT22.

Payload:

{
  "temperatura": 3.2
}

## Tópico de Alerta

escola/grupoG/frigorifico/alerta

- Publisher: ESP32
- Subscriber: Dashboard / terminal

Descrição:

Utilizado para envio de mensagens quando a temperatura sai da faixa segura (1°C a 5°C).

Payload:

{
  "temperatura": 6.5,
  "alerta": "fora_da_faixa"
}
