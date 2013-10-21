#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Component.hpp"

class System
{
public:
    System() {}

    virtual void processStep(Component * c) = 0;
    void batch();

private:
};

#endif // SYSTEM_HPP
