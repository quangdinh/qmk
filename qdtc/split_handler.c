#include QMK_KEYBOARD_H

#include "split_handler.h"
#include "transactions.h"
#include "oled_handler.h"
#include "utils.h"
#include "states_handler.h"

typedef struct {
    uint8_t layer;
    bool combo_enabled;
    uint8_t rgb_mode;
    uint8_t layout;
} transport_msg_sync;

static uint32_t last_transmit_time = 0;

void user_split_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    bool *result = (bool*)out_data;
    *result = true;
    last_transmit_time = timer_read32();
    const transport_msg_sync* sync = (const transport_msg_sync*)in_data;
    oled_render_layout(sync->layout);
    oled_render_layer(sync->layer);
    oled_render_combo(sync->combo_enabled);
    oled_render_rgb_mode(sync->rgb_mode);
}

void register_rpc(void) {
    transaction_register_rpc(USER_SPLIT_SYNC, user_split_sync);
}

bool split_sync(void) {
    const transport_msg_sync state = {
        get_current_layer(),
        is_combo_enabled(),
        rgb_matrix_is_enabled() ? rgb_matrix_get_mode() : 0,
        get_current_default_layer()
    };
    bool success = false;
    transaction_rpc_exec(USER_SPLIT_SYNC, sizeof(state), &state, sizeof(success), &success);
    if (!success) {
        return false;
    }
    last_transmit_time = timer_read32();
    return true;
}

uint32_t last_transmission(void) {
    return last_transmit_time;
}