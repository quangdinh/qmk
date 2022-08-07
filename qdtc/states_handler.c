#include QMK_KEYBOARD_H
#include "layers.h"
#include "states_handler.h"
#include "split_handler.h"
#include "config.h"
#include "split_util.h"
#include "oled_handler.h"

uint8_t current_layer = LAYER_BASE;
uint8_t current_default_layer = LAYER_BASE;

bool tick(void) {
    static uint8_t p_wpm = 0;
    static bool p_combo_enabled = false;
    static uint8_t p_rbg_mode = 100;
    static bool p_split_connected = false;
    static uint8_t p_layer = LAYER_BASE;
    static uint8_t p_layout = LAYER_BASE;

    // Should sync states
    bool should_sync = false;

    // Layer
    if (p_layer != current_layer) {
        should_sync = true;
        p_layer = current_layer;
        oled_render_layer(p_layer);
    }

    // Layout
    if (p_layout != current_default_layer) {
        should_sync = true;
        p_layout = current_default_layer;
        oled_render_layout(p_layout);
    }

    // WPM
    if (p_wpm != get_current_wpm()) {
        p_wpm = get_current_wpm();
        oled_render_wpm(p_wpm);
    }

    // Combo
    if (p_combo_enabled != is_combo_enabled()) {
        should_sync = true;
        p_combo_enabled = is_combo_enabled();
        oled_render_combo(p_combo_enabled);
    }

    // RGB Mode
    const uint8_t current_mode = rgb_matrix_is_enabled() ? rgb_matrix_get_mode() : 0;
    if (p_rbg_mode != current_mode) {
        should_sync = true;
        p_rbg_mode = current_mode;
        oled_render_rgb_mode(p_rbg_mode);
    }

    // Split connection
    if (p_split_connected != is_transport_connected()) {
        should_sync = true;
        p_split_connected = is_transport_connected();
        oled_render_connection_matrix(p_split_connected);
    }

    return should_sync;
}

void set_current_default_layer(uint8_t layer) {
    current_default_layer = layer;
}

uint8_t get_current_default_layer(void) {
    return current_default_layer;
}

void set_current_layer(uint8_t layer) {
    current_layer = layer;
}

uint8_t get_current_layer(void) {
    return current_layer;
}