#ifdef RAW_ENABLE

    #include "raw_hid.h"

    void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
        raw_hid_send(data, length);
    }
#endif