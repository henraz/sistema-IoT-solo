// config.h

#ifndef CONFIG_H
#define CONFIG_H

// Configuração da conexão WiFi
#define NOME_WIFI "nome rede wifi"
#define SENHA_WIFI "senha do wifi"

// Configuração do Adafruit IO
#define AIO_USERNAME "username"
#define AIO_KEY "chave de acesso"

// FEEDS
#define DHT11_TEMPERATURA "/feeds/pi-5.dht11-temperatura"
#define DHT11_UMIDADE "/feeds/pi-5.dht11-umidade"
#define CS12_UMIDADE "/feeds/pi-5.cs12-umidade-inicial"
#define CS12_UMIDADE_PERCENT "/feeds/pi-5.cs12-umidade"
#define DSB18B20_TEMPERATURA "/feeds/pi-5.ds18b20-temperatura"
#define BH1750_LUX "/feeds/pi-5.bh1750-luminosidade"
#define RELE "/feeds/pi-5.rele"
#define CONTROLE "/feeds/pi-5.controle"
#define TEMPO_REGA "/feeds/pi-5.config-tempo-rega"
#define PERCENT_UMID_SOLO "/feeds/pi-5.config-percent-umid-solo"
#define REGA_AUTOMATICA "/feeds/pi-5.config-rega-automatica"

#endif // CONFIG_H