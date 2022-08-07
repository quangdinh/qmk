#include "action.h"

void oled_task_user_once_left(void);
void oled_task_user_once_right(void);

void oled_render_logo(void);
void oled_render_layout(uint8_t layout);
void oled_render_layer(uint8_t layer);
void oled_render_rgb_mode(uint8_t mode);
void oled_render_wpm(uint8_t wpm);
void oled_render_combo(bool is_enabled);

void process_record_matrix_animation(keyrecord_t *record);
void oled_render_connection_matrix(bool connected);

void oled_animate_transmission(void);
void oled_stop_animate_transmission(void);