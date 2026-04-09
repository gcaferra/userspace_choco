#pragma once

// ─── Combo ────────────────────────────────────────────────────────────────────
#define COMBO_COUNT 5
#define COMBO_TERM 40           // ms window; tune 25–70 to taste

// ─── Mod-tap ──────────────────────────────────────────────────────────────────
#define TAPPING_TERM 200        // base; overridden per-key in get_tapping_term()
#define TAPPING_TERM_PER_KEY    // enables the get_tapping_term() override

// QUICK_TAP_TERM: tapping a mod-tap twice quickly repeats the tap keycode
// instead of producing a hold. Prevents double-letter issues (e.g. "ss", "nn").
#define QUICK_TAP_TERM 120

// ─── One-shot mods ────────────────────────────────────────────────────────────
#define ONESHOT_TIMEOUT 2000    // ms before an unconsumed one-shot mod expires