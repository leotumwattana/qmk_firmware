#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
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
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _NUM,
    _NAV,
    _ADJUST,
    _SWAP
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAV,
  NUM,
  ADJUST,
  SWAP,

  BACKLIT,
  RGBRST,

  // Macros
  ARROW,
  PRNS,
  CBRS,
  BRCS,
  ESCS,

  // Dynamic Macro Support
  DYNAMIC_MACRO_RANGE,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#include "dynamic_macro.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LRST  RGBRST
#define LTOG  RGB_TOG
#define LHUI  RGB_HUI
#define LHUD  RGB_HUD
#define LSAI  RGB_SAI
#define LSAD  RGB_SAD
#define LVAI  RGB_VAI
#define LVAD  RGB_VAD
#define LSMOD RGB_MOD

#define SESC LSFT(KC_ESC)
#define SBSP RSFT(KC_BSPC)
#define NAVT LT(_NAV, KC_TAB)
#define NAVQ LT(_NAV, KC_QUOT)

// Xcode
#define XCNEXT LCTL(KC_GRV)
#define XCPREV LCTL(LSFT(KC_GRV))
#define XCJUMP LCTL(KC_6)
#define XSCOPE LCTL(LGUI(KC_E))
#define XCUR   LCTL(KC_LSFT)

#define ADJENT LT(_ADJUST, KC_ENT)

#define MOOM LSFT(KC_ENT)

// Dynamic Macros
#define REC1 DYN_REC_START1
#define REC2 DYN_REC_START2
#define PLAY1 DYN_MACRO_PLAY1
#define PLAY2 DYN_MACRO_PLAY2
#define STOP DYN_REC_STOP

// Hand Swap
#define NUM MO(_NUM)
#define SWAP TG(_SWAP)

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
      SESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    SBSP,  \
      NAVT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, NAVQ,   \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
      NUM,     NUM,     KC_LCTL, KC_LALT, KC_LGUI, LOWER,  SESC,     KC_SPC,  RAISE,   KC_LCTL, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
  ),

  [_LOWER] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      KC_DEL,  ARROW,   PRNS,    CBRS,    BRCS,    ESCS,                      KC_COLN, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, KC_Z,    _______, _______, _______, _______,                   _______, KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   _______, \
      _______, _______, _______, _______, _______, _______, _______,  KC_EQL, KC_ENT,  _______, _______, _______, _______, _______  \
  ),

  [_RAISE] = LAYOUT( \
      KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE, \
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_BSLS, \
      _______, KC_PLUS, KC_MINS, KC_ASTR, _______, _______,                   _______, KC_PLUS, KC_MINS, KC_UNDS, KC_SLSH, _______, \
      _______, _______, _______, _______, _______, KC_ENT,  KC_DEL , _______, _______, _______, _______, _______, _______, _______  \
  ),

  [_NAV] =  LAYOUT( \
      _______, MOOM,    _______, _______, _______, _______,                   S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), _______, \
      _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V),  S(KC_B),                  XSCOPE,  XCPREV,  XCNEXT,  XCJUMP,  _______, _______, \
      _______, _______, _______, _______, XCUR,    KC_SPC,  _______, _______, KC_ENT, _______, _______,  _______, _______, _______  \
  ),

  [_NUM] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   KC_LPRN, KC_7,    KC_8,    KC_9,    KC_RPRN, KC_BSPC, \
      SWAP,    S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),                   KC_MINS, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_ENT , \
      _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B),                   KC_SLSH, KC_1,    KC_2,    KC_3,    KC_ASTR, KC_COMM, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  _______, _______, _______  \
  ),

  [_ADJUST] =  LAYOUT( \
      _______, RESET,   LRST,    _______, _______, _______,                   _______, _______, _______, _______, _______, KC_MUTE, \
      _______, LTOG,    LHUI,    LSAI,    LVAI,    _______,                   _______, PLAY1,   PLAY2,   _______, _______, KC_VOLU, \
      _______, LSMOD,   LHUD,    LSAD,    LVAD,    _______,                   _______, REC1,    REC2,    _______, _______, KC_VOLD, \
      _______, _______, _______, _______, _______, _______, _______, _______, STOP,    _______, _______, _______, _______, _______  \
  ),

  [_SWAP] =  LAYOUT( \
      SBSP,    KC_Y,    KC_O,    KC_I,    KC_U,    KC_Y,                      _______, _______, _______, _______, _______, _______, \
      ADJENT,  KC_SCLN, KC_L,    KC_K,    KC_J,    KC_H,                      _______, _______, _______, _______, _______, _______, \
      SWAP,    KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,                      _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, RAISE,   KC_SPC,  _______, _______, _______, _______, _______, _______, _______, _______  \
  ),

};
#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Dynamic Macro
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
