// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_TRANSACTION_IDS_USER OLED_ID

#undef OLED_FONT_H
#define OLED_FONT_H	"./keymaps/via/font.c"

#define MATRIX_ROW_PINS { GP10, GP11, GP12, GP13 }
#define MATRIX_COL_PINS { GP2, GP3, GP4, GP2, GP3, GP4 }
#define DIODE_DIRECTION ROW2COL

#define MASTER_LEFT

#define RGBLED_NUM 42

#ifdef POINTING_DEVICE_ENABLE
    #define ANALOG_JOYSTICK_X_AXIS_PIN F6
    #define ANALOG_JOYSTICK_Y_AXIS_PIN F5
#endif

#ifdef RGB_MATRIX_ENABLE
    #define NOP_FUDGE 0.4
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP	
    #define WS2812_DI_PIN GP16
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10
#endif

#ifdef RGBLIGHT_ENABLE
    #define NOP_FUDGE 0.4
    #define WS2812_DI_PIN GP16
    #define RGBLIGHT_SPLIT
    #define RGBLED_SPLIT { 21, 21 }
//   #define RGBLIGHT_HUE_STEP 8
//   #define RGBLIGHT_SAT_STEP 8
//   #define RGBLIGHT_VAL_STEP 8
//   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
//   #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
#endif

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61
#define VIAL_KEYBOARD_UID {0x6E, 0xAA, 0x34, 0x26, 0x03, 0x6E, 0x98, 0xD4}
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
#define VIAL_COMBO_ENTRIES 6

#define DEBUG_MATRIX_SCAN_RATE
#define TAPPING_TERM 100
#define SPLIT_WPM_ENABLE

#define MIDI_ADVANCED   

#ifdef OLED_ENABLE
    #define I2C1_SCL_PIN        GP7
    #define I2C1_SDA_PIN        GP6
    #define I2C_DRIVER I2CD1
    #define OLED_DISPLAY_128x32  
#endif

#define SERIAL_USART_FULL_DUPLEX
#    define SOFT_SERIAL_PIN GP0
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#define SERIAL_USART_RX_PIN GP1
