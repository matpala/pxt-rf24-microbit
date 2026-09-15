//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    const RF24_EVENT_SOURCE = 0x5246
    const RF24_EVENT_VALUE = 1
    let receiverStarted = false

    /**
     * Prueba que la extensión MakeCode fue cargada correctamente.
     * No usa C++ ni la radio.
     */
    //% blockId=rf24_test_extension
    //% block="RF24 probar extensión"
    export function testExtension(): void {
        basic.showIcon(IconNames.Yes)
    }

    /**
     * Inicializa la radio RF24.
     */
    //% blockId=rf24_begin
    //% block="RF24 iniciar"
    //% shim=rf24::native_begin
    export function begin(): void {
        return
    }

    /**
     * Envía un número entero de 32 bits.
     */
    //% blockId=rf24_send_number
    //% block="RF24 enviar número %value"
    //% shim=rf24::send_number
    export function sendNumber(value: number): void {
        return
    }

    /**
     * Sends the raw UTF-8 bytes of a string.
     */
    //% blockId=rf24_send_text
    //% block="RF24 enviar texto %text"
    //% shim=rf24::send_text
    export function sendText(text: string): void {
        return
    }

    /**
     * Runs a handler when a valid 4-byte RF24 number is received.
     */
    //% blockId=rf24_on_received_number
    //% block="al recibir RF24 numero %handler"
    export function onReceivedNumber(handler: (value: number) => void): void {
        control.onEvent(RF24_EVENT_SOURCE, RF24_EVENT_VALUE, () => handler(receivedNumber()))
        if (receiverStarted)
            return

        receiverStarted = true
        control.inBackground(() => {
            while (true) {
                pollReceivedNumber()
                basic.pause(1)
            }
        })
    }

    //% shim=rf24::poll_received_number
    function pollReceivedNumber(): void {
        return
    }

    //% shim=rf24::received_number
    function receivedNumber(): number {
        return 0
    }

    /**
     * Distinguishes the simulator body from the native C++ shim.
     */
    //% blockId=rf24_native_probe
    //% block="RF24 prueba nativa"
    //% shim=rf24::native_probe
    export function nativeProbe(): number {
        return 111
    }
}
