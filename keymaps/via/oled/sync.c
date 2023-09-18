#include "transactions.h"
#include "eeprom.h"

void oled_slave_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    g_config.animation = *((uint8_t *)initiator2target_buffer);
    eeprom_update_block(&g_config, ((void *) VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void keyboard_post_init_kb(void) {
    transaction_register_rpc(OLED_ID, oled_slave_sync);
}

