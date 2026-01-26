#pragma once
#include <cstdint>
#include <cstddef>

constexpr uint8_t FRAME_START_BYTE = 0xAA;
constexpr size_t FRAME_MAX_PAYLOAD = 256;

struct __attribute__((packed)) frame_t {
    uint8_t start;
    uint8_t type;
    uint8_t len;
    uint8_t payload[FRAME_MAX_PAYLOAD];
    uint16_t crc;

    frame_t() = default;
    frame_t(const frame_t&) = delete;
    frame_t& operator=(const frame_t&) = delete;
    static void* operator new(size_t) = delete;
    static void* operator new[](size_t) = delete;
};

constexpr size_t FRAME_WIRE_SIZE = 1 + 1 + 1 + FRAME_MAX_PAYLOAD + 2;

static_assert(
    sizeof(frame_t) == FRAME_WIRE_SIZE,
        "frame_t layout mismatch"
);

// Message type architecture
enum class msg_type_t {
    MSG_ARM              = 0x01,
    MSG_DISARM           = 0x02,
    MSG_STATUS_REQUEST   = 0x03,
    MSG_STATUS_RESPONSE  = 0x04,
    MSG_HEARTBEAT        = 0x05,
};