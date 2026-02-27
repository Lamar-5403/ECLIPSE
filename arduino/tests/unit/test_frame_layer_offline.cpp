#include "../../include/types.h"
#include "../../include/frame_decoder.h"
#include "../../include/frame_encoder.h"
#include "../../include/crc16_ccitt_false.h"
#include "../../include/control_authority_controller.h"
#include <cstring>
#include <cstdio>

int main() {
    frame_decoder_reset();

    frame_t test_frame;
    uint8_t test_payload[] = {0x21, 0x34, 0xC5};

    frame_encode(&test_frame, msg_type_t::MSG_HEARTBEAT, test_payload, sizeof(test_payload));

    uint8_t buf[5 + FRAME_MAX_PAYLOAD];
    calc_serialized_buf(&test_frame, buf);

    for (int i = 0; i < 3 + test_frame.len + 2; i++) {
        frame_decoder_process_byte_cb(buf[i]);
    }

    printf("Frame Decoded: type: 0x%02X, len: %d, payload: ", (uint8_t)test_frame.type, test_frame.len);
    for (int i = 0; i < test_frame.len; i++) {
        printf("0x%02X, ", test_frame.payload[i]);
    }
    printf(" crc: 0x%04X", test_frame.crc);
}