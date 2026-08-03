// Core/AntiCheat.h
#pragma once
#include "Memory.h"
#include "Standoff2Offsets.h"

class AntiCheat {
private:
    static Memory* mem;
    static bool initialized;
    static void patch_function(uintptr_t address);
    static void patch_ban_report();
public:
    static void init(Memory* memory);
    static void bypass();
};