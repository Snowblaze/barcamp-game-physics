#pragma once

#ifndef DEMO_HPP
#define DEMO_HPP

#include <vector>
#include <SDL.h>
#include "particle.hpp"
#include "contactresolver.hpp"
#include "contactgenerator.hpp"

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

    unsigned generateContacts();

    SDL_Window* window;

    SDL_Renderer* renderer;

    Uint32 ticksCount;

    bool running;

    std::vector<Particle*> particles;

    ContactResolver* resolver;

    std::vector<ContactGenerator*> generators;

    Contact* contacts;

    unsigned maxContacts;
};

#endif