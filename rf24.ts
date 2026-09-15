//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    /**
     * Inicializa la radio RF24.
     */
    //% blockId=rf24_begin
    //% block="RF24 iniciar"
    //% shim=rf24::begin
    export function begin(): void {
        // Solo se ejecuta en el simulador.
    }

    /**
     * Envía un número entero de 32 bits.
     */
    //% blockId=rf24_send_number
    //% block="RF24 enviar número %value"
    //% shim=rf24::send_number
    export function sendNumber(value: number): void {
        // Solo se ejecuta en el simulador.
    }
}
