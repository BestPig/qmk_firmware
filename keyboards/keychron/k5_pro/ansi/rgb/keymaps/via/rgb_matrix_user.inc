RGB_MATRIX_EFFECT(only_configured_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "keymap.h"

// e.g: A simple effect, self-contained within a single method

extern bool autocorrect_enabled;
extern bool autocorrect_enabled_accent;
extern bool anti_idle_enabled;
extern bool game_mode_enabled;
extern bool prog_key_enabled;
extern unicode_config_t unicode_config;

static bool only_configured_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t layer = get_highest_layer(layer_state);
    
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index <= led_max && index != NO_LED) {
                uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});

                if (keycode == K_AUT_COR) {
                    if (autocorrect_enabled) {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_RED);
                    }
                }
                else if (keycode == K_AUT_COR_ACCENT) {
                    if (autocorrect_enabled_accent) {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_RED);
                    }
                }
                else if (keycode == K_ANTI_IDLE) {
                    if (anti_idle_enabled) {
                        rgb_matrix_set_color(index, RGB_YELLOW);
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                }
                else if (keycode == K_GAME_MODE) {
                    if (game_mode_enabled) {
                        rgb_matrix_set_color(index, RGB_YELLOW);
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                }
                else if (keycode == UC_LINX) {
                    if (unicode_config.input_mode == UNICODE_MODE_LINUX) {
                        if (prog_key_enabled) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        }
                        else {
                            rgb_matrix_set_color(index, RGB_YELLOW);
                        }
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                }
                else if (keycode == UC_WINC) {
                    if (unicode_config.input_mode == UNICODE_MODE_WINCOMPOSE) {
                        if (prog_key_enabled) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        }
                        else {
                            rgb_matrix_set_color(index, RGB_YELLOW);
                        }
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                }
                else if (keycode == UC_MAC) {
                    if (unicode_config.input_mode == UNICODE_MODE_MACOS) {
                        if (prog_key_enabled) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        }
                        else {
                            rgb_matrix_set_color(index, RGB_YELLOW);
                        }
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_GREEN);
                    }
                }
                else if (keycode > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
                else {
                    if (autocorrect_enabled) {
                        rgb_matrix_set_color(index, RGB_RED);
                    }
                    else {
                        rgb_matrix_set_color(index, RGB_BLACK);
                    }
                }
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS