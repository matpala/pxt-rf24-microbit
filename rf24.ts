//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    /**
     * Inicializa la radio RF24.
     */
    //% blockId=rf24_begin
    //% block="RF24 iniciar"
    export function begin(): void {
        rf24native.begin()
    }

    /**
     * Envía un número entero de 32 bits.
     */
    //% blockId=rf24_send_number
    //% block="RF24 enviar número %value"
    export function sendNumber(value: number): void {
        rf24native.sendNumber(value)
    }
}

// API nativa interna, sin bloques visibles.
namespace rf24native {
    //% shim=rf24native::begin
    export function begin(): void {
        // Simulador: no hace nada.
    }

    //% shim=rf24native::send_number
    export function sendNumber(value: number): void {
        // Simulador: no hace nada.
    }
}
