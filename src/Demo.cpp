#include "Demo.hpp"
#include "groundcontact.hpp"

Demo::Demo() : window(nullptr), renderer(nullptr), ticksCount(0), running(), maxContacts(10) {}

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

    resolver = new ContactResolver(5);


    Particle* particle = new Particle();

    particle->setPosition(1024.0f / 4.0f - 50.0f, 728.0f / 2.0f - 50.0f);
    particle->setMass(1.0f);
    particle->setDamping(0.99f);
    particle->setAcceleration(0.0f, -9.81f);

    particles.push_back(particle);


    particle = new Particle();

    particle->setPosition(1024.0f / 4.0f * 2.0f - 50.0f, 728.0f / 2.0f - 50.0f);
    particle->setMass(1.0f);
    particle->setDamping(0.99f);
    particle->setAcceleration(0.0f, 2 * -9.81f);

    particles.push_back(particle);


    particle = new Particle();

    particle->setPosition(1024.0f / 4.0f * 3.0f - 50.0f, 728.0f / 2.0f - 50.0f);
    particle->setMass(1.0f);
    particle->setDamping(0.99f);
    particle->setAcceleration(0.0f, 9.81f);

    particles.push_back(particle);


    GroundContact* groundContactGenerator = new GroundContact();
    groundContactGenerator->init(particles);
    generators.push_back(groundContactGenerator);

    contacts = new Contact[maxContacts];

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

    for (auto particle : particles)
    {
        particle->integrate(deltaTime);
    }

    unsigned usedContacts = generateContacts();

    if (usedContacts)
    {
        resolver->setIterations(usedContacts * 2);
        resolver->resolveContacts(contacts, usedContacts, deltaTime);
    }
}

void Demo::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    for (auto particle : particles)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        nm::float2 currentPosition = particle->getPosition();

        SDL_Rect particleRect = {
            static_cast<int>(1024.0f - (currentPosition.x() + 50.0f)),
            static_cast<int>(728.0f - (currentPosition.y() + 50.0f)),
            100,
            100
        };
        
        SDL_RenderFillRect(renderer, &particleRect);
    }

    SDL_RenderPresent(renderer);
}

unsigned Demo::generateContacts()
{
    unsigned limit = maxContacts;
    Contact* nextContact = contacts;

    for (auto generator : generators)
    {
        unsigned used = generator->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        if (limit <= 0) break;
    }

    return maxContacts - limit;
}