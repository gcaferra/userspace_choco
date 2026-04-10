#pragma once

// ─── Combo ────────────────────────────────────────────────────────────────────
#define COMBO_COUNT 5
#define COMBO_TERM 50           // ms window; raise to 70 if still missing, lower
                                // to 35 if you get accidental triggers in typing

// Required when using combos alongside mod-taps on the same layer.
// Makes the combo engine evaluate on key release rather than key press,
// preventing mod-tap hold detection from swallowing combo keypresses.
#define COMBO_PROCESS_KEY_RELEASE

// ─── Mod-tap ──────────────────────────────────────────────────────────────────
#define TAPPING_TERM 200        // base; overridden per-key in get_tapping_term()
#define TAPPING_TERM_PER_KEY    // enables the get_tapping_term() override

// QUICK_TAP_TERM: tapping a mod-tap twice quickly repeats the tap keycode
// instead of producing a hold. Prevents double-letter issues (e.g. "ss", "nn").
#define QUICK_TAP_TERM 120

// ─── One-shot mods ────────────────────────────────────────────────────────────
#define ONESHOT_TIMEOUT 2000    // ms before an unconsumed one-shot mod expires
