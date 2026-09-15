//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    /**
     * Inicializa la radio RF24.
     * Configuración v0.1:
     * - canal 76 (2476 MHz)
     * - 2 Mbps
     * - dirección E7:E7:E7:E7:E7
     * - CRC16
     * - sin ACK
     */
    //% blockId=rf24_begin
    //% block="RF24 iniciar"
    //% shim=rf24::begin
    export function begin(): void {
        // En el simulador no hacemos nada.
    }

    /**
     * Envía un número entero de 32 bits.
     */
    //% blockId=rf24_send_number
    //% block="RF24 enviar número %value"
    //% value.min=-2147483648 value.max=2147483647
    //% shim=rf24::send_number
    export function sendNumber(value: number): void {
        // En el simulador no hacemos nada.
    }
}
