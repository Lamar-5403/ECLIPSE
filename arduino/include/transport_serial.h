#include <cstddef>
#include <cstdint>

void transport_serial_init();
void transport_serial_poll();
void transport_serial_send_byte(const uint8_t*, size_t);