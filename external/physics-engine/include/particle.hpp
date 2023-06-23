#pragma once

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "nicemath.h"
#include "math.h"

class Particle
{
protected:
    nm::float2 position;
    nm::float2 velocity;
    nm::float2 acceleration;

    float damping;
    float inverseMass;

public:
    void setDamping(const float value)
    {
        damping = value;
    }

    float getDamping() const
    {
        return damping;
    }

    nm::float2 getAcceleration() const
    {
        return acceleration;
    }

    void setAcceleration(const nm::float2 value)
    {
        acceleration = value;
    }

    void setAcceleration(const float x, const float y)
    {
        acceleration = nm::float2(x, y);
    }

    void setMass(const float value)
    {
        inverseMass = 1.0f / value;
    }

    float getInverseMass() const
    {
        return inverseMass;
    }

    void setInverseMass(const float value)
    {
        inverseMass = value;
    }

    void setPosition(const nm::float2 value)
    {
        position = value;
    }

    void setPosition(const float x, const float y)
    {
        position = nm::float2(x, y);
    }

    nm::float2 getPosition() const
    {
        return position;
    }

    void setVelocity(const nm::float2 value)
    {
        velocity = value;
    }

    void setVelocity(const float x, const float y)
    {
        velocity = nm::float2(x, y);
    }

    nm::float2 getVelocity() const
    {
        return velocity;
    }

    void integrate(const float duration)
    {
        if (inverseMass <= 0.0f) return;

        position = position + velocity * duration;

        nm::float2 resultingAcceleration = acceleration;

        velocity = velocity + resultingAcceleration * duration;

        velocity = velocity * powf(damping, duration);
    }
};

#endif