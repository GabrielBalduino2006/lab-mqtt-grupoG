# Escopo do Projeto — [Grupo G]



## Integrantes

- [Gabriel Balduino dos Santos] — [Técnico em Eletrônica]

- [Luan Cesar Pereira] — [Técnico em Eletrônica]

- [Victor Augusto Barcarollo] — [Técnico em Eletrônica]


## Problema

Em câmaras frias o monitoramento da temperatura é essencial para a conservação dos insumos, caso não seja feito o devido cuidado
os insumos podem vir a estragar e perder sua qualidade gerando perdas lucrativas e até mesmo risco à saúde.



## O que será monitorado

Temperatura dos devidos lugares onde os insumos serão monitorados.



## Sensor / Dado

Faixa de temperatura simulada no Wokwi atraves do sensor DHT22, variando entre o minimo de 1 e o maximo de 5 , alertando se houver aumento ou redução da temperatura variante.



## Estrutura de Tópicos MQTT

| Tópico | Descrição | Publisher | Subscriber |


| escola/grupoG/Frigorifico/temperatura 

| Temperatura em °C | ESP32 | Dashboard| 

| escola/grupoG/Frigorifico/alerta 

| alerta de variação na temperatura | ESP32 | Dashboard |



## Resultado Esperado

O sistema monitora a temperatura e publica continuamente os dados. Quando a temperatura sai da faixa de 1°C a 5°C, um alerta é gerado automaticamente em um tópico específico.


## Hardware / Software planejado

- Publisher: Wokwi simulado utilizando ESP32

- Broker: Mosquitto na VPS DigitalOcean (IP:134.199.142.253)

- Subscriber: Dashboard
