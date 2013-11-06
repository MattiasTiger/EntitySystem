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

class Position : public Component<Position, Name> {
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
    /*
    EntitySystem<AllComponents> entitySystem;

    Entity<AllComponents> & e = entitySystem.createEntity();
    Entity<AllComponents> & e2 = entitySystem.createEntity();

    e.add<Position>();  // Require component Name! It is added by automagic.
    e.get<Name>().nameString = "John Doe";

    std::cerr << "\n";
    SystemTest test(entitySystem);
    test.batch();
    */

    int i = MetaFunction<get_index, merge_tuples<std::tuple<Name>, Position::REQUIRED_COMPONENTS>::type>::INDEX;
    std::cout << i << "\n";

    /*
    meta::if<requireRandomAccess<Something>::type,
            MetaFunction<std::vector, type>,
            MetaFunction<std::list, type>           >::type myContainer;
    */

    std::vector<std::string> componentNames;
    semi_meta::ForEach<Position::REQUIRED_COMPONENTS, PushComponentName, decltype(componentNames)>::execute(componentNames);
    for(int n = 0; n < componentNames.size(); n++)
        std::cout << componentNames[n] << "\n";

    std::cout << "\n";
    semi_meta::ForEach<Position::REQUIRED_COMPONENTS, CoutComponentName>::execute();

    meta::ForEach<std::tuple<Position>, RemoveIfRequired, std::tuple<Position> >::execute();

    std::cout << "testing IF...\n";

    // Below: require that isTupleEmpty is a meta::True or meta::False...
    //meta::IF<meta::NOT<isTupleEmpty<std::tuple<Name> >::value >, meta::test>::execute();

    typedef meta::Tuple<double, int> T;
    std::cout << T::length << "\n";
    T::getType<1>::type a = 15;
    std::cout << a << "\n";

    return 0;
}

