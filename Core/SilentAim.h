// Core/SilentAim.h
#pragma once
#include "ESP.h"
#include "Memory.h"
#include "Config.h"
#include <cmath>

class SilentAim {
private:
    static Memory* mem;
    static Vector3 calculate_angle(Vector3 source, Vector3 target);
    static Vector3 clamp_angles(Vector3 angles);
public:
    static void init(Memory* memory);
    static Vector3 get_best_target();
    static void apply_aim();
};