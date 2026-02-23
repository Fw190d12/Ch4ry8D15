#include QMK_KEYBOARD_H


/**************************
 * TAP DANCE DECLARATIONS *
 **************************/
enum {
    TD_ESC_TILDA,
    TD_SLSH_BSLS,
    TD_CTRL_MO3
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

