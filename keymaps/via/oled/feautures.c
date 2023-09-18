#include QMK_KEYBOARD_H
#include "quantum.h"
#include "qmk_corne_jp_duplex.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// Tic Tac Toe

// Объявления функций
enum {
    PLAYER_X,
    PLAYER_O,
    PLAYER_AI
};

int game = 0;

char board[3][3];
int stepnumb = 0;
int currentPlayer = PLAYER_X;
bool is_game_over = false;
bool initialized = false;
bool gameMode = true;

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
    if (stepnumb == 9) {
        oled_write_P(PSTR("Draw"), false);   
    }
        if (gameMode) {
            if (checkWinner('X') && stepnumb != 9) {
                oled_write_P(PSTR("X Win!!!"), false);
            } else if (checkWinner('O') && stepnumb != 9) {
                oled_write_P(PSTR("O Win!!!"), false);
            } else {
                if (currentPlayer == PLAYER_X && stepnumb != 9) {
                    oled_write_P(PSTR("X turn"), false);
                } else if (currentPlayer == PLAYER_O && stepnumb != 9) {
                    oled_write_P(PSTR("O turn"), false);
                }
            }
        } else {
            if (checkWinner('X') && stepnumb != 9) {
                oled_write_P(PSTR("X Win!!!"), false);
            } else if (checkWinner('O') && stepnumb != 9) {
                oled_write_P(PSTR("AI Win!!!"), false);
            } else {
                if (currentPlayer == PLAYER_X && stepnumb != 9) {
                    oled_write_P(PSTR("Your turn"), false);
                } else if (currentPlayer == PLAYER_AI && stepnumb != 9) {
                    oled_write_P(PSTR("AI turn"), false);
                }
            }
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

// Calculator

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

void calculator_g(void) {
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

// Snake

#ifdef EEPROM_HIGHSCORE
typedef union {
  uint8_t raw;
  struct {
    uint8_t storedHighScore :8;
  };
} gameData_t;

gameData_t gameData;

extern gameData_t gameData;
#endif
void render_game(void);
void moveCheck(void);
uint8_t snake_lastdir; 
uint8_t snake_dir;
bool snakeRestart;
bool game_is_running;

#define SNAKE_MAX_LENGTH 32

#ifndef SNAKE_STARTING_LENGTH
#   define SNAKE_STARTING_LENGTH 3
#endif

#ifndef FOOD_FLASH_RATE
#   define FOOD_FLASH_RATE 250
#endif

#ifndef OLED_DISPLAY_WIDTH
#   define OLED_DISPLAY_WIDTH 128
#endif

#ifndef OLED_DISPLAY_HEIGHT
#   define OLED_DISPLAY_HEIGHT 32
#endif

#ifndef GAME_SCALE
#   define GAME_SCALE 2
#endif

#define GAME_DISPLAY_WIDTH OLED_DISPLAY_WIDTH
#define GAME_DISPLAY_HEIGHT OLED_DISPLAY_HEIGHT

typedef struct {
  uint8_t x;
  uint8_t y;
} SnakeSegment;

enum snakeDirections {
    sUP,
    sRIGHT,
    sDOWN,
    sLEFT
};

SnakeSegment snakes[SNAKE_MAX_LENGTH];

char scoreString[9];
char highScoreString[9];

uint8_t snakeLength = SNAKE_STARTING_LENGTH;
uint8_t snake_dir;
uint8_t snake_lastdir;
uint8_t foodX, foodY;
uint8_t score = 0;
uint8_t GAME_SPEED = 160;
uint8_t highScore = 0;

uint8_t maxSnakeLength = SNAKE_STARTING_LENGTH;

uint16_t foodTimer = 0;
uint16_t moveTimer;

bool foodVisible = true;

bool snakeInitialised = false;
bool snakeRestart = false;
bool game_is_running = false;

bool game_over = false;
bool game_win = false;
bool render_infos = false;

bool check_food_overlap(void) {
    for (uint8_t i = 0; i < snakeLength; i++) {
        if (foodX == snakes[i].x && foodY == snakes[i].y) {
            return true;
        }
    };
    return false;
}

void spawn_food(void) {
    foodX = (random() % (GAME_DISPLAY_WIDTH - 2 * GAME_SCALE)) + GAME_SCALE; // Исключаем рамку
    foodY = (random() % (GAME_DISPLAY_HEIGHT - 2 * GAME_SCALE)) + GAME_SCALE; // Исключаем рамку
    
    for (uint8_t i = 0; i < snakeLength; i++) {
        if (foodX == snakes[i].x && foodY == snakes[i].y) {
            spawn_food();
            return;
        }
    }
}

void remove_tail(void) {
  oled_write_pixel(snakes[maxSnakeLength].x, snakes[maxSnakeLength].y, false);
}

void update_snake(void) {
    if (snakes[0].x >= GAME_DISPLAY_WIDTH-1) {
        game_over = true;
    } else if (snakes[0].x <= 0) {
        game_over = true;
    }
    if (snakes[0].y >= GAME_DISPLAY_HEIGHT-1) {
        game_over = true;
    } else if (snakes[0].y <= 0) {
        game_over = true;
    }
    for (uint8_t i = 1; i < snakeLength; i++) {
        if (snakes[i].x == snakes[0].x && snakes[i].y == snakes[0].y) {
            game_over = true;
        }
    }
    if (snakes[0].x == foodX && snakes[0].y == foodY) {
        snakeLength++;
        score++;
        if(GAME_SPEED > 5){
            GAME_SPEED-=5;
        }
        if (snakeLength >= SNAKE_MAX_LENGTH) {
            game_win = true;
            game_over = true;
        }
        spawn_food();
    }

    if (snakeLength > maxSnakeLength) {
        remove_tail();
    }
}

void init_snake(void) {
    snakeLength = SNAKE_STARTING_LENGTH;
    for (uint8_t i = 0; i < snakeLength; i++) {
        snakes[i].x = GAME_DISPLAY_WIDTH / 2;
        snakes[i].y = GAME_DISPLAY_HEIGHT / 2;
    }
    snake_dir = sRIGHT;
    snake_lastdir = snake_dir;
    for(uint8_t i=1; i<snakeLength; i++) {
        if (snakes[0].x == snakes[i].x && snakes[0].y == snakes[i].y) {
            snakes[0].x++;
        }
    }
    spawn_food();
    moveTimer = timer_read();
    snakeInitialised = true;
    game_is_running = true;
}

void checkMove(void) {
    if (snake_dir == sRIGHT && snake_lastdir == sLEFT) {
      snake_dir = snake_lastdir;
    }
    if (snake_dir == sLEFT && snake_lastdir == sRIGHT) {
      snake_dir = snake_lastdir;
    }
    if (snake_dir == sUP && snake_lastdir == sDOWN) {
      snake_dir = snake_lastdir;
    }
    if (snake_dir == sDOWN && snake_lastdir == sUP) {
      snake_dir = snake_lastdir;
    }
}

void move_snake(void) {
    checkMove();
    SnakeSegment new_head = snakes[0];

    switch (snake_dir) {
        case sUP:
        new_head.y--;
        break;
        case sDOWN:
        new_head.y++;
        break;
        case sLEFT:
        new_head.x--;
        break;
        case sRIGHT:
        new_head.x++;
        break;
        default:
        break;
    }

    for (uint8_t i = snakeLength; i > 0; i--) {
        snakes[i] = snakes[i - 1];
    }

    snakes[0] = new_head;
    snake_lastdir = snake_dir;

    if (snakeLength > maxSnakeLength) {
        remove_tail();
    }

    update_snake();
}

void draw_border(void) {
    for (uint8_t x = 0; x < OLED_DISPLAY_WIDTH; x++) {
        oled_write_pixel(x, 0, true);
        oled_write_pixel(x, OLED_DISPLAY_HEIGHT - 1, true);
    }
    for (uint8_t y = 0; y < OLED_DISPLAY_HEIGHT; y++) {
        oled_write_pixel(0, y, true);
        oled_write_pixel(OLED_DISPLAY_WIDTH - 1, y, true);
    }
}

void render_snake(void) {
  for (uint8_t i = 0; i < snakeLength; i++) {
    oled_write_pixel(snakes[i].x, snakes[i].y, true);
  }

  for (uint8_t i = snakeLength; i < SNAKE_MAX_LENGTH; i++) {
    oled_write_pixel(snakes[i].x, snakes[i].y, false);
  }
}

void render_food(void) {
    if(foodVisible) {
        oled_write_pixel(foodX, foodY, true);
    } else {
        oled_write_pixel(foodX, foodY, false);
    }
}

void check_highscore(void){
#ifdef EEPROM_HIGHSCORE
  gameData.raw = eeconfig_read_kb();
  highScore = gameData.storedHighScore;
  if ( score > highScore ) {
    gameData.storedHighScore = score;
    eeconfig_update_kb(gameData.raw);
  }
#else
  if (score > highScore) {
    highScore = score;
  }
#endif
}

void gameRestart(void){
        GAME_SPEED = 160;
        render_infos = false;
        game_over = false;
        game_win = false;
        snakeInitialised = false;
        snakeRestart = !snakeRestart;
}

void render_gameover(void) {
    if (game_win) {
        oled_clear();
        oled_set_cursor(0, 1);
        oled_write_P(PSTR("WOW!"), false);
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("YOU WON!"), false); 
        oled_set_cursor(0, 3);
        oled_write_P(PSTR("Go touch grass!"), false); 
    } else {
        // Update highscore
        check_highscore();
        if (game_is_running) {
            game_is_running = !game_is_running;
        }
        // Output score to scoreString
        sprintf(scoreString, "%u", score);
        sprintf(highScoreString, "%u", highScore);
        oled_clear();
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("GAME OVER"), false); 
        oled_set_cursor(0, 1);
        oled_write_P(PSTR("Score:"), false); 
        oled_write_ln(scoreString, false);
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("HiScore:"), false); 
        oled_write_ln(highScoreString, false);
        oled_set_cursor(0, 3);
        oled_write_P(PSTR("Play Again? y/n"), false);
        if (snakeRestart) {
          gameRestart();
        }
    }
}

void render_info(void) {
        render_infos = true;
        // Update highscore
        check_highscore();
        // Output score to scoreString
        sprintf(scoreString, "%u", score);
        sprintf(highScoreString, "%u", highScore);
        oled_clear();
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Score:"), false); 
        oled_write_ln(scoreString, false);
        oled_set_cursor(0, 1);
        oled_write_P(PSTR("HiScore:"), false); 
        oled_write_ln(highScoreString, false);
        oled_set_cursor(0, 2);
        oled_write_P(PSTR("Start? y/n"), false);
        if (snakeRestart) {
          gameRestart();
        }
}

void snake_game(void) {
    if (render_infos) {
        game_over = false;
        game_win = false;
        snakeInitialised = false;
        snakeRestart = !snakeRestart;
    } else if (!game_over) {
        if (!snakeInitialised) {
        oled_clear();
        init_snake();
        draw_border();
        render_snake();
        render_food();
        }
        if (timer_elapsed(moveTimer) > GAME_SPEED) {
        move_snake();
        update_snake();
        moveTimer = timer_read();
        }
        if(timer_elapsed(foodTimer) > FOOD_FLASH_RATE) {
        foodVisible = !foodVisible;
        foodTimer = timer_read();
        }
        render_snake();
        render_food();
  } else if(game_over) {
        render_gameover();
  }
}

int cell;
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(game){
            case 1:
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
                                    } else if (stepnumb == 9) {
                                        is_game_over = true;
                                    } else {
                                        if (gameMode) {
                                            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                                        } else {
                                            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_AI : PLAYER_X;
                                            if (currentPlayer == PLAYER_AI) {
                                                // Логика хода AI
                                                do {
                                                    cell = rand() % 9;
                                                    row = cell / 3;
                                                    col = cell % 3;
                                                } while (board[row][col] != ' ');

                                                board[row][col] = 'O';
                                                stepnumb++;
                                                drawBoard();

                                                if (checkWinner('O')) {
                                                    is_game_over = true;
                                                } else if (stepnumb == 9) {
                                                    is_game_over = true;
                                                } else {
                                                    currentPlayer = PLAYER_X;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case KC_ESC:
                        gameMode = !gameMode;
                            if (gameMode) {
                                srand((unsigned)timer_read32());
                                currentPlayer = rand() % 2 == 0 ? PLAYER_X : PLAYER_O;
                            } else {
                                currentPlayer = PLAYER_X;
                            }
                        initialized = false;
                        is_game_over = false;
                        stepnumb = 0;
                        break;
                }
            break;
            case 2:
                switch(keycode) {
                    case KC_W:
                        snake_dir = sUP;
                        break;
                    case KC_A:
                        snake_dir = sLEFT;
                        break;
                    case KC_S:
                        snake_dir = sDOWN;
                        break;
                    case KC_D:
                        snake_dir = sRIGHT;
                        break;
                    case KC_I:
                        snake_dir = sUP;
                        break;
                    case KC_J:
                        snake_dir = sLEFT;
                        break;
                    case KC_K:
                        snake_dir = sDOWN;
                        break;
                    case KC_L:
                        snake_dir = sRIGHT;
                        break;
                    case KC_E:
                        oled_clear();
                        gameRestart();
                        break;
                    case KC_R:
                        oled_clear();
                        render_info();
                        break;
                    case KC_O:
                        oled_clear();
                        gameRestart();
                        break;
                    case KC_P:
                        oled_clear();
                        render_info();
                        break;
                }
            break;
            case 3:
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
            break;
        }
        return true;
    }
    return process_record_user(keycode, record);
}

void tic_tac_toe(int game_number){
    game = game_number;
    oled_clear();
    initializeBoard();
    drawBoard();
}

void snake(int game_number){
    game = game_number;
    snake_game();
}

void calculator(int game_number){
    game = game_number;
    oled_clear();
    calculator_g();
}