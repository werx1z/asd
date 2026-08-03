// Standoff2Offsets.h
#pragma once
#include <stdint.h>

namespace Standoff2 {
    static uintptr_t CLIENT_BASE = 0x0;
    
    // GameController
    static const uintptr_t OFFSET_GAME_CONTROLLER_INSTANCE = 0x10;
    static const uintptr_t OFFSET_PLAYER_CONTROLLER = 0x1D0;
    
    // AntiCheat
    static const uintptr_t OFFSET_REPORTS = 0x20;
    static const uintptr_t OFFSET_LOCAL_REPORTS = 0x28;
    static const uintptr_t OFFSET_ANTI_CHEATS = 0x30;
    static const uintptr_t OFFSET_ALREADY_BANNED = 0x38;
    static const uintptr_t OFFSET_PLAYER_BANNED_HANDLER = 0x40;
    
    static const uintptr_t METHOD_REPORT_VIA_SERVER = 0x1510AE0;
    static const uintptr_t METHOD_BAN_ME = 0x1510F44;
    static const uintptr_t METHOD_REPORT = 0x150ABCC;
    static const uintptr_t METHOD_ON_INSTANTIATE = 0x15118DC;
    static const uintptr_t METHOD_ON_RETURN_TO_POOL = 0x15100E8;
    
    // PlayerController
    static const uintptr_t OFFSET_AIM_CONTROLLER = 0x88;
    static const uintptr_t OFFSET_WEAPONRY_CONTROLLER = 0x90;
    static const uintptr_t OFFSET_MOVEMENT_CONTROLLER = 0xA0;
    static const uintptr_t OFFSET_BIPED_MAP = 0xC8;
    static const uintptr_t OFFSET_TEAM = 0x49;
    static const uintptr_t OFFSET_TRANSFORM = 0x68;
    
    static const uintptr_t METHOD_GET_HEALTH = 0xDE0020;
    static const uintptr_t METHOD_GET_TEAM = 0x1DE19F0;
    static const uintptr_t METHOD_GET_ARMOR = 0x1DDF69C;
    static const uintptr_t METHOD_IS_DEATH = 0x1DE0C1C;
    
    // AimController
    static const uintptr_t OFFSET_SENSITIVITY_X = 0x50;
    static const uintptr_t OFFSET_SENSITIVITY_Y = 0x54;
    static const uintptr_t OFFSET_AIM_CMD = 0x100;
    static const uintptr_t OFFSET_CUR_SPINE_AIM_ANGLE = 0x110;
    static const uintptr_t OFFSET_AIMING_DATA = 0x90;
    static const uintptr_t OFFSET_PLAYER_CONTROLLER_IN_AIM = 0x58;
    
    static const uintptr_t METHOD_SET_ROTATION = 0x1EE1B7C;
    static const uintptr_t METHOD_GET_ROTATION = 0x1EE3444;
    
    // BipedMap
    static const uintptr_t OFFSET_HEAD = 0x18;
    static const uintptr_t OFFSET_SPINE1 = 0x28;
    static const uintptr_t OFFSET_LEFT_UPPERARM = 0x40;
    static const uintptr_t OFFSET_RIGHT_UPPERARM = 0x60;
    static const uintptr_t OFFSET_HIP = 0x78;
}