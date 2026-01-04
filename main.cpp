#include <stdio.h>
#include <iostream>
#include <cstring>      // memcpy 사용을 위해 필요
#include <sys/mman.h>   // mmap, mprotect
#include <unistd.h>     // sysconf

// 이미 올바르게 정렬된 쉘코드 (Python 스크립트 결과물)
#include "main.h"

int main() {
    // 1. 메모리 할당 (초기엔 Write 권한 필요)
    void* exec_mem = mmap(nullptr, code_len, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    if (exec_mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    std::memcpy(exec_mem, code, code_len);

    if (mprotect(exec_mem, code_len, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect failed");
        return 1;
    }

    __builtin___clear_cache((char*)exec_mem, (char*)exec_mem + code_len);

    std::cout << "Executing shellcode..." << std::endl;
    
    int (*func)(int, int) = (int(*)(int, int))exec_mem;
    int result = func(31, 4);
    std::cout << "Shellcode finished with result: " << result << std::endl;

    munmap(exec_mem, code_len);

    return 0;
}