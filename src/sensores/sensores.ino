#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ESP8266WiFi.h>
#include <DHTesp.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <BH1750.h>
#include "config.h"

// Portas dos sensores
#define PortaUmidadeSolo = A0
#define PortaDHT = 14
#define PortaDS18B20 = D7

// Instanciando objetos para os sensores
DHTesp dht;
OneWire barramento(PortaDS18B20);
DallasTemperature sensorDS18B20(&barramento);
BH1750 sensorBH1750;

// Objeto para conexão com a Adafruit IO via MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, AIO_USERNAME, AIO_KEY);

// Objetos para conexão com os feeds dos sensores
Adafruit_MQTT_Publish cs12Umidade = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME CS12_UMIDADE);
Adafruit_MQTT_Publish dht11Temperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME DHT11_TEMPERATURA);
Adafruit_MQTT_Publish dht11Umidade = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME DHT11_UMIDADE);
Adafruit_MQTT_Publish ds18b2Temperatura = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME DSB18B20_TEMPERATURA);
Adafruit_MQTT_Publish bh1750lux = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME BH1750_LUX);

void setup() {
  
  Serial.begin(9600);
  
  // Iniciando Sensores
  // DS18B20
  dht.setup(PortaDHT, DHTesp::DHT11);

  // DS18B20
  sensor.begin();

  // BH1750
  Wire.begin();
  lightMeter.begin();

  //Conexão com a rede WiFi
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(NOME_WIFI, SENHA_WIFI);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao WiFi!");
}

void loop() {

  // Iniciando a conexão com a plataforma AdafruitIO
  MQTTconnect();

  // Umidade Solo
  int valorUmidadeSolo = analogRead(PortaUmidadeSolo);
  Serial.print("Umidade do Solo: ");
  Serial.print(valorUmidadeSolo);
  Serial.println(" %");
  
  // DHT11
  float valorTemperaturaDHT = dht.getTemperature();
  float valorUmidadeDHT = dht.getHumidity();
  Serial.print("Temperature: ");
  Serial.print(valorTemperaturaDHT);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(valorUmidadeDHT);
  Serial.println(" %");

  // DS18B20
  sensorDS18B20.requestTemperatures();
  int valorBH1750temperatura = sensorBH1750.getTempCByIndex(0);
  Serial.println(valorBH1750temperatura);

  // BH1750
  float valorLuxBH1750 = sensorBH1750.readLightLevel();
  Serial.print("Light: ");
  Serial.print(valorLuxBH1750);
  Serial.println(" lx");
  
  // Publicando dados dos sensores
  cs12Humidade.publish(valorUmidadeSolo);
  dht11Temperatura.publish(valorTemperaturaDHT);
  dht11Umidade.publish(valorUmidadeDHT);
  ds18b2Temperatura.publish(valorBH1750temperatura);
  bh1750lux.publish(valorLuxBH1750);

  delay(5000);
}


void MQTTconnect() {
  int8_t ret;

  // Verifica se já está conectado
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando ao Adafruit IO...");

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Tentando novamente em 5 segundos...");
    mqtt.disconnect();
    delay(5000);
  }

  Serial.println("Conectado!");
}