#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "config.h"
#include "quantum.h"
#include "debounce.h"
#include "print.h"
#include <qmk_corne_jp_duplex.h>

#define MATRIX_IO_DELAY 30
#define COL_SHIFTER ((uint16_t)1)

static const pin_t row_pins[] = { GP10, GP11, GP12, GP13, GP10, GP11, GP12, GP13 };
static const pin_t col_pins[] = MATRIX_COL_PINS;
static matrix_row_t previous_matrix[MATRIX_ROWS];

static void select_pin(pin_t pin) {
    setPinOutput(pin);
    writePinLow(pin);
}

static void unselect_pin(pin_t pin) {
    setPinInputHigh(pin);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS/2; x++) {
        unselect_pin(col_pins[x*2]);
    }
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        unselect_pin(row_pins[x]);
    }
}

static void read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    select_pin(row_pins[current_row]);
    wait_us(MATRIX_IO_DELAY);

    for (uint8_t col_index = 0; col_index < MATRIX_COLS / 2; col_index++) {
        uint16_t column_index_bitmask = COL_SHIFTER << ((col_index * 2) + 1);
        uint8_t real_col_index = (current_row < MATRIX_ROWS / 2) ? col_index : col_index + MATRIX_COLS / 2;

        if (readPin(col_pins[real_col_index])) {
            current_matrix[current_row] &= ~column_index_bitmask;
        } else {
            current_matrix[current_row] |= column_index_bitmask;
        }
    }

    unselect_pin(row_pins[current_row]);
}

static void read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    select_pin(col_pins[current_col]);
    wait_us(MATRIX_IO_DELAY);

    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        if (readPin(row_pins[row_index])) {
            current_matrix[row_index] &= ~(1 << (current_col * 2));
        } else {
            current_matrix[row_index] |= (1 << (current_col * 2));
        }
    }

    unselect_pin(col_pins[current_col]);
}

void matrix_init_custom(void) {
    unselect_cols();
    unselect_rows();
    setPinInput(row_pins[MATRIX_ROWS-1]);
    writePinHigh(row_pins[MATRIX_ROWS-1]);
    debounce_init(MATRIX_ROWS);
}

void store_old_matrix(matrix_row_t current_matrix[]) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        previous_matrix[i] = current_matrix[i];
    }
}

bool has_matrix_changed(matrix_row_t current_matrix[]) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (previous_matrix[i] != current_matrix[i]) return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    store_old_matrix(current_matrix);

    for (uint8_t current_col = 0; current_col < MATRIX_COLS / 2; current_col++) {
        read_rows_on_col(current_matrix, current_col);
    }

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        read_cols_on_row(current_matrix, current_row);
    }

    return has_matrix_changed(current_matrix);
}