# Introdução

Sistema IoT para controle da temperatura e umidade relativa do ar, nível de luminosidade, temperatura e nível de umidade do solo construído como parte do Projeto Integrador da UNIVESP.

# Ferramentas

## Sistema IoT

### Materiais utilizados

1. [nodeMCU devkit](https://github.com/nodemcu/nodemcu-devkit-v1.0)
2. Sensor DHT11
3. Sensor DS18B20
4. BH1750
5. Sensor de umidade do solo capacitivo
6. Mini bomba d'água

### Bibliotecas

O desenvolvimento foi realizado utilizando a [Arduino IDE](https://www.arduino.cc/en/software), sendo necessário a instalação das seguintes bibliotecas:

1. [Adafruit MQTT Library (2.5.8)](https://github.com/adafruit/Adafruit_MQTT_Library)
2. [Adafruit IO Arduino (4.2.9)](https://github.com/adafruit/Adafruit_IO_Arduino)
3. [Adafruit Unified Sensor (1.1.12)](https://github.com/adafruit/Adafruit_Sensor)
4. [DHT sensor library (1.4.4)](https://github.com/adafruit/DHT-sensor-library)
5. [OneWire (2.3.7)](https://github.com/PaulStoffregen/OneWire)
6. [DallasTemperature (3.9.0)](https://github.com/milesburton/Arduino-Temperature-Control-Library)
7. [BH1750 (1.3.0)](https://github.com/claws/BH1750)

## Análise de dados

### Bibliotecas

1. [adafruit-io (2.7.0)](https://pypi.org/project/adafruit-io/)
2. [pandas (2.1.2)](https://pandas.pydata.org/docs/index.html)
3. [matplotlib (3.8.1)](https://matplotlib.org/)


# Estrutura do Projeto

## Sistema IoT

![Image](/img/arquitetura.png)

## Circuito

![Image](/img/circuito.png)