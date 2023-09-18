#ifdef CUSTOM_KEYCODE

    #include "eeprom.h"
    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            case TEST2:
                if (record->event.pressed) {
                    g_config.animation = g_config.animation+1;
                    if(g_config.animation >= 3) {
                        g_config.animation = 3;
                    }
                } else {
                    eeconfig_update_kb(g_config.animation);
                // Do something else when release
                }
                return false; // Skip all further processing of this key
            case TEST:
                if (record->event.pressed) {
                    g_config.animation = g_config.animation-1;
                    if(g_config.animation <= 0) {
                        g_config.animation = 0;
                    }
                } else {
                    eeconfig_update_kb(g_config.animation);
                // Do something else when release
                }
                return false; // Skip all further processing of this key
            default:
                return true;
        }
    }
    
#endif