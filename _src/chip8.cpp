#include "chip8.h"

Chip8::Chip8()
{
    bool initialized = true;

  std::cout << "Test";
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        initialized = false;
    }
    _window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);
    if(!_window)
    {
        initialized = false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if(!_renderer)
    {
        initialized = false;
    }
    
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 320);
    if(!_texture)
    {
        initialized = false;
    }

    while(initialized)
    {   
        SDL_SetRenderDrawColor( _renderer, 0x0F, 0x0F, 0x0F, 0xFF );
        SDL_RenderClear(_renderer);
        SDL_Event* e;
        while(SDL_PollEvent(e))
        {
            switch(e->type)
            {
                case SDL_QUIT:
                    initialized = false;
                break;
                //INPUT
            }
        }
        //UPDATE
        //DISPLAY
        SDL_RenderPresent(_renderer);
    }
}

Chip8::~Chip8()
{
    SDL_DestroyWindow(_window);
    delete _window;
    SDL_DestroyRenderer(_renderer);
    delete _renderer;
    SDL_DestroyTexture(_texture);
    delete _texture;
    SDL_Quit();
}
