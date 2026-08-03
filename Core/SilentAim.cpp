// Core/SilentAim.cpp
#include "SilentAim.h"
#include "Standoff2Offsets.h"

Memory* SilentAim::mem = nullptr;

void SilentAim::init(Memory* memory) { mem = memory; }

Vector3 SilentAim::calculate_angle(Vector3 source, Vector3 target) {
    Vector3 delta = {target.x - source.x, target.y - source.y, target.z - source.z};
    float length = sqrtf(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
    if (length < 0.001f) return Vector3(0,0,0);
    Vector3 angles;
    angles.x = asinf(delta.z / length) * (180.0f / M_PI);
    angles.y = atan2f(delta.y, delta.x) * (180.0f / M_PI);
    angles.z = 0;
    return angles;
}

Vector3 SilentAim::clamp_angles(Vector3 angles) {
    if (angles.x > 89.0f) angles.x = 89.0f;
    if (angles.x < -89.0f) angles.x = -89.0f;
    if (angles.y > 180.0f) angles.y = -180.0f;
    if (angles.y < -180.0f) angles.y = 180.0f;
    return angles;
}

Vector3 SilentAim::get_best_target() {
    Vector3 best_target(0,0,0);
    return best_target;
}

void SilentAim::apply_aim() {
    if (!Config::silent_aim_enabled) return;
    Vector3 target = get_best_target();
    if (target.x == 0 && target.y == 0 && target.z == 0) return;
    
    uintptr_t gameController = mem->read_ptr(Standoff2::CLIENT_BASE + Standoff2::OFFSET_GAME_CONTROLLER_INSTANCE);
    if (!gameController) return;
    uintptr_t local = mem->read_ptr(gameController + Standoff2::OFFSET_PLAYER_CONTROLLER);
    if (!local) return;
    uintptr_t aim = mem->read_ptr(local + Standoff2::OFFSET_AIM_CONTROLLER);
    if (!aim) return;
    
    Vector3 aim_angle = clamp_angles(calculate_angle(Vector3(0,0,0), target));
    mem->write_float(aim + Standoff2::OFFSET_AIM_CMD, aim_angle.x);
    mem->write_float(aim + Standoff2::OFFSET_AIM_CMD + 4, aim_angle.y);
}