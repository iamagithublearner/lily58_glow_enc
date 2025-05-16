#include QMK_KEYBOARD_H


enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_PSCR,   KC_BRID,    KC_PSCR,    KC_BRIU,    KC_MNXT,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_VOLU,  KC_COPY,   MS_BTN1,    MS_UP,    MS_BTN2,    KC_MPLY,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_MUTE,  KC_CUT,   MS_LEFT,    MS_DOWN,    MS_RGHT,    KC_MPRV,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_VOLD,  KC_F16,   KC_F13,    KC_F14,    KC_F15,    KC_PSTE,   KC_LBRC,         KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        TO(0), TO(1), TO(2), MO(0),                                KC_ENT, MO(_RAISE), KC_BSPC, KC_RGUI
),

[_LOWER] = LAYOUT(
  KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_MNXT,                   _______, _______, _______,_______, _______, _______,
  KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_MPLY,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_LSFT,   KC_A,   KC_S,   KC_D,   KC_F,  KC_MPRV,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_M, _______,          _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, _______,  _______, _______, _______
),

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
)
};



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [1] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU)  },
    [2] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT) },
};
#endif


#ifdef QUANTUM_PAINTER_ENABLE
#    include "qp.h"
#    include "eyes.qgf.h"

static painter_device_t       display;
static painter_image_handle_t my_image;
#endif // QUANTUM_PAINTER_ENABLE

void keyboard_post_init_user(void) {
#ifdef QUANTUM_PAINTER_ENABLE
    display = qp_sh1106_make_i2c_device(128, 32, 0x3C); // Example values for width, height, and address
    qp_init(display, QP_ROTATION_90);
    qp_clear(display);
    my_image = qp_load_image_mem(gfx_eyes);
    qp_animate(display, 0, 0, my_image);
    qp_flush(display);
#endif // QUANTUM_PAINTER_ENABLE
}
