#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Объявления функций
enum {
    PLAYER_X,
    PLAYER_O,
    PLAYER_AI
};

char board[3][3];
int stepnumb = 0;
int currentPlayer = PLAYER_X;
bool is_game_over = false;
bool initialized = false;

// Размер и позиция поля на OLED-дисплее
#define OLED_WIDTH 32
#define OLED_HEIGHT 32
#define BOARD_SIZE 3
#define CELL_SIZE (OLED_WIDTH / BOARD_SIZE)

// Графика для крестика (X) и нолика (O)
const uint8_t cross[8] = {0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b00000000};
const uint8_t circle[8] = {0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b10000001, 0b01000010, 0b00111100, 0b00000000};

bool checkWinner(char player) {
    // Проверка горизонталей, вертикалей и диагоналей
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true; // Горизонтальная линия
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true; // Вертикальная линия
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true; // Главная диагональ
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true; // Побочная диагональ
    }
    return false;
}

void initializeBoard(void) {
    if (!initialized) {
        initialized = true;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = ' ';
            }
        }
    }
    oled_write_P(PSTR("       "), false);
    if (checkWinner('X')) {
        oled_write_P(PSTR("X Win!!!"), false);
    } else if (checkWinner('O')) {
        oled_write_P(PSTR("O Win!!!"), false);
    } else if (currentPlayer == PLAYER_X) {
        oled_write_P(PSTR("X turn"), false);
    } else if (currentPlayer == PLAYER_O) {
        oled_write_P(PSTR("O turn"), false);
    }
}

void drawPixel(int x, int y) {
    if (x >= 0 && x < OLED_WIDTH && y >= 0 && y < OLED_HEIGHT) {
        oled_write_pixel(x, y, true);
    }
}

void drawBoard(void) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;

            // Отрисовать горизонтальные и вертикальные линии для создания поля
            for (int k = 0; k < CELL_SIZE; k++) {
                drawPixel(x + k, y);
                drawPixel(x + k, y + CELL_SIZE - 1);
                drawPixel(x, y + k);
                drawPixel(x + CELL_SIZE - 1, y + k);
            }

            // Отрисовать крестик, если на поле "X"
            if (board[i][j] == 'X') {
                // Отрисовать крестик (X) в центре ячейки
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        if (cross[row] & (1 << col)) {
                            drawPixel(x + CELL_SIZE / 8 * col + 1, y + CELL_SIZE / 8 * row + 1);
                        }
                    }
                }
            }

            // Отрисовать нолик, если на поле "O"
            if (board[i][j] == 'O') {
                // Отрисовать нолик (O) в центре ячейки
                for (int row = 0; row < 8; row++) {
                    for (int col = 0; col < 8; col++) {
                        if (circle[row] & (1 << col)) {
                            drawPixel(x + CELL_SIZE / 8 * col + 1, y + CELL_SIZE / 8 * row + 1);
                        }
                    }
                }
            }
        }
    }
}

int cell;
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_0:
            case KC_1 ... KC_9:
                if (!is_game_over) {
                    cell = keycode - KC_1 + 1;
                    if (cell >= 0 && cell <= 8) {
                        int row = cell / 3;
                        int col = cell % 3;

                        if (board[row][col] == ' ') {
                            board[row][col] = (currentPlayer == PLAYER_X) ? 'X' : 'O';
                            stepnumb++;
                            drawBoard();
                            if (checkWinner(board[row][col])) {
                                is_game_over = true;
                                // Display a victory message if necessary
                            } else if (stepnumb == 9) {
                                is_game_over = true;
                                // Display a draw message if necessary
                            } else {
                                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                                if (currentPlayer == PLAYER_AI) {
                                    stepnumb++;
                                    if (checkWinner('X') || checkWinner('O')) {
                                        is_game_over = true;
                                        // Display a victory message if necessary
                                    }
                                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                                }
                            }
                        }
                    }
                }
                break;
            case KC_ESC:
                srand((unsigned)timer_read32());
                currentPlayer = rand() % 2 == 0 ? PLAYER_X : PLAYER_O;
                initialized = false;
                is_game_over = false;
                stepnumb = 0;
                break;
        }
    }
    return process_record_user(keycode, record);
}