#include <stdio.h>
#include <iostream>
#include <cstring>
#include <sys/mman.h>   // For mmap, mprotect
#include <unistd.h>     // For getpagesize
#include <libkern/OSCacheControl.h> // For sys_icache_invalidate (macOS specific)

#include "main.h"

int main() {
    // 1. Get the system page size
    size_t page_size = sysconf(_SC_PAGESIZE);
    
    // 2. Allocate a memory page that is Read/Write initially
    void* exec_mem = mmap(nullptr, sizeof(code), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    if (exec_mem == MAP_FAILED) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    // 3. Copy the shellcode into the allocated memory
    std::memcpy(exec_mem, code, sizeof(code));

    // 4. Change permissions to Read/Execute (removing Write permission is safer)
    if (mprotect(exec_mem, sizeof(code), PROT_READ | PROT_EXEC) == -1) {
        std::cerr << "Memory protection failed" << std::endl;
        return 1;
    }

    // 5. Invalidate Instruction Cache (Critical for macOS on Apple Silicon)
    // This ensures the CPU doesn't execute stale data from the cache.
    sys_icache_invalidate(exec_mem, sizeof(code));

    // 6. Cast to function pointer and execute
    int (*func)(int, int) = (int(*)(int, int))exec_mem;
    
    std::cout << "Executing shellcode..." << std::endl;
    int result = func(10, 4);
    std::cout << "Shellcode finished with result: " << result << std::endl;
    // Cleanup
    munmap(exec_mem, sizeof(code));

    return 0;
}