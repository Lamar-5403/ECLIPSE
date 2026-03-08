#pragma once
#include <cstdint>
#include <cstddef>

// System Lifecycle State
enum class life_cycle_state_t {
    BOOTSTRAP, 
    OPERATIONAL,
    DEGRADED,
    FAULT
};

// Control Authority State
enum class control_authority_state_t {
    CAS_SAFE,
    CAS_ARMING,
    CAS_ARMED,
    CAS_DISARMED,
    CAS_LOCKOUT
};

// Message type architecture
enum class msg_type_t : uint8_t {
    MSG_ARM              = 0x01,
    MSG_DISARM           = 0x02,
    MSG_STATUS_REQUEST   = 0x03,
    MSG_STATUS_RESPONSE  = 0x04,
    MSG_HEARTBEAT        = 0x05,
};

// Frame Struct
constexpr uint8_t FRAME_START_BYTE = 0xAA;
constexpr size_t FRAME_MAX_PAYLOAD = 256;

struct __attribute__((packed)) frame_t {
    uint8_t start;
    msg_type_t type;
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

// Frame Decoder State
enum class frame_decoder_state_t {
    WAIT_START,
    READ_TYPE,
    READ_LEN,
    READ_PAYLOAD,
    READ_CRC
};

// WiFi connection state
enum class connection_status_t {
    WIFI_UNINITIALIZED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_DISCONNECTED,
    WIFI_FAILED
};

// Scope Control Policies
struct tactic_policy_t {
    uint8_t tactic;
    bool allowed;
};

struct technique_policy_t {
    uint8_t technique;
    bool allowed;
};

// Cooldown Policy
struct cooldown_entry_t {
    uint8_t technique;
    uint32_t cooldown_ms;
    uint32_t last_execution;
};