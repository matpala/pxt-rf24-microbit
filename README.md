# RF24 micro:bit V2 — v0.1

Extensión MakeCode experimental para transmitir paquetes compatibles con nRF24L01+ desde la radio interna del micro:bit V2.

## Alcance de v0.1

- Solo micro:bit V2.
- TX únicamente.
- Canal 76 = 2476 MHz.
- 2 Mbps.
- Dirección: `E7:E7:E7:E7:E7`.
- CRC16.
- Payload dinámico.
- ESB con Auto-ACK activo en el RF-Nano; el micro:bit v0.1 ignora la respuesta ACK.
- Bloques:
  - `RF24 iniciar`
  - `RF24 enviar número`

## Prueba MakeCode

Usar:

- `al iniciar` -> `RF24 iniciar`
- `al presionar botón A` -> `RF24 enviar número 42`

## RF-Nano receptor

Configurar RF24 así:

```cpp
radio.setChannel(76);
radio.setDataRate(RF24_2MBPS);
radio.setCRCLength(RF24_CRC_16);
radio.enableDynamicPayloads();
radio.setAutoAck(true);
```

Dirección:

```cpp
const uint8_t address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
radio.openReadingPipe(1, address);
```

Esta versión es deliberadamente mínima para validar interoperabilidad antes de agregar RX, ACK, texto y configuración por bloques.
# pxt-rf24-microbit
