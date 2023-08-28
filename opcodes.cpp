#include "CHIP-8.hpp"
#include <cstring>
// reserved
void Chip8::OP_0NNN()
{
}
// CLS clear Display
void Chip8::OP_00E0()
{
    memset(screen, 0, sizeof(screen));
}
// RET return
void Chip8::OP_00EE()
{
    --sp;
    pc = stack[sp];
}
// JMP to adress NNN
void Chip8::OP_1NNN()
{
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}
// CALL to address NNN
void Chip8::OP_2NNN()
{
    uint16_t address = opcode & 0x0FFFu;
    stack[sp] = pc;
    ++sp;
    pc = address;
}
// Skip Next instruction if NN == Vx
void Chip8::OP_3XNN()
{
    uint8_t NN = opcode & 0x00FFu;
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    if (registers[Vx] == NN)
    {
        pc += 2;
    }
}
// Skip Next instruction if NN != Vx
void Chip8::OP_4XNN()
{
    uint8_t NN = opcode & 0x00FFu;
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    if (registers[Vx] != NN)
    {
        pc += 2;
    }
}
// Skip Next instruction if Vy == Vx
void Chip8::OP_5XY0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    if (registers[Vx] == registers[Vy])
    {
        pc += 2;
    }
}
// Set Vx to NN
void Chip8::OP_6XNN()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t NN = opcode & 0x00FFu;
    registers[Vx] = NN;
}
// Set Vx += NN
void Chip8::OP_7XNN()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t NN = opcode & 0x00FFu;
    registers[Vx] += NN;
}
// Set Vx = Vy
void Chip8::OP_8XY0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] = registers[Vy];
}
// Set Vx = Vx | Vy
void Chip8::OP_8XY1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] = registers[Vx] | registers[Vy];
}
// Set Vx &= Vy
void Chip8::OP_8XY2()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] &= registers[Vy];
}
// set Vx ^= Vy
void Chip8::OP_8XY3()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[Vx] ^= registers[Vy];
}
// Set Vx = Vx + Vy && Vf = carry
void Chip8::OP_8XY4()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = registers[Vx] + registers[Vy];
    registers[0xF] = sum > 255U;
    registers[Vx] = sum & 0xFFu;
}
// Set Vx = Vx - Vy && Vf = !borrow
void Chip8::OP_8XY5()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[0xF] = !(registers[Vx] > registers[Vy]);
    registers[Vx] -= registers[Vy];
}
// set Vx = Vx >> 1 && Vf = least-significant bit;
void Chip8::OP_8XY6()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[0xF] = Vx & 0x01u;
    registers[Vx] >>= 1;
}
// Set Vx = Vy - Vx && Vf = !borrow

void Chip8::OP_8XY7()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    registers[0xF] = (registers[Vy] > registers[Vx]);
    registers[Vx] = registers[Vy] - registers[Vx];
}
// set Vx = Vx << 1 && Vf = most-significant bit;
void Chip8::OP_8XYE()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[0xF] = (Vx & 0x80u) >> 7u;
    registers[Vx] <<= 1;
}
// Skip next instruction if Vx != Vy
void Chip8::OP_9XY0()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    if (registers[Vx] != registers[Vy])
    {
        pc += 2;
    }
}
// set index = NNN
void Chip8::OP_ANNN()
{
    uint16_t NNN = (opcode & 0xFFFu);
    index = NNN;
}
// JMP to address NNN + V0
void Chip8::OP_BNNN()
{
    uint16_t NNN = (opcode & 0x0FFFu);
    pc = registers[0x0] + NNN;
}
// Set Vx = randByte & NN
void Chip8::OP_CXNN()
{
    uint8_t NN = (opcode & 0x0FFu);
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[Vx] = randByte(randGen) & NN;
}
// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void Chip8::OP_DXYN()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;
    uint8_t N = opcode & 0x000Fu;

    // Wrap if going beyond screen boundaries
    uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
    uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

    registers[0xF] = 0;

    for (unsigned int address = index; address < N + index; ++address)
    {
        uint8_t spriteByte = memory[address];

        for (unsigned int bit = 0; bit < 8; ++bit)
        {
            uint8_t spritePixel = spriteByte & (0x80u >> bit);
            uint8_t *screenPixel = &screen[4 * ((yPos + address - index) * VIDEO_WIDTH + (xPos + bit))];

            // Sprite pixel is on
            if (spritePixel)
            {
                // Screen pixel also on - collision
                if (screenPixel[0] == 0xFF)
                {
                    registers[0xF] = 1;
                }

                // Effectively XOR with the sprite pixel
                screenPixel[0] ^= 0xFF;
                screenPixel[1] ^= 0xFF;
                screenPixel[2] ^= 0xFF;
                screenPixel[3] ^= 0xFF;
            }
        }
    }
}
// Skip next instruction if key with the value of Vx is pressed.
void Chip8::OP_EX9E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    uint8_t key = registers[Vx];

    if (keypad[key])
    {
        pc += 2;
    }
}
// Skip next instruction if key with the value of Vx is not pressed.
void Chip8::OP_EXA1()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;

    uint8_t key = registers[Vx];

    if (!keypad[key])
    {
        pc += 2;
    }
}
// Set Vx = delay timer value
void Chip8::OP_FX07()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    registers[Vx] = delayTimer;
}
// Wait for keypress , store in Vx
void Chip8::OP_FX0A()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    if (keypad[0])
    {
        registers[Vx] = 0;
    }
    else if (keypad[1])
    {
        registers[Vx] = 1;
    }
    else if (keypad[2])
    {
        registers[Vx] = 2;
    }
    else if (keypad[3])
    {
        registers[Vx] = 3;
    }
    else if (keypad[4])
    {
        registers[Vx] = 4;
    }
    else if (keypad[5])
    {
        registers[Vx] = 5;
    }
    else if (keypad[6])
    {
        registers[Vx] = 6;
    }
    else if (keypad[7])
    {
        registers[Vx] = 7;
    }
    else if (keypad[8])
    {
        registers[Vx] = 8;
    }
    else if (keypad[9])
    {
        registers[Vx] = 9;
    }
    else if (keypad[10])
    {
        registers[Vx] = 10;
    }
    else if (keypad[11])
    {
        registers[Vx] = 11;
    }
    else if (keypad[12])
    {
        registers[Vx] = 12;
    }
    else if (keypad[13])
    {
        registers[Vx] = 13;
    }
    else if (keypad[14])
    {
        registers[Vx] = 14;
    }
    else if (keypad[15])
    {
        registers[Vx] = 15;
    }
    else
    {
        pc -= 2;
    }
}
// set delay timer to Vx
void Chip8::OP_FX15()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    delayTimer = registers[Vx];
}
// set sound timer to Vx
void Chip8::OP_FX18()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    soundTimer = registers[Vx];
}
// Set index += VX
void Chip8::OP_FX1E()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    index += registers[Vx];
}
// Set I = location of sprite for digit Vx
void Chip8::OP_FX29()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t digit = registers[Vx];

    index = FONTSET_START_ADDRESS + (5 * digit);
}
// Store BCD representation of Vx in memory locations I, I+1, and I+2.
void Chip8::OP_FX33()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t number = registers[Vx];
    uint8_t ones = number % 10;
    uint8_t tens = (number / 10) % 10;
    uint8_t hundereds = (number / 100) % 10;
    memory[index] = hundereds;
    memory[index + 1] = tens;
    memory[index + 2] = ones;
}
// Store registers V0 through Vx in memory starting at location I.
void Chip8::OP_FX55()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    for (uint8_t i = 0; i < Vx; i++)
    {
        memory[index + i] = registers[i];
    }
}
void Chip8::OP_FX65()
{
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    for (uint8_t i = 0; i < Vx; i++)
    {
        registers[i] = memory[index + i];
    }
}
