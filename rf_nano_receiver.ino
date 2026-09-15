#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8);

const uint8_t address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!radio.begin()) {
    Serial.println("ERROR: nRF24L01+ no detectado");
    while (true) {}
  }

  radio.setChannel(76);
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setCRCLength(RF24_CRC_16);
  radio.enableDynamicPayloads();
  radio.setAutoAck(true);

  radio.openReadingPipe(1, address);
  radio.startListening();

  Serial.println("Esperando paquetes...");
}

void loop() {
  if (!radio.available()) return;

  uint8_t len = radio.getDynamicPayloadSize();
  if (len == 0 || len > 32) {
    radio.flush_rx();
    return;
  }

  uint8_t buffer[32] = {0};
  radio.read(buffer, len);

  Serial.print("RX len=");
  Serial.print(len);
  Serial.print(" HEX: ");

  for (uint8_t i = 0; i < len; i++) {
    if (buffer[i] < 0x10) Serial.print('0');
    Serial.print(buffer[i], HEX);
    Serial.print(' ');
  }

  if (len == 4) {
    int32_t value =
      ((int32_t)buffer[0]) |
      ((int32_t)buffer[1] << 8) |
      ((int32_t)buffer[2] << 16) |
      ((int32_t)buffer[3] << 24);

    Serial.print(" -> numero=");
    Serial.print(value);
  }

  Serial.println();
}
