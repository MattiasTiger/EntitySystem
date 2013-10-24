#include <iostream>
#include "EntitySystem.hpp"
#include "Component.hpp"
#include "System.hpp"

#define AllComponents Name,Position     //OBS required as for now... :(

class Name : public Component<> {
public:
    const std::string getName() override { return "Name"; }
    std::string nameString;
};

class Position : public Component<Name> {
public:
    const std::string getName() override { return "Position"; }
    float x;
};

class SystemTest : public System<Name, AllComponents>
{
public:
    SystemTest(EntitySystem<AllComponents> & es):System<Name, AllComponents>::System(es) {}
    void processStep(Name & name) {
        Entity<AllComponents> & e = getEntity(name);
        std::cerr << "name: " + e.get<Name>().nameString + "\n";
    }
};

int main()
{
    EntitySystem<AllComponents> entitySystem;

    Entity<AllComponents> & e = entitySystem.createEntity();
    Entity<AllComponents> & e2 = entitySystem.createEntity();

    e.add<Position>();  // Require component Name! It is added by automagic.
    e.get<Name>().nameString = "John Doe";

    std::cerr << "\n";
    SystemTest test(entitySystem);
    test.batch();

    return 0;
}

