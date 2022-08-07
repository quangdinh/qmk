#include QMK_KEYBOARD_H
#include "config.h"
#include "split_util.h"
#include "oled_handler.h"
#include "split_handler.h"
#include "custom_keycodes.h"
#include "states_handler.h"
#include "layers.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_matrix_animation(record);
    return process_custom_keycode(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_current_layer(get_highest_layer(state|default_layer_state));
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t layer = layer_state_cmp(state, LAYER_COLEMAK) ? LAYER_COLEMAK : LAYER_BASE;
    set_current_default_layer(layer);
    return state;
}

static uint32_t animated_frame = 0;

void housekeeping_task_user(void) {
    static bool need_sync = false;
    if (is_keyboard_left()) {
        bool changes = tick();
        need_sync |= changes;
    }

    if ((timer_elapsed32(last_transmission()) > SPLIT_SYNC_INTERVAL) 
          && need_sync
          && is_transport_connected()) {
        
        if (split_sync()) {
            need_sync = false;
        }
    }

    // If no transport, stop any ongoing animation
    if (!is_transport_connected()) {
        oled_stop_animate_transmission();
        return;
    }

    // // Handle transmit animation timing
    if (timer_elapsed32(last_transmission()) > SYNC_ANIMATION_TIME) {
        oled_stop_animate_transmission();
    } else if (timer_elapsed32(animated_frame) > SYNC_ANIMATION_SPEED) {
        animated_frame = timer_read32();
        oled_animate_transmission();
    }
}

void keyboard_post_init_user(void) {
    register_rpc();
}