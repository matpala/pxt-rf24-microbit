// Temporary generated-equivalent declarations; regenerate with PXT.
declare namespace rf24 {
    //% shim=rf24::native_begin
    function native_begin(): void;

    //% shim=rf24::send_number
    function send_number(value: number): void;

    //% shim=rf24::send_text
    function send_text(text: string): void;

    //% shim=rf24::poll_received_number
    function poll_received_number(): void;

    //% shim=rf24::received_number
    function received_number(): number;

    //% shim=rf24::received_motor_left
    function received_motor_left(): number;

    //% shim=rf24::received_motor_right
    function received_motor_right(): number;

    //% shim=rf24::native_probe
    function native_probe(): number;
}
