#pragma once

#ifndef GROUNDCONTACT_HPP
#define GROUNDCONTACT_HPP

#include <vector>
#include "particle.hpp"
#include "contact.hpp"
#include "contactgenerator.hpp"

class GroundContact : public ContactGenerator
{
public:
    void init(std::vector<Particle*> particles)
    {
        mParticles = particles;
    }

    virtual unsigned addContact(Contact* contact, unsigned limit) const
    {
        unsigned count = 0;
        for (auto particle : mParticles)
        {
            if (count >= limit) break;

            float y = particle->getPosition().y();
            if (y < 50.0f)
            {
                contact->contactNormal = nm::float2(0.0f, 1.0f);
                contact->particle[0] = particle;
                contact->particle[1] = nullptr;
                contact->penetration = -y;
                contact->restitution = 0.2f;
                count++;
                contact++;
            }
        }
        return count;
    }

private:
    std::vector<Particle*> mParticles;
};

#endif