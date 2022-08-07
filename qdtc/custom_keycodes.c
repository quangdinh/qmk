#include QMK_KEYBOARD_H
#include "custom_keycodes.h"

bool process_custom_keycode(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case CK_EMAIL:
            SEND_STRING("youremail@here");
            break;
        case CK_CLEARLINE:
            tap_code16(KC_END);
            tap_code16(S(KC_HOME));
            tap_code16(KC_BSPC);
            break;
    }

    return true;
}