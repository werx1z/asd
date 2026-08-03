// Core/Protection.cpp
#include "Protection.h"
#include <sys/ptrace.h>

void Protection::init() {
    anti_debug();
    hide_memory_access();
}

void Protection::anti_debug() {
    ptrace(PT_DENY_ATTACH, 0, 0, 0);
}

void Protection::hide_memory_access() {}