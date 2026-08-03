// Core/ESP.cpp
#include "ESP.h"
#include <cstdio>

Memory* ESP::mem = nullptr;
Vector3 ESP::local_position;
int ESP::local_team = 0;
std::vector<Player> ESP::players;

void ESP::init(Memory* memory) { mem = memory; }

bool ESP::world_to_screen(Vector3 world, Vector2& screen) {
    screen.x = 100;
    screen.y = 100;
    screen.visible = true;
    return true;
}

void ESP::draw_box(Vector2 top, Vector2 bottom, int color) {}
void ESP::draw_health_bar(Player& p) {}
void ESP::draw_name(Player& p) {}
void ESP::draw_distance(Player& p) {}
void ESP::draw_head_circle(Player& p) {}

void ESP::update_players() {
    players.clear();
    uintptr_t gameController = mem->read_ptr(Standoff2::CLIENT_BASE + Standoff2::OFFSET_GAME_CONTROLLER_INSTANCE);
    if (!gameController) return;
    uintptr_t local = mem->read_ptr(gameController + Standoff2::OFFSET_PLAYER_CONTROLLER);
    if (!local) return;
    local_team = mem->read_int(local + Standoff2::OFFSET_TEAM);
    
    Player p;
    p.address = local;
    p.team = 1;
    p.health = 100;
    p.name[0] = 'T';
    p.name[1] = 'e';
    p.name[2] = 's';
    p.name[3] = 't';
    p.name[4] = '\0';
    players.push_back(p);
}

void ESP::render() {
    if (!Config::esp_enabled) return;
    update_players();
}