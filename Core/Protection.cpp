// Core/Protection.cpp
#include "Protection.h"
#import <Foundation/Foundation.h>
#include <dlfcn.h>

// Тип для ptrace
typedef int (*ptrace_ptr_t)(int request, pid_t pid, caddr_t addr, int data);

void Protection::init() {
    anti_debug();
    hide_memory_access();
}

void Protection::anti_debug() {
    // Загружаем ptrace динамически через dlopen
    void* handle = dlopen("/usr/lib/system/libsystem_kernel.dylib", RTLD_LAZY);
    if (handle) {
        ptrace_ptr_t ptrace_ptr = (ptrace_ptr_t)dlsym(handle, "ptrace");
        if (ptrace_ptr) {
            // PT_DENY_ATTACH = 31
            ptrace_ptr(31, 0, 0, 0);
        }
        dlclose(handle);
    }
}

void Protection::hide_memory_access() {
    // Пустая заглушка
}
