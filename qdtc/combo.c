#include QMK_KEYBOARD_H
#include "custom_keycodes.h"

const uint16_t email_combo[] PROGMEM = {KC_E, KC_M, COMBO_END};
const uint16_t clear_line_combo[] PROGMEM = {KC_D, KC_L, COMBO_END};
const uint16_t left_bracket[] PROGMEM = {KC_A, KC_COMMA, COMBO_END};
const uint16_t right_bracket[] PROGMEM = {KC_A, KC_DOT, COMBO_END};
const uint16_t left_curlybracket[] PROGMEM = {KC_D, KC_COMMA, COMBO_END};
const uint16_t right_curlybracket[] PROGMEM = {KC_D, KC_DOT, COMBO_END};
const uint16_t left_paren[] PROGMEM = {KC_S, KC_COMMA, COMBO_END};
const uint16_t right_parent[] PROGMEM = {KC_S, KC_DOT, COMBO_END};
const uint16_t at[] PROGMEM = {KC_F, KC_COMMA, COMBO_END};
const uint16_t exclamation[] PROGMEM = {KC_F, KC_DOT, COMBO_END};
const uint16_t asterisk[] PROGMEM = {KC_J, KC_A, COMBO_END};
const uint16_t tilde[] PROGMEM = {KC_J, KC_T, COMBO_END};
const uint16_t dollar[] PROGMEM = {KC_J, KC_D, COMBO_END};
const uint16_t hash[] PROGMEM = {KC_J, KC_F, COMBO_END};
const uint16_t amp[] PROGMEM = {KC_K, KC_A, COMBO_END};
const uint16_t escape[] PROGMEM = {KC_K, KC_J, COMBO_END};
const uint16_t underscore[] PROGMEM = {KC_U, KC_S, COMBO_END};

uint16_t COMBO_LEN = 17;

combo_t key_combos[] = {
    COMBO(email_combo, CK_EMAIL),
    COMBO(clear_line_combo, CK_CLEARLINE),
    COMBO(left_bracket, KC_LBRC),
    COMBO(right_bracket, KC_RBRC),
    COMBO(left_curlybracket, KC_LCBR),
    COMBO(right_curlybracket, KC_RCBR),
    COMBO(left_paren, KC_LPRN),
    COMBO(right_parent, KC_RPRN),
    COMBO(at, KC_AT),
    COMBO(exclamation, KC_EXLM),
    COMBO(asterisk, KC_ASTR),
    COMBO(tilde, KC_TILD),
    COMBO(dollar, KC_DLR),
    COMBO(hash, KC_HASH),
    COMBO(amp, KC_AMPR),
    COMBO(escape, KC_ESC),
    COMBO(underscore, KC_UNDS),
};