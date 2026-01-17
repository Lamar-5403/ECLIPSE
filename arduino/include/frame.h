#pragma once
#include <stdint.h>

#define FRAME_START_BYTE 0xAA
#define FRAME_MAX_PAYLOAD 256

typedef struct __attribute__((packed)) {
    uint8_t start;
    uint8_t type;
    uint8_t len;
    uint8_t payload[FRAME_MAX_PAYLOAD];
    uint16_t crc;
} frame_t;

// Message type architecture
typedef enum {
    MSG_ARM              = 0x01,
    MSG_DISARM           = 0x02,
    MSG_STATUS_REQUEST   = 0x03,
    MSG_STATUS_RESPONSE  = 0x04,
    MSG_HEARTBEAT        = 0x05,
} msg_type_t;