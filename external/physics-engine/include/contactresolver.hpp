#pragma once

#ifndef CONTACTRESOLVER_HPP
#define CONTACTRESOLVER_HPP

#include "contact.hpp"

class ContactResolver
{
protected:
    unsigned iterations;

    unsigned iterationsUsed;

public:
    ContactResolver(unsigned iterations) : iterations(iterations) {}

    void setIterations(unsigned value)
    {
        iterations = value;
    }

    void resolveContacts(Contact* contactArray, unsigned numContacts, float duration)
    {
        unsigned i;
        iterationsUsed = 0;
        while (iterationsUsed < iterations)
        {
            // Find the contact with the lowest separating velocity
            float max = std::numeric_limits<float>::max();
            unsigned maxIndex = numContacts;
            for (i = 0; i < numContacts; i++)
            {
                float sepVel = contactArray[i].calculateSeparatingVelocity();
                if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
                {
                    max = sepVel;
                    maxIndex = i;
                }
            }

            // Terminate if none were found
            if (maxIndex == numContacts) break;

            contactArray[maxIndex].resolve(duration);
            iterationsUsed++;
        }
    }
};

#endif