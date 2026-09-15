//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    /**
     * Inicializa la radio RF24.
     */
    //% blockId=rf24_begin
    //% block="RF24 iniciar"
    export function begin(): void {
        native_begin()
    }

    /**
     * Envía un número entero.
     */
    //% blockId=rf24_send_number
    //% block="RF24 enviar número %value"
    export function sendNumber(value: number): void {
        native_send_number(value)
    }
}
