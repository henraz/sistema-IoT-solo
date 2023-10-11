#include <DHTesp.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <BH1750.h>
#include "config.h"

//Portas dos sensores
#define PortaUmidadeSolo = A0
#define PortaDHT = 14
#define PortaDS18B20 = D7

//Instanciando objetos para os sensores
DHTesp dht;
OneWire barramento(PortaDS18B20);
DallasTemperature sensorDS18B20(&barramento);
BH1750 sensorBH1750;

void setup() {
  
  Serial.begin(9600);
  
  // Iniciando Sensores
  // DS18B20
  dht.setup(PortaDHT, DHTesp::DHT11);

  //DS18B20
  sensor.begin();

  // BH1750
  Wire.begin();
  lightMeter.begin();
}

void loop() {

  // Umidade Solo
  int umidadeSolo = analogRead(PortaUmidadeSolo);
  Serial.print("Umidade do Solo: ");
  Serial.print(umidadeSolo);
  Serial.println(" %");
  
  // DHT11
  float temperaturaDHT = dht.getTemperature();
  float umidadeDHT = dht.getHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperaturaDHT);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(umidadeDHT);
  Serial.println(" %");

  //BH1750
  float luxBH1750 = sensorBH1750.readLightLevel();

  //DS18B20
  sensorDS18B20.requestTemperatures();
  Serial.println(sensorBH1750.getTempCByIndex(0));
  
  //GY-30
  Serial.print("Light: ");
  Serial.print(luxBH1750);
  Serial.println(" lx");

  delay(5000);
}
