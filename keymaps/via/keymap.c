#include QMK_KEYBOARD_H

enum my_keycodes {
    TEST = SAFE_RANGE,
    TEST2
};

#define _BL 0
#define _NL 1
#define _GL 2
#define _BOOT 3
#define _LIGHT 4
#define _SNAKE 5
#define _TTT 6
#define _MIDI 7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                              TG(_BOOT), KC_LGUI,   MO(_NL),  KC_SPC,     KC_Q, KC_ENT,   KC_ENT, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_NL] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, TG(_TTT), TG(_SNAKE),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                TG(_MIDI), XXXXXXX, MO(_NL),  KC_SPC,     KC_Q, KC_ENT, TG(_GL), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_GL] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_G,                         KC_1,     KC_2,    KC_3,   KC_4,    KC_5,    KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    XXXXXXX,                         KC_6,    KC_7,     KC_8,    KC_9,   KC_0,    KC_5,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_Z,    KC_1,    KC_2,    KC_3,    KC_4,                         KC_1,     KC_2,    KC_3,   KC_4,    KC_5,    KC_6,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                             KC_MUTE, KC_B,  KC_BTN3,  KC_SPC,     KC_Q, KC_ENT, TG(_GL), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_BOOT] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, QK_CLEAR_EEPROM, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                TG(_BOOT), XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_LIGHT] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            KC_MUTE,  KC_LGUI, _______,  KC_SPC,     KC_Q, KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
  [_SNAKE] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_D,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_W,    KC_S,    KC_E,    KC_R,   XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_A,  XXXXXXX, XXXXXXX, XXXXXXX, TG(_SNAKE),                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            KC_TRNS,  XXXXXXX, XXXXXXX,  XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [_TTT] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,   KC_3,   KC_6,     KC_9,  XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_2,     KC_5,    KC_8,  XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_1,    KC_4,    KC_7,   TG(_TTT), XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            KC_TRNS,  XXXXXXX, XXXXXXX,  XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
  [_MIDI] = LAYOUT_ortho_4x6(
  //,-----------------------------------------------------.                                                             ,-----------------------------------------------------.
      XXXXXXX,QK_MIDI_NOTE_C_SHARP_0,QK_MIDI_NOTE_D_SHARP_0,XXXXXXX,QK_MIDI_NOTE_F_SHARP_0,QK_MIDI_NOTE_G_SHARP_0,          QK_MIDI_NOTE_A_SHARP_0, XXXXXXX, QK_MIDI_NOTE_C_SHARP_0, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+----------------------+----------------------+-------+----------------------+----------------------|       |--------+--------+--------+--------+--------+--------|
      QK_MIDI_NOTE_C_5,QK_MIDI_NOTE_D_0,QK_MIDI_NOTE_E_0,QK_MIDI_NOTE_F_0,QK_MIDI_NOTE_G_0,QK_MIDI_NOTE_A_0,                QK_MIDI_NOTE_B_0,     QK_MIDI_NOTE_C_0,   QK_MIDI_NOTE_D_0, XXXXXXX, XXXXXXX, XXXXXXX,
  //|-----------------+----------------+---------------+--------------+-------------------+----------------------|       |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+------------------------------------------------------|       |--------+--------+--------+--------+--------+--------+--------|
                                                                        TG(_MIDI),  QK_MIDI_OCTAVE_DOWN, XXXXXXX,  XXXXXXX,           XXXXXXX, XXXXXXX, QK_MIDI_OCTAVE_UP, XXXXXXX
                                                                                //`--------------------------'              `--------------------------'
  ),

//   [2] = LAYOUT_ortho_4x6(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_NLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                              KC_MUTE, KC_LGUI,   MO(3),  KC_SPC,     KC_Q, KC_ENT, _______, KC_RALT
//                                       //`--------------------------'  `--------------------------'
//   ),
};

#include <oled/oled.c>
#include <oled/sync.c>
#include <encoder.c>
#include <custom_keycode.c>
#include <rgb_matrix.c>
// #include <raw_hid.c>