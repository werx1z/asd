// Core/Memory.h
#pragma once
#include <mach/mach.h>
#include <dlfcn.h>
#include <cstring>

class Memory {
private:
    mach_port_t task;
    uintptr_t base_address;
    
    static uintptr_t get_base_address_static() {
        Dl_info info;
        if (dladdr((const void*)&get_base_address_static, &info)) {
            return (uintptr_t)info.dli_fbase;
        }
        return 0;
    }
    
public:
    Memory() {
        task = mach_task_self();
        base_address = get_base_address_static();
    }
    
    template<typename T>
    T read(uintptr_t address) {
        T value = 0;
        vm_size_t size = sizeof(T);
        vm_offset_t data;
        mach_msg_type_number_t count = 0;
        
        kern_return_t kr = mach_vm_read(task, address, size, &data, &count);
        if (kr == KERN_SUCCESS && count == size) {
            memcpy(&value, (void*)data, size);
            vm_deallocate(task, data, count);
        }
        return value;
    }
    
    template<typename T>
    void write(uintptr_t address, T value) {
        vm_write(task, address, (vm_offset_t)&value, sizeof(T));
    }
    
    uintptr_t read_ptr(uintptr_t address) { return read<uintptr_t>(address); }
    float read_float(uintptr_t address) { return read<float>(address); }
    int read_int(uintptr_t address) { return read<int>(address); }
    bool read_bool(uintptr_t address) { return read<bool>(address); }
    
    void read_string(uintptr_t address, char* buffer, size_t size) {
        vm_offset_t data;
        mach_msg_type_number_t count = 0;
        
        kern_return_t kr = mach_vm_read(task, address, size, &data, &count);
        if (kr == KERN_SUCCESS && count == size) {
            memcpy(buffer, (void*)data, size);
            vm_deallocate(task, data, count);
        }
    }
    
    void write_float(uintptr_t address, float value) { write<float>(address, value); }
    void write_int(uintptr_t address, int value) { write<int>(address, value); }
    uintptr_t get_base() { return base_address; }
};