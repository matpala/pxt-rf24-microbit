# RF24 micro:bit V2 v0.1.1

Corrección de la primera versión:
- agrega `shims.d.ts` y `enums.d.ts`
- separa `rf24` (bloques) de `rf24native` (C++)
- mantiene la API visible simple: `RF24 iniciar` y `RF24 enviar número`

Configuración fija de esta prueba:
- canal 76
- 2 Mbps
- dirección E7:E7:E7:E7:E7
- CRC16
- ESB
