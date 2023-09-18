#include "quantum.h"
#include "qmk_corne_jp_duplex.h"
#include <stdio.h>

int data1 = 0;
char data2 = ' ';
int data3 = 0;
int answer = 0;
bool is_calculating = false;
bool first_digit_input = false;
char result_str[20];

void update_display(void) {
    if (is_calculating) {
        snprintf(result_str, sizeof(result_str), "%d %c %d %c %d", data1, data2, data3, '=', answer);
    } else if(!is_calculating){
        snprintf(result_str, sizeof(result_str), "%d", data1);
    }
    oled_write(result_str, false);
}

void calc(void) {
    switch (data2) {
        case '-':
            answer = data1 - data3;
            break;
        case '+':
            answer = data1 + data3;
            break;
        case '*':
            answer = data1 * data3;
            break;
        case '/':
            if (data3 != 0) {
                answer = data1 / data3;
            } else {
                answer = 0;
            }
            break;
    }
    update_display();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_0:
            case KC_1 ... KC_9:
                if (data2 == ' ') {
                    if (!first_digit_input) {
                        data1 = keycode - KC_1 + 1;
                        first_digit_input = true;
                        data2 = ' ';
                    } else {
                        data1 = data1 * 10 + (keycode - KC_1) + 1;
                    }
                } else {
                    is_calculating = true;
                    update_display();
                    data3 = data3 * 10 + (keycode - KC_1) + 1;
                }
                update_display();
                break;
            case KC_PLUS:
                data2 = '+';
                is_calculating = true;
                update_display();
                break;
            case KC_MINUS:
                data2 = '-';
                is_calculating = true;
                update_display();
                break;
            case KC_ASTR:
                data2 = '*';
                is_calculating = true;
                update_display();
                break;
            case KC_SLSH:
                data2 = '/';
                is_calculating = true;
                update_display();
                break;
            case KC_CLR:
                data1 = 0;
                data2 = ' ';
                data3 = 0;
                is_calculating = false;
                first_digit_input = false;
                update_display();
                break;
            case KC_EQL:
                is_calculating = true;
                first_digit_input = false;
                update_display();
                break;
            case KC_ENTER:
                break;
        }
        return true;
    }
    return process_record_user(keycode, record);
}