#pragma once

#ifndef CONTACTGENERATOR_HPP
#define CONTACTGENERATOR_HPP

#include "contact.hpp"

class ContactGenerator
{
public:
    virtual unsigned addContact(Contact* contact, unsigned limit) const = 0;
};

#endif