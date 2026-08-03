// UI/Config.h
#pragma once

struct Config {
    static bool esp_enabled;
    static bool silent_aim_enabled;
    static bool no_recoil;
    static bool menu_visible;
    
    static void toggle_esp() { esp_enabled = !esp_enabled; }
    static void toggle_silent_aim() { silent_aim_enabled = !silent_aim_enabled; }
    static void toggle_no_recoil() { no_recoil = !no_recoil; }
};