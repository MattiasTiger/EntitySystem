#include <iostream>
#include "EntitySystem.hpp"
#include "Component.hpp"

class Name : public Component {
public:
    std::string name;
};

class Position : public Component {
public:
    float x;
};

int main()
{
    EntitySystem<Name, Position> entitySystem;

    return 0;
}

