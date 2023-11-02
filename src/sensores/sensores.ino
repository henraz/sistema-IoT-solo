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
#define PortaRele = D6

// Tempo de envio dos dados
unsigned long executionDuration = 900000; 
int tempoControle[][2] = {
  {180000, 0},
  {360000, 1},
  {540000, 2},
  {720000, 3}
};

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
Adafruit_MQTT_Publish bh1750Lux = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME BH1750_LUX);
Adafruit_MQTT_Subscribe releSubscribe = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME RELE);
Adafruit_MQTT_Publish relePublish = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME RELE);

void setup() {
  
  Serial.begin(115200);

  // Iniciando Sensores

  //Relé
  pinMode(PortaRele, OUTPUT);
  digitalWrite(PortaRele, LOW);
  mqtt.subscribe(&releSubscribe);

  // DS18B20
  dht.setup(PortaDHT, DHTesp::DHT11);

  // DS18B20
  sensor.begin();

  // BH1750
  Wire.begin();
  lightMeter.begin();

  // Variáveis que receberão os resultados dos sensores
  int valorUmidadeSolo;
  float valorTemperaturaDHT;
  float valorUmidadeDHT;
  int valorBH1750temperatura;
  float valorLuxBH1750;

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

  // Iniciando contagem de tempo
  startTime = millis();

  // Umidade Solo
  valorUmidadeSolo = analogRead(PortaUmidadeSolo);

  // Ativar Bomba com base nos dados do sensor de umidade
  if (valorUmidadeSolo > 1000) {
    digitalWrite(PortaRele, HIGH);
    delay(1000);
    controle.publish("REGA");
    digitalWrite(PortaRele, LOW);
  }

  // DHT11
  valorTemperaturaDHT = dht.getTemperature();
  valorUmidadeDHT = dht.getHumidity();

  // DS18B20
  sensorDS18B20.requestTemperatures();
  valorBH1750temperatura = sensorBH1750.getTempCByIndex(0);

  // BH1750
  valorLuxBH1750 = sensorBH1750.readLightLevel();
  
  // Publicando dados dos sensores
  cs12Humidade.publish(valorUmidadeSolo);
  dht11Temperatura.publish(valorTemperaturaDHT);
  dht11Umidade.publish(valorUmidadeDHT);
  ds18b2Temperatura.publish(valorBH1750temperatura);
  bh1750lux.publish(valorLuxBH1750);

  int aux = 0;
  while ((millis() - startTime) <= executionDuration) {
      
      VerificaBotao();

      for (int i = 0; i <= 3; i++){
        if (((millis() - startTime) >= meuArray[i][0]) && (aux == meuArray[i][1])){
          controle.publish("CONTROLE");
          aux += 1;
        }
      }
  }
  delay(5000);
}


// Ativar Bomba com base na decisão do usuário.
void VerificaBotao(){
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &releSubscribe) {

       if (strcmp((char *)releSubscribe.lastread, "ON") == 0) { 
          digitalWrite(PortaRele, HIGH);
          controle.publish("REGA");
          delay(1000);
          digitalWrite(PortaRele, LOW);
          relePublish.publish("OFF");
      }
    }
  }
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