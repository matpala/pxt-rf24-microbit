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
- al recibir comando RF24 motor

The motor command receive block accepts the 6-byte payload
`[0x03, leftSpeedLo, leftSpeedHi, rightSpeedLo, rightSpeedHi, sequence]`.
`leftSpeed` and `rightSpeed` are signed int16 little-endian values constrained
to `-255..255`; packets with another shape, marker, or range are rejected.
The sequence byte is reserved for command sequencing. The extension drives
Robotbit ports `M1A` and `M2A` with the two validated speeds and stops both
motors when no valid motor command arrives for 300 ms. Motor direction can be
calibrated with the direction constants in `rf24.ts`.

`RF24 enviar número` keeps the legacy 4-byte little-endian integer payload
(for example, `42` is sent as `2A 00 00 00`).

`RF24 enviar texto` transmits `[0x02, utf8_length, utf8_bytes]`, followed by
zero padding when needed. Text is limited to 30 UTF-8 bytes so the marker and
length fit in the 32-byte RF payload. Packets are padded to at least 5 bytes,
which keeps them distinct from the 4-byte numeric format.

The numeric receive block accepts valid 4-byte numeric packets, while the motor receive
block accepts the documented valid 6-byte commands. The receiver does not send
nRF24 auto-ACKs. Packets can be lost
while the radio switches between RX and TX; TX is preserved and RX is re-armed
after each transmission when receiving is active.
