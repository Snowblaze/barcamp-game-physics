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

    mCharacter = new Particle();

    mCharacter->setPosition((1024.0f - 100.0f) / 2.0f, (728.0f - 100.0f) / 2.0f);
    mCharacter->setMass(1.0f);
    mCharacter->setDamping(0.99f);
    mCharacter->setAcceleration(0.0f, -9.81f);

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

    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mCharacter->integrate(deltaTime);
}

void Demo::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    nm::float2 currentPosition = mCharacter->getPosition();

    SDL_Rect character = {
        static_cast<int>(1024.0f - currentPosition.x()),
        static_cast<int>(728.0f - currentPosition.y()),
        100,
        100
    };

    SDL_RenderFillRect(renderer, &character);

    SDL_RenderPresent(renderer);
}