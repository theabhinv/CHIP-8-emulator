#ifndef CHIP8_H
#define CHIP8_H

#include <iostream>

#include "SDL2/SDL.h"

class Chip8
{
    public:
       Chip8();
       ~Chip8(); 
    private:

    public:

    private:
        SDL_Window* _window{};
        SDL_Renderer* _renderer{};
        SDL_Texture* _texture{};
};

#endif