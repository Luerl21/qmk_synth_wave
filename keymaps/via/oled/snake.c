#include "quantum.h"
#include "qmk_corne_jp_duplex.h"
#include "snake.h"
#include <stdio.h>
#include <stdbool.h>

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

// Update game values in ms
// #ifndef GAME_SPEED
// #   define GAME_SPEED 150
// #endif

#ifndef GAME_SCALE
#   define GAME_SCALE 2
#endif

#define GAME_DISPLAY_WIDTH OLED_DISPLAY_WIDTH
#define GAME_DISPLAY_HEIGHT OLED_DISPLAY_HEIGHT

typedef struct {
  uint8_t x;
  uint8_t y;
} SnakeSegment;

// Snake direction enum
enum snakeDirections {
    sUP,
    sRIGHT,
    sDOWN,
    sLEFT
};


SnakeSegment snake[SNAKE_MAX_LENGTH];

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
        if (foodX == snake[i].x && foodY == snake[i].y) {
            return true;
        }
    };
    return false;
}

void spawn_food(void) {
    foodX = (random() % (GAME_DISPLAY_WIDTH - 2 * GAME_SCALE)) + GAME_SCALE; // Исключаем рамку
    foodY = (random() % (GAME_DISPLAY_HEIGHT - 2 * GAME_SCALE)) + GAME_SCALE; // Исключаем рамку
    
    for (uint8_t i = 0; i < snakeLength; i++) {
        if (foodX == snake[i].x && foodY == snake[i].y) {
            spawn_food();
            return;
        }
    }
}

void remove_tail(void) {
  oled_write_pixel(snake[maxSnakeLength].x, snake[maxSnakeLength].y, false);
}

void update_snake(void) {
    // Check if snake is at the edge of the screen.
    if (snake[0].x >= GAME_DISPLAY_WIDTH-1) {
        game_over = true;
    } else if (snake[0].x <= 0) {
        game_over = true;
    }
    if (snake[0].y >= GAME_DISPLAY_HEIGHT-1) {
        game_over = true;
    } else if (snake[0].y <= 0) {
        game_over = true;
    }
    // Check for collision with itself
    for (uint8_t i = 1; i < snakeLength; i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
            game_over = true;
        }
    }
    // Check for collision with food
    if (snake[0].x == foodX && snake[0].y == foodY) {
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
        snake[i].x = GAME_DISPLAY_WIDTH / 2;
        snake[i].y = GAME_DISPLAY_HEIGHT / 2;
    }
    snake_dir = sRIGHT;
    snake_lastdir = snake_dir;
    for(uint8_t i=1; i<snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            snake[0].x++;
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
    SnakeSegment new_head = snake[0];

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
        snake[i] = snake[i - 1];
    }

    snake[0] = new_head;
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
    oled_write_pixel(snake[i].x, snake[i].y, true);
  }

  for (uint8_t i = snakeLength; i < SNAKE_MAX_LENGTH; i++) {
    oled_write_pixel(snake[i].x, snake[i].y, false);
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

void render_game(void) {
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

    bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
        if (record->event.pressed){
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
            return true;
        }
	    return process_record_user(keycode, record);
    }