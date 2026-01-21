#include <cstddef>
#include <cstdint>

typedef enum {
    WIFI_UNITIALIZED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_DISCONNECTED,
    WIFI_FAILED
} connection_status_t;

void transport_wifi_init();
void transport_wifi_poll();
void transport_wifi_send_byte(const uint8_t*, size_t);