 
#pragma once


#include <iostream>
#include <cstdlib>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "log.h"
#include "sprite.h"



class Screen{
    private:
        SDL_Window *window;                    
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Event event;

        unsigned int chooser = 0;
        const int numberOfStars = 100;
        const int starSize = 2; // Pixels


    private:
        void handle_stars(std::vector<int> starsX , std::vector<int> &starsY , SDL_Rect darea);

    public:
        Screen(int width , int height);
        void render();
        bool menu();
};
