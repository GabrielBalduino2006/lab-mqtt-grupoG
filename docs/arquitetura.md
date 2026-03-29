# Arquitetura da Solução
## Visão Geral

O sistema foi projetado para realizar o monitoramento contínuo da temperatura em câmaras frias, utilizando uma arquitetura baseada em Internet das Coisas (IoT).

A solução permite coleta de dados em tempo real, envio para um broker MQTT e visualização remota, além de resposta local imediata através de LEDs.

## Camadas da Arquitetura

### Camada de Dispositivo

Responsável pela coleta de dados.

• ESP32 (microcontrolador)

• Sensor DHT22 (temperatura)

O ESP32 realiza leituras periódicas da temperatura e atua como publisher, enviando os dados para o broker MQTT.

### Camada de Rede

Responsável pela comunicação entre os componentes.

• Conexão Wi-Fi

• Protocolo TCP/IP

• Protocolo MQTT (QoS 1)

O ESP32 transmite os dados via Wi-Fi utilizando MQTT sobre TCP/IP. As mensagens são enviadas com QoS nível 1, garantindo que sejam entregues ao broker ao menos uma vez, equilibrando confiabilidade e desempenho.

### Camada de Plataforma

Responsável pelo gerenciamento das mensagens.

• Broker MQTT (Mosquitto)

• Hospedado em VPS

O broker recebe as mensagens publicadas pelo ESP32 e as distribui para todos os clientes inscritos nos tópicos.

### Camada de Aplicação

Responsável pelo consumo e visualização dos dados.

• Subscriber (terminal ou dashboard)

O subscriber se conecta ao broker e se inscreve nos tópicos definidos, recebendo os dados de temperatura em tempo real.

## Fluxo de Dados

O sensor DHT22 realiza a leitura da temperatura.

O ESP32 processa os dados.

Os dados são estruturados em formato JSON.

O ESP32 publica as mensagens no tópico escola/grupoG/frigorifico/temperatura, utilizando MQTT com QoS 1.

O broker MQTT recebe e distribui as mensagens.

O subscriber recebe os dados em tempo real e exibe as informações.

## Mecanismo de Alerta

O sistema possui um mecanismo de detecção de condição crítica baseado na faixa de temperatura.

Faixa segura: 1°C a 5°C

Condição crítica: <1°C ou >5°C

Quando a temperatura sai da faixa:

O ESP32 publica uma mensagem no tópico escola/grupoG/frigorifico/alerta.

O subscriber recebe e identifica a condição crítica.

## Resposta Local

Além do monitoramento remoto, o sistema possui resposta local independente da rede:

LED verde: temperatura dentro da faixa

LED vermelho: temperatura fora da faixa

Essa abordagem garante indicação imediata do estado do sistema, mesmo em caso de falha de comunicação.

## Tópicos MQTT Utilizados

escola/grupoG/frigorifico/temperatura → envio contínuo de dados sobre temperatura

escola/grupoG/frigorifico/alerta → envio de eventos críticos, como temperatura fora da faixa ideal
