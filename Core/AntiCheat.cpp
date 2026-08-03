// Core/AntiCheat.cpp
#include "AntiCheat.h"

Memory* AntiCheat::mem = nullptr;
bool AntiCheat::initialized = false;

void AntiCheat::init(Memory* memory) {
    mem = memory;
    initialized = true;
}

void AntiCheat::patch_function(uintptr_t address) {
    if (!address || !mem) return;
    unsigned char ret_bytes[] = {0xC0, 0x03, 0x5F, 0xD6};
    for (int i = 0; i < 4; i++) {
        mem->write<uint8_t>(address + i, ret_bytes[i]);
    }
}

void AntiCheat::patch_ban_report() {
    uintptr_t methods[] = {
        0x1513CA0, 0x1513E80, 0x15135EC, 0x1512330, 0x1513F28,
        0x1510D6C, 0x1513FD8, 0x1514088, 0x1514138, 0x1514268,
        0x1514398, 0x1514440, 0x15144F0, 0x1514598, 0x15146C8,
        0x1512200, 0x15147F8, 0x15148A0, 0x15149D0, 0x1514A78,
        0x1514BA8, 0x1514CD8, 0x1514E08, 0x1514EB0, 0x1514FE0,
        0x1515090, 0x1512C9C, 0x15151C0, 0x1515268, 0x1515318,
        0x150FDA8, 0x15153C0, 0x1513DD0, 0x15154F0, 0x1515598,
        0x1512DCC, 0x1515648, 0x150FED8, 0x1510E9C, 0x151371C,
        0x1515778, 0x15158A8, 0x1515950, 0x15159F8
    };
    for (int i = 0; i < sizeof(methods)/sizeof(uintptr_t); i++) {
        patch_function(Standoff2::CLIENT_BASE + methods[i]);
    }
}

void AntiCheat::bypass() {
    if (!mem || !initialized) return;
    patch_function(Standoff2::CLIENT_BASE + 0x1510F44);
    patch_function(Standoff2::CLIENT_BASE + 0x1510AE0);
    patch_function(Standoff2::CLIENT_BASE + 0x150ABCC);
    patch_ban_report();
    patch_function(Standoff2::CLIENT_BASE + 0x15118DC);
    patch_function(Standoff2::CLIENT_BASE + 0x15100E8);
}