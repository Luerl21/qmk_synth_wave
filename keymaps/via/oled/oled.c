#ifdef OLED_ENABLE
    #include <qmk_corne_jp_duplex.h>
    #include <stdio.h>
    #include <os_detection.h>
    #include <oled/feautures.c>
    #include <oled/images.c>
    #include <oled/bootlogo.c>
    #include <oled/arasaka.c>
    // #include <oled/girl.c>
    // #include <oled/sf.c>

    /////////////////////////// Boot logo
        void keyboard_pre_init_user(void) {
            test = true;
            oled_clear();
        }
    ///////////////////////////

    /////////////////////////// Rotate OLED display
    // oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // 	if (!is_keyboard_master()) return OLED_ROTATION_0;
    //     else return OLED_ROTATION_0;
    // }
    ///////////////////////////

    uint8_t rotation_oled = 0;
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
                        int value = g_config.animation;
                        if(value == 8) { 
                            rotation_oled = 2;
                            return OLED_ROTATION_270; 
                        }
                        else {
                            rotation_oled = 1;
                            return OLED_ROTATION_0; 
                        }
                    }


    /////////////////////////// Render master OLED display animation
    static void render_master(void) {
        int value = g_config.animation;
        switch (get_highest_layer(layer_state)) {
            /////////////////////////// Layer 3
            case 3:
                oled_write_raw_P(warning, sizeof(warning));
                oled_scroll_left();
            break;
            /////////////////////////// Layer 5
            case 6:
            value = 6;
            oled_clear();
            tic_tac_toe(1);
            break;
            /////////////////////////// Layer 6
            case 5:
            value = 5;
            snake(2);
            break;
            default:
                oled_scroll_off();
                if(value != 8 && rotation_oled == 2){
                    soft_reset_keyboard();
                }
                if (value == 0){
                void animation_phase(void) {

                    if (get_current_wpm() <=IDLE_SPEED) {
                        current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
                        oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
                    }

                    if (get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED) {
                        oled_write_raw_P(prep[0], ANIM_SIZE);
                    }

                    if (get_current_wpm() >=TAP_SPEED) {
                        current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
                        oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
                    }
                }

                if (get_current_wpm() != 000) {
                    oled_on();

                    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                        anim_timer = timer_read32();
                        animation_phase();
                    }

                    anim_sleep = timer_read32();
                } else {
                    if (timer_elapsed32(anim_sleep) > oled_timeout) {
                        oled_off();
                    } else {
                        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                            anim_timer = timer_read32();
                            animation_phase();
                        }
                    }
                }
                }
                if (value == 1){
                    oled_clear();
                    /////////////////////////// WPM
                    oled_write_P(PSTR("WPM: "), false);
                    oled_write(get_u8_str(get_current_wpm(), '0'), false);
                    // sprintf(wpm_str, "%03d", get_current_wpm());
                    // oled_write_P(PSTR(" WPM "), false);
                    // oled_write(wpm_str, false);
                    oled_write_P(PSTR("     "), false);
                    #ifdef OS_DETECTION_ENABLE
                        char data;
                        switch (detected_host_os()) {
                            case OS_UNSURE:
                                data = 0x01; // Face mark
                                break;
                            case OS_LINUX:
                                data = 0x99; // Penguin
                                break;
                            case OS_WINDOWS:
                                data = 0x97; // Window
                                break;
                            case OS_MACOS:
                                data = 0x95; // Banana
                                break;
                            case OS_IOS:
                                data = 0x95; // Banana
                                break;
                            default:
                                data = 0x3F; // ?
                                break;
                        }

                        uint8_t x = 19;
                        uint8_t y = 0;
                        oled_set_cursor(x, y++);
                        oled_write_char(data++, false);
                        oled_write_char(data, false);
                        data += 31;
                        oled_set_cursor(x, y);
                        oled_write_char(data++, false);
                        oled_write_char(data, false);
                    #endif

                    /////////////////////////// Layer indicator
                    oled_write_P(PSTR(" LAYER - "), false);
                    switch (get_highest_layer(layer_state)) {
                    /////////////////////////// Layer 6
                        // case 6:
                        //     value = 6;
                        //     tic_tac_toe(1);
                        // break;
                    /////////////////////////// Layer 5
                        // case 5:
                        //     value = 5;
                        //     snake(2);
                        // break;
                    /////////////////////////// Layer 4
                        case 4:
                        oled_write_P(PSTR(" LIGHT "), false);
                        break;
                    /////////////////////////// Layer 3
                        // case 3:
                        // oled_write_P(PSTR(" BOOT "), false);
                        // break;
                    /////////////////////////// Layer 2
                        case 2:
                        oled_write_P(PSTR(" GAME "), false);
                        break;
                    /////////////////////////// Layer 1
                        case 1:
                            oled_write_P(PSTR(" NUMBER "), false);
                            break;
                    /////////////////////////// Layer 0
                        default:
                            oled_write_P(PSTR(" BASE "), false);
                            break;
                    }
                    
                    oled_write_P(PSTR("\n"), false);

                    /////////////////////////// Host Keyboard LED Status
                    led_t led_state = host_keyboard_led_state();
                    oled_write_P(led_state.num_lock ? PSTR(" NUM ") : PSTR("     "), false);
                    oled_write_P(led_state.caps_lock ? PSTR(" CAP ") : PSTR("     "), false);
                    oled_write_P(led_state.scroll_lock ? PSTR(" SCR ") : PSTR("    "), false);
                }
                if(value == 2){
                    oled_write_raw_P(FA, sizeof(FA));
                }
                if(value == 3){
                    oled_write_raw_P(PA, sizeof(PA));
                }
                if(value == 4){
                    oled_write_raw_P(EYE, sizeof(PA));
                }
                if(value == 5){
                    oled_clear();
                    tic_tac_toe(1);
                }
                if(value == 6){
                    snake(2);
                }
                if(value == 7){
                    oled_clear();
                    calculator(3);
                }
                if(value == 8){
                    if(rotation_oled == 1){
                        soft_reset_keyboard();
                    }
                    arasaka_draw();
                }
                if(value == 9){
                    // oled_write_raw_P(EB, sizeof(EB));
                    // girl();
                    // sf();
                }  
            break;  
        }
    }
    

    /////////////////////////// Render left OLED display
    static void render_slave(void) {
        
        int value = g_config.animation;
        switch (get_highest_layer(layer_state)) {
            /////////////////////////// Layer 3
            case 3:
                oled_write_raw_P(warning, sizeof(warning));
                oled_scroll_left();
            break;
            /////////////////////////// Layer 5
            case 6:
            value = 6;
            oled_clear();
            tic_tac_toe(1);
            break;
            /////////////////////////// Layer 6
            case 5:
            value = 5;
            snake(2);
            break;
            default:
                oled_scroll_off();
                if(value != 8 && rotation_oled == 2){
                    soft_reset_keyboard();
                }
                if (value == 0){
                void animation_phase(void) {

                    if (get_current_wpm() <=IDLE_SPEED) {
                        current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
                        oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)], ANIM_SIZE);
                    }

                    if (get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED) {
                        oled_write_raw_P(prep[0], ANIM_SIZE);
                    }

                    if (get_current_wpm() >=TAP_SPEED) {
                        current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
                        oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
                    }
                }

                if (get_current_wpm() != 000) {
                    oled_on();

                    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                        anim_timer = timer_read32();
                        animation_phase();
                    }

                    anim_sleep = timer_read32();
                } else {
                    if (timer_elapsed32(anim_sleep) > oled_timeout) {
                        oled_off();
                    } else {
                        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                            anim_timer = timer_read32();
                            animation_phase();
                        }
                    }
                }
                }
                if (value == 1){
                    oled_clear();
                    /////////////////////////// WPM
                    oled_write_P(PSTR("WPM: "), false);
                    oled_write(get_u8_str(get_current_wpm(), '0'), false);
                    // sprintf(wpm_str, "%03d", get_current_wpm());
                    // oled_write_P(PSTR(" WPM "), false);
                    // oled_write(wpm_str, false);
                    oled_write_P(PSTR("     "), false);
                    #ifdef OS_DETECTION_ENABLE
                        char data;
                        switch (detected_host_os()) {
                            case OS_UNSURE:
                                data = 0x01; // Face mark
                                break;
                            case OS_LINUX:
                                data = 0x99; // Penguin
                                break;
                            case OS_WINDOWS:
                                data = 0x97; // Window
                                break;
                            case OS_MACOS:
                                data = 0x95; // Banana
                                break;
                            case OS_IOS:
                                data = 0x95; // Banana
                                break;
                            default:
                                data = 0x3F; // ?
                                break;
                        }

                        uint8_t x = 19;
                        uint8_t y = 0;
                        oled_set_cursor(x, y++);
                        oled_write_char(data++, false);
                        oled_write_char(data, false);
                        data += 31;
                        oled_set_cursor(x, y);
                        oled_write_char(data++, false);
                        oled_write_char(data, false);
                    #endif

                    /////////////////////////// Layer indicator
                    oled_write_P(PSTR(" LAYER - "), false);
                    switch (get_highest_layer(layer_state)) {
                    /////////////////////////// Layer 6
                        // case 6:
                        //     value = 6;
                        //     tic_tac_toe(1);
                        // break;
                    /////////////////////////// Layer 5
                        // case 5:
                        //     value = 5;
                        //     snake(2);
                        // break;
                    /////////////////////////// Layer 4
                        case 4:
                        oled_write_P(PSTR(" LIGHT "), false);
                        break;
                    /////////////////////////// Layer 3
                        // case 3:
                        // oled_write_P(PSTR(" BOOT "), false);
                        // break;
                    /////////////////////////// Layer 2
                        case 2:
                        oled_write_P(PSTR(" GAME "), false);
                        break;
                    /////////////////////////// Layer 1
                        case 1:
                            oled_write_P(PSTR(" NUMBER "), false);
                            break;
                    /////////////////////////// Layer 0
                        default:
                            oled_write_P(PSTR(" BASE "), false);
                            break;
                    }
                    
                    oled_write_P(PSTR("\n"), false);

                    /////////////////////////// Host Keyboard LED Status
                    led_t led_state = host_keyboard_led_state();
                    oled_write_P(led_state.num_lock ? PSTR(" NUM ") : PSTR("     "), false);
                    oled_write_P(led_state.caps_lock ? PSTR(" CAP ") : PSTR("     "), false);
                    oled_write_P(led_state.scroll_lock ? PSTR(" SCR ") : PSTR("    "), false);
                }
                if(value == 2){
                    oled_write_raw_P(FA, sizeof(FA));
                }
                if(value == 3){
                    oled_write_raw_P(PA, sizeof(PA));
                }
                if(value == 4){
                    oled_write_raw_P(EYE, sizeof(PA));
                }
                if(value == 5){
                    oled_clear();
                    tic_tac_toe(1);
                }
                if(value == 6){
                    snake(2);
                }
                if(value == 7){
                    oled_clear();
                    calculator(3);
                }
                if(value == 8){
                    if(rotation_oled == 1){
                        soft_reset_keyboard();
                    }
                    arasaka_draw();
                }
                if(value == 9){
                    // oled_write_raw_P(EB, sizeof(EB));
                    // girl();
                    // sf();
                }  
            break;  
        }
    }

    bool oled_task_user(void) {
            if(test && rotation_oled == 1){
                bootlogo();
            } else {
                if (is_keyboard_master()) {
                    // Left side
                    render_master();
                } else {
                    // Right side
                    render_slave();
                }
            }
    return false;
    }
#endif