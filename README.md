# MagicKit 🪄

**MagicKit** is a lightweight research framework for compiling, converting, and dynamically executing ARM64 shellcode on macOS (Apple Silicon). 

It provides a seamless workflow to convert raw assembly instructions into executable machine code, handling the complexities of `mmap`, memory protection (W^X), and instruction cache invalidation on ARM64 architectures.

## 🚀 Features

- **ARM64 Assembly Support**: Write native ARM64 assembly code.
- **Hex Converter**: Python utility to parse disassembly (`objdump`) and convert it to Little Endian C-strings.
- **Dynamic Loader**: C++ harness to allocate executable memory (`PROT_EXEC`) and run shellcode.
- **Apple Silicon Ready**: Handles `__builtin___clear_cache` to prevent "illegal hardware instruction" errors caused by stale instruction caches.

## 📋 Prerequisites

- macOS (Apple Silicon recommended)
- `clang` / `clang++`
- `python3`

## 🛠 Project Structure

```bash
.
├── test.asm        # Source ARM64 assembly code
├── converter.py    # Python script to convert ASM hex to C-string
├── runner.cpp      # C++ loader to execute the shellcode
└── README.md       # This file
