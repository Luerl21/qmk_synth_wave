#include "atmega32u4_test.h"
#include "quantum.h"
#include "analog.h"
#include "eeprom.h"
#include "print.h"

via_config g_config = {
        .animation = 1,
};

void values_load(void) {
    if(g_config.animation == 0){
        print("0 load");
    }
    if(g_config.animation == 1){
        print("1 load");
    }
    if(g_config.animation == 2){
        print("2 load");
    }
    eeprom_read_block(&g_config, ((void *) VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void values_save(void) {
    if(g_config.animation == 0){
        print("0 save");
    }
    if(g_config.animation == 1){
        print("1 save");
    }
    if(g_config.animation == 2){
        print("2 save");
    }
    eeprom_update_block(&g_config, ((void *) VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config));
}

void via_init_kb(void) {
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else {
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                values_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_animation:
            g_config.animation = *value_data;
            break;
    }
}

void via_config_get_value(uint8_t *data) {
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_animation:
            *value_data = g_config.animation;
            break;
    }
}