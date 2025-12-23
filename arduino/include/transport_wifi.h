#include <cstdint>
#include <cstddef>

void transport_wifi_init();
void transport_wifi_poll();
void transport_wifi_send_byte(const uint8_t*, size_t);