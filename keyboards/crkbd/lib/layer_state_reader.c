
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_NUM 8
#define L_NAV 16
#define L_ADJUST 32
#define L_SWAP 64
#define L_SWAP2 72
#define L_ADJUST_TRI 65560

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case L_NUM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NumPad");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Navigation");
    break;
  case L_ADJUST:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  case L_SWAP:
  case L_SWAP2:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Swap");
    break;
  // case L_ADJUST_TRI:
  //   snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
  //   break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}


