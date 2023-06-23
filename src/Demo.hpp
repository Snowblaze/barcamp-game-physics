#pragma once

#ifndef DEMO_HPP
#define DEMO_HPP

#include <SDL.h>
#include "particle.hpp"

class Demo
{
public:
    Demo();

    bool init();

    void run();

    void shutdown();

private:
    void processInput();

    void update();

    void render();

    SDL_Window* window;

    SDL_Renderer* renderer;

    Uint32 ticksCount;

    bool running;

    Particle* mCharacter;
};

#endif