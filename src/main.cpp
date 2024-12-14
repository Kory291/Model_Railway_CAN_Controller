#include <Arduino.h>
#include <SPI.h>

// define pins here
#define LED_PIN 2
#define VSPI_CLK 18
#define VSPI_MISO 19
#define VSPI_MOSI 23
#define VSPI_SS 5
#define HSPI_CLK 14
#define HSPI_MISO 12
#define HSPI_MOSI 13
#define HSPI_SS 15
#define spiClk 1000000

SPIClass *vspi;
SPIClass *hspi;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);
  vspi->begin(VSPI_CLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  hspi->begin(HSPI_CLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);
  
  pinMode(vspi->pinSS(), OUTPUT);
  pinMode(hspi->pinSS(), OUTPUT);
  
  pinMode(LED_PIN, OUTPUT);

}

void spiCommand(SPIClass *spi, byte data) {
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW);
  Serial.printf("data to send: %i\n", data);
  byte result = spi->transfer(data);
  digitalWrite(spi->pinSS(), HIGH);
  Serial.println(result);
  spi->endTransaction();
}

void spiRead(SPIClass *spi) {
  spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW);
  byte data = spi->transfer(NULL);
  digitalWrite(spi->pinSS(), HIGH);
  spi->endTransaction();
  Serial.println(data);
}

void loop() {
  spiCommand(vspi, 0xA1);
  delay(1000);
  spiRead(hspi);
}
