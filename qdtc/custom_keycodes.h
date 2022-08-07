
// Custom keycodes
#include "action.h"

bool process_custom_keycode(uint16_t keycode, keyrecord_t *record);

enum custom_keycodes {
    CK_EMAIL = SAFE_RANGE,
    CK_CLEARLINE,
};