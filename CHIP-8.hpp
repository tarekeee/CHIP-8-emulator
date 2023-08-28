#pragma once
#include <cstdint>
#include <random>
#include <assert.h>
#include <iostream>
#include <chrono>
#define START_ADDRESS 0x200
#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50
#define VIDEO_HEIGHT 32
#define VIDEO_WIDTH 64
class Chip8
{
private:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint16_t opcode;
    uint8_t fontset[FONTSET_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    typedef void (Chip8::*Chip8Func)();
    Chip8Func table[0xF + 1];
    Chip8Func table0[0xE + 1];
    Chip8Func table8[0xE + 1];
    Chip8Func tableE[0xE + 1];
    Chip8Func tableF[0x65 + 1];
    void OP_NULL() {

    };
    void OP_0NNN();
    void OP_00E0();
    void OP_00EE();
    void OP_1NNN();
    void OP_2NNN();
    void OP_3XNN();
    void OP_4XNN();
    void OP_5XY0();
    void OP_6XNN();
    void OP_7XNN();
    void OP_8XY0();
    void OP_8XY1();
    void OP_8XY2();
    void OP_8XY3();
    void OP_8XY4();
    void OP_8XY5();
    void OP_8XY6();
    void OP_8XY7();
    void OP_8XYE();
    void OP_9XY0();
    void OP_EX9E();
    void OP_EXA1();
    void OP_FX07();
    void OP_FX0A();
    void OP_FX15();
    void OP_FX18();
    void OP_FX1E();
    void OP_FX29();
    void OP_FX33();
    void OP_FX55();
    void OP_FX65();
    void OP_ANNN();
    void OP_BNNN();
    void OP_CXNN();
    void OP_DXYN();
    void Table0()
    {
        ((*this).*(table0[opcode & 0x000Fu]))();
    }

    void Table8()
    {
        ((*this).*(table8[opcode & 0x000Fu]))();
    }

    void TableE()
    {
        ((*this).*(tableE[opcode & 0x000Fu]))();
    }

    void TableF()
    {
        ((*this).*(tableF[opcode & 0x00FFu]))();
    }

public:
    uint8_t keypad[16]{};
    void Cycle()
    {
        // Fetch
        opcode = (memory[pc] << 8u) | memory[pc + 1];
        std::cout << "OP:" << opcode << "\n";
        std::cout << "PC:" << pc << "\n";
        std::cout << "SP:" << (int)sp << "\n";
        // increment pc
        pc += 2;
        assert(pc < 4096);
        // decode and excute
        ((*this).*(table[(opcode & 0xF000u) >> 12u]))();
        // manage Timers
        if (delayTimer > 0)
        {
            delayTimer -= 1;
        }

        if (soundTimer)
        {
            soundTimer -= 1;
        }
    }
    uint8_t screen[64 * 32 * 4]{};
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;
    void LoadROM(char const *filename);
    Chip8();
};