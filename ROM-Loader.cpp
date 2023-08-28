#include "CHIP-8.hpp"
#include <fstream>


void Chip8::LoadROM(char const* filename) {
    std::ifstream file(filename,std::ios::binary | std::ios::ate);
    if ( file.is_open()) {
        std::cout << "Reading Rom" << "\n";
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0,std::ios::beg);
        file.read(buffer,size);
        file.close();


        for (int i = 0; i< size; ++i) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
        std::cout << "Done Reading Rom" << "\n";
    }
}