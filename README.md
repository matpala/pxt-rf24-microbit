# RF24 micro:bit V2 v0.1.2

Esta versión corrige la arquitectura de los shims MakeCode:

- namespace visible: `rf24`
- funciones nativas declaradas en `shims.d.ts`
- wrapper TypeScript simple
- C++ directo en el mismo namespace nativo

Prueba:
- RF24 iniciar
- RF24 enviar número 42
