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
    entitySystem.add(Name());
    entitySystem.get<Name>()[0].name = "A name";
    std::cout << entitySystem.get<Name>()[0].name << std::endl;

    return 0;
}

