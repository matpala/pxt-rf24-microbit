#include "pxt.h"

#if MICROBIT_CODAL
#include "nrf.h"
#endif

using namespace pxt;

namespace rf24 {

#if MICROBIT_CODAL

struct __attribute__((packed)) RadioPacket {
    uint8_t length;
    uint8_t s1;
    uint8_t payload[32];
};

static RadioPacket txPacket;
static bool initialized = false;
static uint8_t packetId = 0;

static void waitDisabled() {
    while (NRF_RADIO->EVENTS_DISABLED == 0) {}
    NRF_RADIO->EVENTS_DISABLED = 0;
}

static void configureRadio() {
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_DISABLE = 1;

    if ((NRF_RADIO->STATE & RADIO_STATE_STATE_Msk) !=
        (RADIO_STATE_STATE_Disabled << RADIO_STATE_STATE_Pos)) {
        waitDisabled();
    }

    NRF_RADIO->FREQUENCY = 76;
    NRF_RADIO->MODE = RADIO_MODE_MODE_Nrf_2Mbit;

    NRF_RADIO->PCNF0 =
        (0UL << RADIO_PCNF0_S0LEN_Pos) |
        (6UL << RADIO_PCNF0_LFLEN_Pos) |
        (3UL << RADIO_PCNF0_S1LEN_Pos) |
        (1UL << RADIO_PCNF0_S1INCL_Pos);

    NRF_RADIO->PCNF1 =
        (32UL << RADIO_PCNF1_MAXLEN_Pos) |
        (0UL << RADIO_PCNF1_STATLEN_Pos) |
        (4UL << RADIO_PCNF1_BALEN_Pos) |
        (RADIO_PCNF1_ENDIAN_Big << RADIO_PCNF1_ENDIAN_Pos) |
        (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos);

    NRF_RADIO->BASE0 = 0xE7E7E7E7;
    NRF_RADIO->PREFIX0 = 0x000000E7;
    NRF_RADIO->TXADDRESS = 0;

    NRF_RADIO->CRCCNF = RADIO_CRCCNF_LEN_Two;
    NRF_RADIO->CRCPOLY = 0x11021;
    NRF_RADIO->CRCINIT = 0xFFFF;

    NRF_RADIO->TXPOWER = RADIO_TXPOWER_TXPOWER_0dBm;

    NRF_RADIO->SHORTS =
        RADIO_SHORTS_READY_START_Msk |
        RADIO_SHORTS_END_DISABLE_Msk;

    NRF_RADIO->PACKETPTR =
        reinterpret_cast<uint32_t>(&txPacket);

    initialized = true;
}
#endif

//%
void native_begin() {
#if MICROBIT_CODAL
    configureRadio();
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}

//%
void send_number(int value) {
#if MICROBIT_CODAL
    if (!initialized)
        configureRadio();

    txPacket.length = 4;

    // ESB packet ID 0..3, NO_ACK=0.
    txPacket.s1 = packetId & 0x03;
    packetId = (packetId + 1) & 0x03;

    txPacket.payload[0] = (uint8_t)(value & 0xff);
    txPacket.payload[1] = (uint8_t)((value >> 8) & 0xff);
    txPacket.payload[2] = (uint8_t)((value >> 16) & 0xff);
    txPacket.payload[3] = (uint8_t)((value >> 24) & 0xff);

    NRF_RADIO->PACKETPTR =
        reinterpret_cast<uint32_t>(&txPacket);

    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_TXEN = 1;

    waitDisabled();
#else
    (void)value;
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}

//%
void send_text(String text) {
#if MICROBIT_CODAL
    if (!initialized)
        configureRadio();

    uint32_t length = PXT_STRING_DATA_LENGTH(text);
    if (length > sizeof(txPacket.payload))
        length = sizeof(txPacket.payload);

    txPacket.length = (uint8_t)length;

    // ESB packet ID 0..3, NO_ACK=0.
    txPacket.s1 = packetId & 0x03;
    packetId = (packetId + 1) & 0x03;

    const char *data = PXT_STRING_DATA(text);
    for (uint32_t i = 0; i < length; ++i)
        txPacket.payload[i] = (uint8_t)data[i];

    NRF_RADIO->PACKETPTR =
        reinterpret_cast<uint32_t>(&txPacket);

    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_TXEN = 1;

    waitDisabled();
#else
    (void)text;
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}

//%
int native_probe() {
    return 222;
}

}
