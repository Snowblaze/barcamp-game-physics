#include "Demo.hpp"

Demo::Demo() : window(nullptr), renderer(nullptr), ticksCount(0), running() {}

bool Demo::init()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Demo", 100, 100, 1024, 728, 0);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Demo::run()
{
    running = true;

    while (running)
    {
        processInput();
        update();
        render();
    }
}

void Demo::shutdown()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Demo::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        running = false;
    }
}

void Demo::update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    ticksCount = SDL_GetTicks();
}

void Demo::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}