#include "pxt.h"

#if MICROBIT_CODAL
#include "nrf.h"
#endif

using namespace pxt;

namespace rf24 {

#if MICROBIT_CODAL

    // Payload en RAM para EasyDMA.
    // Con S0LEN=0, LFLEN=6 y S1LEN=3, RADIO usa:
    // byte 0: LENGTH
    // byte 1: S1 (solo 3 bits significativos)
    // bytes siguientes: payload
    struct __attribute__((packed)) RadioPacket {
        uint8_t length;
        uint8_t s1;
        uint8_t payload[32];
    };

    static RadioPacket txPacket;
    static bool initialized = false;
    static uint8_t packetId = 0;

    static void wait_disabled() {
        while (NRF_RADIO->EVENTS_DISABLED == 0) {
        }
        NRF_RADIO->EVENTS_DISABLED = 0;
    }

    static void configure_radio() {
        // Detener cualquier uso previo del periférico RADIO.
        NRF_RADIO->EVENTS_DISABLED = 0;
        NRF_RADIO->TASKS_DISABLE = 1;

        // Si la radio ya estaba deshabilitada, DISABLED puede no dispararse.
        // Esperamos solo cuando el estado no sea DISABLED.
        if ((NRF_RADIO->STATE & RADIO_STATE_STATE_Msk) !=
            (RADIO_STATE_STATE_Disabled << RADIO_STATE_STATE_Pos)) {
            wait_disabled();
        }

        // Canal 76 => 2476 MHz.
        NRF_RADIO->FREQUENCY = 76;

        // Nordic proprietary 2 Mbps, compatible con nRF24L01+ a 2 Mbps.
        NRF_RADIO->MODE = RADIO_MODE_MODE_Nrf_2Mbit;

        // Packet Control Field de Enhanced ShockBurst:
        // LENGTH = 6 bits, S0 = 0 bits, S1 = 3 bits (PID + NO_ACK).
        NRF_RADIO->PCNF0 =
            (0UL << RADIO_PCNF0_S0LEN_Pos) |
            (6UL << RADIO_PCNF0_LFLEN_Pos) |
            (3UL << RADIO_PCNF0_S1LEN_Pos) |
            (1UL << RADIO_PCNF0_S1INCL_Pos);

        // 5 bytes de dirección: BASE de 4 bytes + PREFIX de 1 byte.
        // Sin whitening, como nRF24L01+.
        NRF_RADIO->PCNF1 =
            (32UL << RADIO_PCNF1_MAXLEN_Pos) |
            (0UL << RADIO_PCNF1_STATLEN_Pos) |
            (4UL << RADIO_PCNF1_BALEN_Pos) |
            (RADIO_PCNF1_ENDIAN_Little << RADIO_PCNF1_ENDIAN_Pos) |
            (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos);

        // Dirección simétrica para evitar ambigüedad de orden de bytes.
        // E7:E7:E7:E7:E7
        NRF_RADIO->BASE0 = 0xE7E7E7E7;
        NRF_RADIO->PREFIX0 = 0x000000E7;
        NRF_RADIO->TXADDRESS = 0;

        // CRC16 compatible con nRF24L01+.
        NRF_RADIO->CRCCNF = RADIO_CRCCNF_LEN_Two;
        NRF_RADIO->CRCPOLY = 0x11021;
        NRF_RADIO->CRCINIT = 0xFFFF;

        // Potencia de transmisión: 0 dBm.
        NRF_RADIO->TXPOWER = RADIO_TXPOWER_TXPOWER_0dBm;

        // READY -> START y END -> DISABLE.
        NRF_RADIO->SHORTS =
            RADIO_SHORTS_READY_START_Msk |
            RADIO_SHORTS_END_DISABLE_Msk;

        txPacket.length = 0;
        txPacket.s1 = 0;

        NRF_RADIO->PACKETPTR =
            reinterpret_cast<uint32_t>(&txPacket);

        initialized = true;
    }

#endif

    //%
    void begin() {
#if MICROBIT_CODAL
        configure_radio();
#else
        target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
    }

    //%
    void send_number(int value) {
#if MICROBIT_CODAL
        if (!initialized) {
            configure_radio();
        }

        // 4 bytes, little-endian, para coincidir con int32_t del RF-Nano.
        txPacket.length = 4;

        // Los 3 bits S1 completan el Packet Control Field de ESB:
        // PID (2 bits) + NO_ACK (1 bit).
        //
        // Mantenemos NO_ACK=0 para que el receptor nRF24 permanezca en
        // Enhanced ShockBurst. El micro:bit v0.1 no escucha el ACK: simplemente
        // termina la transmisión después de END.
        //
        // Rotamos PID para que envíos repetidos del mismo valor no sean
        // descartados por el receptor como duplicados.
        txPacket.s1 = (packetId & 0x03);
        packetId = (packetId + 1) & 0x03;

        txPacket.payload[0] = (uint8_t)(value & 0xFF);
        txPacket.payload[1] = (uint8_t)((value >> 8) & 0xFF);
        txPacket.payload[2] = (uint8_t)((value >> 16) & 0xFF);
        txPacket.payload[3] = (uint8_t)((value >> 24) & 0xFF);

        NRF_RADIO->PACKETPTR =
            reinterpret_cast<uint32_t>(&txPacket);

        NRF_RADIO->EVENTS_DISABLED = 0;
        NRF_RADIO->TASKS_TXEN = 1;

        wait_disabled();
#else
        (void)value;
        target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
    }
}
