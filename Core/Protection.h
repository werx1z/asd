// Core/Protection.h
#pragma once

class Protection {
public:
    static void init();
    static void anti_debug();
    static void hide_memory_access();
};