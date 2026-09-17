//% color=#0066CC weight=90 icon="\uf1eb" block="RF24"
namespace rf24 {
    const RF24_EVENT_SOURCE = 0x5246
    const RF24_EVENT_VALUE = 1
    const RF24_MOTOR_EVENT_SOURCE = 0x5247
    const RF24_MOTOR_EVENT_VALUE = 1
    const LEFT_MOTOR_PORT = robotbit.Motors.M1A
    const RIGHT_MOTOR_PORT = robotbit.Motors.M2A
    const LEFT_MOTOR_DIRECTION = 1
    const RIGHT_MOTOR_DIRECTION = 1
    const MOTOR_WATCHDOG_MS = 300
    let receiverStarted = false
    let motorControlRegistered = false
    let motorCommandActive = false
    let lastMotorCommandAt = 0

    /**
     * Tests that the MakeCode extension loaded correctly.
     * Does not use C++ or the radio.
     */
    //% blockId=rf24_test_extension
    //% block="RF24 test extension"
    export function testExtension(): void {
        basic.showIcon(IconNames.Yes)
    }

    /**
     * Initializes the RF24 radio.
     */
    //% blockId=rf24_begin
    //% block="RF24 begin"
    //% shim=rf24::native_begin
    export function begin(): void {
        return
    }

    /**
     * Sends a 32-bit integer.
     */
    //% blockId=rf24_send_number
    //% block="RF24 send number %value"
    //% shim=rf24::send_number
    export function sendNumber(value: number): void {
        return
    }

    /**
     * Sends the raw UTF-8 bytes of a string.
     */
    //% blockId=rf24_send_text
    //% block="RF24 send text %text"
    //% shim=rf24::send_text
    export function sendText(text: string): void {
        return
    }

    /**
     * Runs a handler when a valid 4-byte RF24 number is received.
     * @param value the received number
     */
    //% blockId=rf24_on_number_drag block="on RF24 number received $value" blockGap=16
    //% value.loc.es="valor" value.loc.es-ES="valor"
    //% useLoc="rf24.onReceivedNumber" draggableParameters=reporter
    //% group="Receive"
    //% weight=20
    export function onReceivedNumber(cb: (value: number) => void): void {
        control.onEvent(RF24_EVENT_SOURCE, RF24_EVENT_VALUE, () => cb(receivedNumber()))
        startReceiver()
    }

    /**
     * Runs a handler when a valid RF24 motor command is received.
     * @param left the left motor value
     * @param right the right motor value
     */
    //% blockId=rf24_on_motor_command_drag block="on RF24 motor command received $left $right" blockGap=16
    //% left.loc.es="izquierda" left.loc.es-ES="izquierda" right.loc.es="derecha" right.loc.es-ES="derecha"
    //% useLoc="rf24.onReceivedMotorCommand" draggableParameters=reporter
    //% group="Receive"
    //% weight=19
    export function onReceivedMotorCommand(cb: (left: number, right: number) => void): void {
        motorControlRegistered = true
        stopMotors()
        control.onEvent(RF24_MOTOR_EVENT_SOURCE, RF24_MOTOR_EVENT_VALUE,
            () => {
                const left = receivedMotorLeft()
                const right = receivedMotorRight()
                lastMotorCommandAt = control.millis()
                motorCommandActive = true
                cb(left, right)
                robotbit.MotorRunDual(LEFT_MOTOR_PORT, left * LEFT_MOTOR_DIRECTION,
                    RIGHT_MOTOR_PORT, right * RIGHT_MOTOR_DIRECTION)
            })
        startReceiver()
    }

    function startReceiver(): void {
        if (receiverStarted)
            return

        receiverStarted = true
        control.inBackground(() => {
            while (true) {
                pollReceivedNumber()
                if (motorControlRegistered && motorCommandActive &&
                    control.millis() - lastMotorCommandAt >= MOTOR_WATCHDOG_MS)
                    stopMotors()
                basic.pause(1)
            }
        })
    }

    function stopMotors(): void {
        motorCommandActive = false
        robotbit.MotorRunDual(LEFT_MOTOR_PORT, 0, RIGHT_MOTOR_PORT, 0)
    }

    //% shim=rf24::poll_received_number
    function pollReceivedNumber(): void {
        return
    }

    //% shim=rf24::received_number
    function receivedNumber(): number {
        return 0
    }

    //% shim=rf24::received_motor_left
    function receivedMotorLeft(): number {
        return 0
    }

    //% shim=rf24::received_motor_right
    function receivedMotorRight(): number {
        return 0
    }

    /**
     * Distinguishes the simulator body from the native C++ shim.
     */
    //% blockId=rf24_native_probe
    //% block="RF24 native test"
    //% shim=rf24::native_probe
    export function nativeProbe(): number {
        return 111
    }
}
