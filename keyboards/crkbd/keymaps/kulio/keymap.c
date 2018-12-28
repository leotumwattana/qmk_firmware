#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _NUM 3
#define _NAV 4
#define _ADJUST 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAV,
  NUM,
  ADJUST,
  BACKLIT,
  RGBRST,

  // Macros
  ARROW,
  PRNS,
  CBRS,
  BRCS,
  ESCS,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_SESC LSFT_T(KC_ESC)
#define KC_SBSPC LSFT_T(KC_BSPC)
#define KC_NAVT LT(_NAV, KC_TAB)
#define KC_NAVQ LT(_NAV, KC_QUOT)
#define KC_SENT RSFT_T(KC_ENT)

#define KC_CTLZ CTL_T(KC_Z)
#define KC_ALTX ALT_T(KC_X)
#define KC_CTLSH CTL_T(KC_SLSH)
#define KC_ALTDT ALT_T(KC_DOT)

#define KC_NUM TT(_NUM)
#define KC_XCNEXT LCTL(KC_GRV)
#define KC_XCPREV LCTL(LSFT(KC_GRV))
#define KC_XCJUMP LCTL(KC_6)

#define KC_MOOM LSFT(KC_ENT)

// Macros
#define KC_ARROW ARROW
#define KC_PRNS PRNS
#define KC_CBRS CBRS
#define KC_BRCS BRCS
#define KC_ESCS ESCS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  //,-----------d------------------------------.                ,-----------------------------------------.
      SESC ,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P, SBSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      NAVT ,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  NAVQ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       NUM ,  CTLZ,  ALTX,     C,     V,     B,                      N,     M,  COMM, ALTDT, CTLSH,  SENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LGUI, LOWER,   SESC,      SPC, RAISE, RGUI \
                              //`--------------------'  `--------------------'
  ),


  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      GRV  ,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      DEL  , ARROW, PRNS , CBRS , BRCS , ESCS ,                  COLN , LPRN , RPRN , LBRC , RBRC , BSLS ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, LCBR , RCBR , LT   , GT   , _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    EQUAL, ENT  , _____ \
                              //`--------------------'  `--------------------'
  ),


  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      TILD,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  PIPE ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, EXLM , AT   , HASH , DLR  , PERC ,                  CIRC , AMPR , ASTR , MINS , EQUAL, BSLS ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, PLUS , MINS , ASTR , _____, _____,                  _____, PLUS , MINS , UNDS , SLSH , _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, ENT  ,  DEL ,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_NAV] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____,TAB   ,ENT   , _____, _____,                 _____, XCPREV,XCNEXT,XCJUMP, _____,  MUTE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, MOOM , _____,LGUI  ,LALT  ,RSFT  ,                 LEFT  ,DOWN  ,UP    ,RGHT  , _____,  VOLU,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____,  VOLD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 _____, _____, SPC   ,   ENT   , _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_NUM] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  RST , LRST , _____, _____, _____,                  LPRN ,     7,     8,     9, RPRN , BSPC ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, LTOG , LHUI , LSAI , LVAI , _____,                  MINS ,     4,     5,     6, PLUS , ENT  ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, LSMOD, LHUD , LSAD , LVAD, _____,                  SLSH ,     1,     2,     3, ASTR , COMM ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 _____, _____, _____ ,   _____ ,     0,  DOT  \
                              //`--------------------'  `--------------------'
  ),
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_rgb_info(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    // matrix_write_ln(matrix, read_keylog());
    // matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write_ln(matrix, read_host_led_state());
    matrix_write_ln(matrix, read_rgb_info());
    matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
// #ifdef SSD1306OLED
    // set_keylog(keycode, record);
// #endif
    set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case ARROW:
      if (record->event.pressed) {
        // when keycode ARROW is pressed
        SEND_STRING("->");
      }
      return false;
      break;
    case PRNS:
      if (record->event.pressed) {
        // when keycode PRNS is pressed
        SEND_STRING("()");
        SEND_STRING(SS_TAP(X_LEFT));
      }
      return false;
      break;
    case CBRS:
      if (record->event.pressed) {
        // when keycode CBRS is pressed
        SEND_STRING("{}");
        SEND_STRING(SS_TAP(X_LEFT));
        // SEND_STRING("\n");
      }
      return false;
      break;
    case BRCS:
      if (record->event.pressed) {
        // when keycode BRCS is pressed
        SEND_STRING("[]");
        SEND_STRING(SS_TAP(X_LEFT));
      }
      return false;
      break;
    case ESCS:
      if (record->event.pressed) {
        // when keycode ESCS is pressed
        SEND_STRING("\\()");
        SEND_STRING(SS_TAP(X_LEFT));
      }
      return false;
      break;
  }
  return true;
}

