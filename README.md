# RF24 micro:bit V2 v0.2.0

Experimental MakeCode extension.

## Diagnostic test

1. Open [MakeCode for micro:bit](https://makecode.microbit.org).
2. Create a project, open **Extensions**, and import
   `https://github.com/matpala/pxt-rf24-microbit` (do not import the ZIP).
3. In `on start`, use **RF24 probar extensión**, then use **RF24 prueba
   nativa** with `basic.showNumber`.

The simulator shows the TypeScript test icon and `111`. Compile for a
micro:bit V2 and download it to see `222` instead. This verifies the
Blocks → TypeScript → C++ path; it does not test RF transmission.

RF blocks:
- RF24 iniciar
- RF24 enviar número
- RF24 enviar texto
- al recibir RF24 numero

`RF24 enviar número` keeps the legacy 4-byte little-endian integer payload
(for example, `42` is sent as `2A 00 00 00`).

`RF24 enviar texto` transmits `[0x02, utf8_length, utf8_bytes]`, followed by
zero padding when needed. Text is limited to 30 UTF-8 bytes so the marker and
length fit in the 32-byte RF payload. Packets are padded to at least 5 bytes,
which keeps them distinct from the 4-byte numeric format.

The receive block accepts only valid 4-byte numeric packets. This first receive
slice is receive-only and does not send nRF24 auto-ACKs. Packets can be lost
while the radio switches between RX and TX; TX is preserved and RX is re-armed
after each transmission when receiving is active.
