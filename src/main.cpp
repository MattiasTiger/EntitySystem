#include <iostream>
#include "EntitySystem.hpp"
#include "Component.hpp"
#include "System.hpp"

#define AllComponents Name,Position     //OBS required as for now... :(

class Name : public Component {
public:
    std::string name;
};

class Position : public Component {
public:
    float x;
};


class SystemTest : public System<Name, AllComponents>
{
public:
    SystemTest(EntitySystem<AllComponents> & es):System<Name, AllComponents>::System(es) {}
    void processStep(Name & name) {
        std::cerr << "name: " + name.name + "\n";
    }
};

int main()
{
    EntitySystem<AllComponents> entitySystem;

    Entity<AllComponents> & e = entitySystem.createEntity();
    Entity<AllComponents> & e2 = entitySystem.createEntity();
    entitySystem.addComponent<Name>(e);
    entitySystem.addComponent<Name>(e2);
    e.get<Name>()->name = "John Doe";
    e2.get<Name>()->name = "Bar Foo";
    std::cerr << "\n";

    SystemTest test(entitySystem);
    test.batch();

    return 0;
}

