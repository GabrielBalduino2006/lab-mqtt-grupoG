# lab-mqtt-grupoG
## GrupoG
## Projeto: Monitoramento de temperatura em câmaras frias/frigorificos.
Integrantes: Gabriel Balduino dos Santos, Luan César Pereira e Victor Augusto Barcarollo. 

## Descrição do projeto:
Sistema de monitoramento de temperatura para câmaras frias utilizando ESP32, protocolo MQTT e broker em VPS. O sistema realiza leitura contínua da temperatura e gera alertas em tempo real quando os valores saem da faixa segura de operação.

## Problema:
Câmaras frias são ambientes críticos para a conservação de insumos, exigindo controle rigoroso de temperatura. A faixa ideal de operação está entre 1°C e 5°C. Quando essa faixa não é mantida, os insumos podem sofrer degradação, perda de qualidade ou até se tornarem impróprios para consumo, gerando prejuízos financeiros e riscos à saúde. A ausência de monitoramento contínuo e de alertas em tempo real pode fazer com que essas variações passem despercebidas.

## Arquitetura:
O sistema segue uma arquitetura baseada em Internet das Coisas (IoT), organizada em camadas:

Dispositivo: ESP32 + sensor DHT22 (leitura da temperatura)

Rede: Comunicação via Wi-Fi utilizando MQTT sobre TCP/IP

Plataforma: Broker MQTT (Mosquitto) hospedado em VPS

Aplicação: Subscriber (dashboard) para exibição dos dados.


Além disso, o sistema possui resposta local com LEDs:

🟢 Verde: temperatura dentro da faixa (1°C a 5°C)

🔴 Vermelho: temperatura fora da faixa (condição crítica)

## Especificação Técnica
Sensor: DHT22

Grandeza: Temperatura

Faixa operacional: 1°C a 5°C

Condição crítica: Menos que 1°C, mais que 5°C

Unidade: °C

Frequência de leitura: A cada 5 segundos

Formato de payload: JSON

QoS: 1

## Instruções de Uso

1. Acesse o projeto no Wokwi e inicie a simulação do ESP32
2. Certifique-se de que o broker MQTT na VPS está ativo
3. Execute o subscriber para se conectar ao broker
4. Observe o recebimento dos dados de temperatura em tempo real
5. Simule variações de temperatura fora da faixa para testar o envio de alertas
6. Verifique a mudança dos LEDs conforme a condição da temperatura
