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
