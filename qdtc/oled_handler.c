#include QMK_KEYBOARD_H
#include "split_util.h"
#include "split_handler.h"
#include "utils.h"
#include "oled_handler.h"
#include "layers.h"

#define LOGO_OFFSET 0
#define LAYER_OFFSET 2
#define COMBO_OFFSET 5
#define RGB_OFFSET 6
#define WPM_OFFSET 7
#define LAYOUT_OFFSET 8
#define MATRIX_OFFSET 9
#define MATRIX_KEY_X_OFFSET 7

uint8_t transmission_last_y = 8;
uint8_t matrix_key_y_offset = 0;

void oled_task_user_once(void) {
    if (is_keyboard_left()) {
      oled_task_user_once_left();
    } else {
      oled_task_user_once_right();
    }
}

void oled_task_user_once_left(void) {
    oled_render_logo();
    oled_render_layer(get_highest_layer(layer_state));
    oled_render_wpm(0);
    oled_render_connection_matrix(false);
    oled_render_layout(LAYER_BASE);
}

void oled_task_user_once_right(void) {
    oled_render_logo();
}

void oled_render_wpm(uint8_t wpm) {
    oled_set_cursor(0, WPM_OFFSET);
    static const char p[] PROGMEM = {0xAD, 0x0};
    oled_write_P(p, false);
    char out[4] = {0x0};
    format_number(out, wpm);
    oled_write_ln(out, false);
}

void oled_render_combo(bool is_enabled) {
    oled_set_cursor(0, COMBO_OFFSET);
    static const char PROGMEM disabled[] = {0x99, 0xB9, 0x9A, 0xBA, 0x0};
    static const char PROGMEM enabled[] = {0x99, 0x9B, 0xBB, 0xBA, 0x0};
    oled_write_ln_P(is_enabled ? enabled : disabled, false);
}

void oled_render_logo(void) {
    static const char qdtc_logo[] PROGMEM = {
        0x81, 0xA1, 0x83, 0xA3,
        0x80, 0xA0, 0x82, 0xA2,
        0x00
    };
    oled_set_cursor(0, LOGO_OFFSET);
    oled_write_ln_P(qdtc_logo, false);
}

void oled_render_layer(uint8_t layer) {
    static const char layer_base[] PROGMEM = {
        0x86, 0xA6, 0x89, 0xA9,
        0x85, 0xA5, 0x88, 0xA8,
        0x00
    };

    static const char layer_num[] PROGMEM = {
        0x86, 0xAB, 0x8D, 0xA9,
        0x8A, 0xAA, 0x8C, 0xAC,
        0x0
    };

    static const char layer_nav[] PROGMEM = {
        0x86, 0x8F, 0xAF, 0xA9,
        0x8A, 0x8E, 0xAE, 0xAC,
        0x00
    };

    static const char layer_settings[] PROGMEM = {
        0x86, 0x91, 0xB1, 0xA9,
        0x8A, 0x90, 0xB0, 0xAC,
        0x0
    };

    static const char layer_function[] PROGMEM = {
        0x86, 0x93, 0xB3, 0xA9,
        0x8A, 0x92, 0xB2, 0xAC,
        0x0
    };

    static const char layer_end[] PROGMEM = {
        0x84, 0xA4, 0x87, 0xA7,
        0x0
    };

    oled_set_cursor(0, LAYER_OFFSET);
    switch (layer) {
        case LAYER_BASE:
        case LAYER_COLEMAK:
            oled_write_ln_P(layer_base, false);
            break;
        case LAYER_NUM:
            oled_write_ln_P(layer_num, false);
            break;
        case LAYER_NAV:
            oled_write_ln_P(layer_nav, false);
            break;
        case LAYER_SETTINGS:
            oled_write_ln_P(layer_settings, false);
            break;
        case LAYER_FUNCTIONS:
            oled_write_ln_P(layer_function, false);
            break;
    }
    oled_write_ln_P(layer_end, false);
}

void oled_render_rgb_mode(uint8_t mode) {
    oled_set_cursor(0, RGB_OFFSET);
    static const char p[] PROGMEM = {0x8B, 0x0};
    oled_write_P(p, false);
    char out[4] = {0x0};
    format_number(out, mode);
    oled_write_ln(out, false);
}

void oled_render_layout(uint8_t layer) {
    oled_set_cursor(0, LAYOUT_OFFSET);
    switch (layer) {
        case LAYER_BASE:
            oled_write_P(PSTR("QWTY"), false);
            break;
        case LAYER_COLEMAK:
            oled_write_P(PSTR("C-DH"), false);
            break;
        default: break;
    }
}

// Point: top left pixel, 2x2 of a key
struct point { 
    uint8_t x; 
    uint8_t y;
};

const struct point keypress_mapping[MATRIX_ROWS][MATRIX_COLS] = {
    // qwert
    {{x: 8, y: 1}, {x: 8, y: 3}, {x: 9, y: 5}, {x: 9, y: 7}, {x: 9, y: 9}, {x: 9, y: 11}},
    // asdfg
    {{x: 6, y: 1}, {x: 6, y: 3}, {x: 7, y: 5}, {x: 7, y: 7}, {x: 7, y: 9}, {x: 7, y: 11}},
    // zxcvb
    {{x: 4, y: 1}, {x: 4, y: 3}, {x: 5, y: 5}, {x: 5, y: 7}, {x: 5, y: 9}, {x: 5, y: 11}},
    // Left thumb cluster
    {{x: 0, y: 0}, {x: 0, y: 0}, {x: 0, y: 0}, {x: 3, y: 8}, {x: 3, y: 10}, {x: 3, y: 12}},
    // poiuy
    {{x: 7, y: 29}, {x: 7, y: 27}, {x: 8, y: 25}, {x: 8, y: 23}, {x: 8, y: 21}, {x: 8, y: 19}},
    // ;lkjh
    {{x: 5, y: 29}, {x: 5, y: 27}, {x: 6, y: 25}, {x: 6, y: 23}, {x: 6, y: 21}, {x: 6, y: 19}},
    // /.,mn
    {{x: 3, y: 29}, {x: 3, y: 27}, {x: 4, y: 25}, {x: 4, y: 23}, {x: 4, y: 21}, {x: 4, y: 19}},
    // Right thumb cluster
    {{x: 0, y: 0}, {x: 0, y: 0}, {x: 0, y: 0}, {x: 2, y: 22}, {x: 2, y: 20}, {x: 2, y: 18}}
};

void process_record_matrix_animation(keyrecord_t *record) {
    struct point p = keypress_mapping[record->event.key.row][record->event.key.col];
    oled_write_pixel(p.x + MATRIX_KEY_X_OFFSET, p.y + matrix_key_y_offset, record->event.pressed);
    oled_write_pixel(p.x + MATRIX_KEY_X_OFFSET + 1, p.y + matrix_key_y_offset, record->event.pressed);
    oled_write_pixel(p.x + MATRIX_KEY_X_OFFSET, p.y + 1 + matrix_key_y_offset, record->event.pressed);
    oled_write_pixel(p.x + MATRIX_KEY_X_OFFSET + 1, p.y + 1 + matrix_key_y_offset, record->event.pressed);
}

void oled_render_connection_matrix(bool connected) {
    static const char corne_splitconnected[] PROGMEM = {
        0x96, 0xB6, 0x97, 0xB7,
        0x00
    };

    static const char corne_splitdisconnected[] PROGMEM = {
        0x20, 0x96, 0x98, 0x20,
        0x00
    };

    oled_set_cursor(0, MATRIX_OFFSET);
    oled_write_ln_P(connected ? corne_splitconnected : corne_splitdisconnected, false);
    matrix_key_y_offset = connected ? 0 : 8;
}

void oled_animate_transmission() {
    oled_write_pixel(0, transmission_last_y, false);
    oled_write_pixel(2, transmission_last_y, false);
    transmission_last_y++;
    if (transmission_last_y > 31) {
        transmission_last_y = 0;
    }
    oled_write_pixel(0, transmission_last_y, true);
    oled_write_pixel(2, transmission_last_y, true);
}

void oled_stop_animate_transmission() {
    oled_write_pixel(0, transmission_last_y, false);
    oled_write_pixel(2, transmission_last_y, false);
    transmission_last_y = 0;
}