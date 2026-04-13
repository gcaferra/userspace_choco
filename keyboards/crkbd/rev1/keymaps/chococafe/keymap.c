#include QMK_KEYBOARD_H

// ─── Home row mod-taps (QWERTY) ───────────────────────────────────────────────
// Left hand:  A  S  D  F  G
#define ALT_S  ALT_T(KC_S)
#define SFT_D  SFT_T(KC_D)
#define CTL_F  CTL_T(KC_F)
#define CMD_G  LCMD_T(KC_G)

// Right hand: H  J  K  L  ;
#define CMD_H  RCMD_T(KC_H)
#define CTL_J  CTL_T(KC_J)
#define SFT_K  SFT_T(KC_K)
#define ALT_L  ALT_T(KC_L)

// ─── Thumb layer-taps ─────────────────────────────────────────────────────────
#define SPC_L1 LT(1, KC_SPC)
#define ENT_L4 LT(4, KC_ENT)

// ─── Custom keycodes ──────────────────────────────────────────────────────────
enum custom_keycodes {
    KC_ARROW = SAFE_RANGE,  // =>
    KC_NEQL,                // !=
    KC_DEQL,                // ==
    KC_NCOAL,               // ??
    KC_RARR,                // ->
    KC_SUDORM,              // sudo !!
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_ARROW:  SEND_STRING("=>"); return false;
            case KC_NEQL:   SEND_STRING("!="); return false;
            case KC_DEQL:   SEND_STRING("=="); return false;
            case KC_NCOAL:  SEND_STRING("??"); return false;
            case KC_RARR:   SEND_STRING("->"); return false;
            case KC_SUDORM: SEND_STRING("sudo !!"); return false;
        }
    }
    return true;
}

// ─── Combos ───────────────────────────────────────────────────────────────────
// All combos use plain (non-mod-tap) keys only — mod-tap keys intercept
// keypresses before the combo engine sees them.
//
//  Y + U  =>  =>    LINQ lambda    right top row, pinky+ring
//  W + E  =>  !=    not-equal      left top row,  ring+middle
//  Q + W  =>  ==    equality       left top row,  pinky+ring
//  U + O  =>  ??    null coalesce  right top row, ring+middle (skip index)
//  M + ,  =>  ->    bash arrow     right bottom row

const uint16_t PROGMEM arrow_combo[] = {KC_Y, KC_U,    COMBO_END};
const uint16_t PROGMEM neql_combo[]  = {KC_W, KC_E,    COMBO_END};
const uint16_t PROGMEM deql_combo[]  = {KC_Q, KC_W,    COMBO_END};
const uint16_t PROGMEM ncoal_combo[] = {KC_U, KC_O,    COMBO_END};
const uint16_t PROGMEM rarr_combo[]  = {KC_M, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    COMBO(arrow_combo, KC_ARROW),
    COMBO(neql_combo,  KC_NEQL),
    COMBO(deql_combo,  KC_DEQL),
    COMBO(ncoal_combo, KC_NCOAL),
    COMBO(rarr_combo,  KC_RARR),
};

// ─── Per-key tapping term ─────────────────────────────────────────────────────
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_S:  return 220;   // left ring
        case ALT_L:  return 220;   // right ring
        case SFT_D:  return 200;   // left middle
        case SFT_K:  return 200;   // right middle
        case CTL_F:  return 180;   // left index
        case CTL_J:  return 180;   // right index
        case CMD_G:  return 210;   // left index stretch col
        case CMD_H:  return 210;   // right index stretch col
        default:     return TAPPING_TERM;
    }
}

// ─── Keymap ───────────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 0 — QWERTY base                                                  ║
// ║                                                                          ║
// ║   Q   W   E   R   T       Y   U   I   O   P                             ║
// ║   A  S⎇  D⇧  F⌃  G⌘     H⌘  J⌃  K⇧  L⎇  ;                             ║
// ║   Z   X   C   V   B       N   M   ,   .   /                             ║
// ║           [3][2][SPC/1]  [ENT/4][5][6]                                  ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[0] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_A,    ALT_S,   SFT_D,   CTL_F,   CMD_G,                          CMD_H,   CTL_J,   SFT_K,   ALT_L,  KC_SCLN,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          MO(3),   MO(2),  SPC_L1,       ENT_L4,  MO(5),   MO(6)
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 1 — Navigation  (Space hold)                                     ║
// ║                                                                          ║
// ║  ESC  TAB A-Tab C-Tab S-Tab   DEL HOME  UP  END  BSPC                   ║
// ║ GUI  ALT  SFT   CTL    _      TAB  ←    ↓   →    '                      ║
// ║   _   _    _     _   MENU      _  PGUP   _  PGDN  \                     ║
// ║                                                                          ║
// ║  Top left: plain TAB + all tab-navigation variants in one row            ║
// ║   TAB      = plain tab (forward indent / completion)                     ║
// ║   Alt+Tab  = switch window (hold Alt, keep tapping Tab to cycle)         ║
// ║   Ctrl+Tab = switch editor tab in Rider / browser tab                    ║
// ║   Shift+Tab= reverse tab / back-indent                                   ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[1] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
  //  ESC    TAB     A-Tab       C-Tab       S-Tab                            DEL    HOME     UP     END    BSPC
      KC_ESC, KC_TAB, A(KC_TAB), C(KC_TAB), S(KC_TAB),                      KC_DEL, KC_HOME, KC_UP, KC_END, KC_BSPC,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______,KC_TAB, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, KC_MENU,                        KC_NO,   KC_PGUP, KC_NO,   KC_PGDN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 2 — Numbers  (inner left thumb)                                  ║
// ║                                                                          ║
// ║   _   _   _  DEL BSPC      1   2   3   4   5                            ║
// ║  GUI ALT SFT CTL   _       6   7   8   9   0                            ║
// ║   _   _   _   _   _        _   _   _   _   _                            ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[2] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
      _______, _______, _______, KC_DEL,  KC_BSPC,                        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, KC_6, KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 3 — F-keys  (outer left thumb)                                   ║
// ║                                                                          ║
// ║   _   _   _   _   _      F1  F2  F3  F4  F5                             ║
// ║  GUI ALT SFT CTL   _     F6  F7  F8  F9  F10                            ║
// ║   _   _   _   _   _     F11 F12 F13 F14 F15                             ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[3] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
      _______, _______, _______, _______, _______,                        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, KC_F6, KC_F7,  KC_F8,   KC_F9,   KC_F10,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,                        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 4 — System + Rider IntelliJ keymap  (Enter hold)                 ║
// ║                                                                          ║
// ║  Verified from JetBrains Rider 'IntelliJ' keymap PDF                    ║
// ║                                                                          ║
// ║  Left hand — universal + terminal                                        ║
// ║   ESC   C-a   C-s   C-f   C-l                                           ║
// ║   TAB   PSCR  C-r   C-y    _                                            ║
// ║   C-c   C-z   C-d   C-x   C-v                                           ║
// ║                                                                          ║
// ║  Right hand — Rider IntelliJ actions                                     ║
// ║   F9   C-F2   F8    F7   BSPC                                            ║
// ║  C-F9  A-F7  S-F6  A-Ent  _                                             ║
// ║  C-;   C-F8  C-S   INS   UG                                             ║
// ║                                                                          ║
// ║  Key (all verified from IntelliJ keymap PDF):                            ║
// ║   F9        = Resume program / continue debug                            ║
// ║   C-F2      = Stop                                                       ║
// ║   F8        = Step over                                                  ║
// ║   F7        = Step into                                                  ║
// ║   C-F9      = Build  (also: toggle/enable breakpoint context-dep.)       ║
// ║   A-F7      = Find usages                                                ║
// ║   S-F6      = Rename                                                     ║
// ║   A-Ent     = Show context actions / quick fix                           ║
// ║   C-;       = Unit test prefix (Ctrl+;) — follow with R to run          ║
// ║   C-F8      = Toggle line breakpoint                                     ║
// ║   C-S       = Save all                                                   ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[4] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
  //  ESC    C-a      C-s      C-f      C-l            F9      C-F2     F8       F7       BSPC
      KC_ESC, C(KC_A), C(KC_S), C(KC_F), C(KC_L),      KC_F9,  C(KC_F2),KC_F8,   KC_F7,   KC_BSPC,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
  //  PSCR   _        C-r      C-y       _           C-F9    A-F7    S-F6    A-Ent    C-;
      KC_PSCR, _______, C(KC_R), C(KC_Y), _______,   C(KC_F9),A(KC_F7),S(KC_F6),A(KC_ENT),C(KC_SCLN),
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
  //  C-c    C-z      C-d      C-x      C-v           C-F8    INS      _        _       UG
      C(KC_C),C(KC_Z), C(KC_D), C(KC_X), C(KC_V),   C(KC_F8), KC_INS, _______, _______, UG_TOGG,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 5 — Brackets + assignment  (right inner thumb)                   ║
// ║                                                                          ║
// ║   ~   `   [   ]   @        _   _   _   _  BSPC                          ║
// ║   (   )   =   !   "        _  RC  RS  RA  RG                            ║
// ║   {   }   \   '   #        _   _   _   _   _                            ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[5] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
      KC_TILD, KC_GRV,  KC_LBRC, KC_RBRC, KC_AT,                         _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_LPRN, KC_RPRN, KC_EQL,  KC_EXLM, KC_DQUO,                       _______, KC_RCTL, KC_RSFT, KC_RALT, KC_RCMD,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_LCBR, KC_RCBR, KC_BSLS, KC_QUOT, KC_HASH,                       _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  Layer 6 — Operators + LINQ  (right outer thumb)                        ║
// ║                                                                          ║
// ║   %   *   /   +   -        _   _   _   _  BSPC                          ║
// ║   |   &   >   <   ?        _  RC  RS  RA  RG                            ║
// ║   ^   $   .   ,   ;        _   _   _   _  UG                            ║
// ╚══════════════════════════════════════════════════════════════════════════╝
[6] = LAYOUT_split_3x5_3(
  //|----------------------------------------------|                    |--------------------------------------------|
      KC_PERC, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS,                       _______, _______, _______, _______, KC_BSPC,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_PIPE, KC_AMPR, KC_GT,   KC_LT,   KC_QUES,                       _______, KC_RCTL, KC_RSFT, KC_RALT, KC_RCMD,
  //|--------+--------+--------+--------+--------+-|                    |--------+--------+--------+--------+--------|
      KC_CIRC, KC_DLR,  KC_DOT,  KC_COMM, KC_SCLN,                       _______, _______, _______, _______, UG_TOGG,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
),

};
