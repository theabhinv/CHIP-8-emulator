#ifndef CHIP8_H
#define CHIP8_H

#include <iostream>
#include <cstring>
#include <cstdint>
#include <random>
#include "SDL2/SDL.h"

static const int   START_PROG_MEM = 0x200;
static const int   END_PROG_MEM   = 0xFFF;
static const int   X_RES          = 64;
static const int   Y_RES          = 32;
static const int   RES_SCALING    = 20;
const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;

class Chip8
{
    public:
    Chip8();
    ~Chip8(); 
	   
	void Cycle();

	uint32_t display[Y_RES * X_RES]{};

    private:
	bool Input();
	void clearInput();

	void Table0();
	void Table8();
	void TableE();
	void TableF();

    // Do nothing
	void OP_NULL();

	// CLS
	void OP_00E0();

	// RET
	void OP_00EE();

	// JP address
	void OP_1nnn();

	// CALL address
	void OP_2nnn();

	// SE Vx, byte
	void OP_3xkk();

	// SNE Vx, byte
	void OP_4xkk();

	// SE Vx, Vy
	void OP_5xy0();

	// LD Vx, byte
	void OP_6xkk();

	// ADD Vx, byte
	void OP_7xkk();

	// LD Vx, Vy
	void OP_8xy0();

	// OR Vx, Vy
	void OP_8xy1();

	// AND Vx, Vy
	void OP_8xy2();

	// XOR Vx, Vy
	void OP_8xy3();

	// ADD Vx, Vy
	void OP_8xy4();

	// SUB Vx, Vy
	void OP_8xy5();

	// SHR Vx
	void OP_8xy6();

	// SUBN Vx, Vy
	void OP_8xy7();

	// SHL Vx
	void OP_8xyE();

	// SNE Vx, Vy
	void OP_9xy0();

	// LD I, address
	void OP_Annn();

	// JP V0, address
	void OP_Bnnn();

	// RND Vx, byte
	void OP_Cxkk();

	// DRW Vx, Vy, height
	void OP_Dxyn();

	// SKP Vx
	void OP_Ex9E();

	// SKNP Vx
	void OP_ExA1();

	// LD Vx, DT
	void OP_Fx07();

	// LD Vx, K
	void OP_Fx0A();

	// LD DT, Vx
	void OP_Fx15();

	// LD ST, Vx
	void OP_Fx18();

	// ADD I, Vx
	void OP_Fx1E();

	// LD F, Vx
	void OP_Fx29();

	// LD B, Vx
	void OP_Fx33();

	// LD [I], Vx
	void OP_Fx55();

	// LD Vx, [I]
	void OP_Fx65();


        SDL_Window* _window{};
        SDL_Renderer* _renderer{};
        SDL_Texture* _texture{};




        uint8_t 	memory[MEMORY_SIZE]{};       //memory //from location 0x000 (0) to 0xFFF (4095) 
        uint8_t     V[REGISTER_COUNT];			//16 8 bit registers
        uint16_t 	index{};                    // Address Register
        uint8_t     delayTimer{};           	// Refresh rate of the screen
        uint8_t     soundTimer{};           	// Play a sound after counting down from 60
        uint16_t    pc{};                   	// Program Counter, program space: 0x200 - 0xFFF
        uint8_t     sp{};                   	// Stack Pointer
        uint16_t 	stack[STACK_LEVELS]{};     // Program Stack
        uint16_t    opcode{};
		uint8_t     keypad[0xF];

		std::default_random_engine randGen;
		std::uniform_int_distribution<uint8_t> randByte;


	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1]{&Chip8::OP_NULL};
	Chip8Func table0[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func table8[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableE[0xE + 1]{&Chip8::OP_NULL};
	Chip8Func tableF[0x65 + 1]{&Chip8::OP_NULL};
};

#endif