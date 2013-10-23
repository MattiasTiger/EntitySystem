#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <map>

#include "Vectors.hpp"
#include "Lists.hpp"
#include "Entity.hpp"
#include "Component.hpp"

template<typename... Components>
class EntitySystem
{
public:
    EntitySystem() {}

    template<typename Component> std::vector<Component> & getComponents();

    Entity<Components...> & createEntity();

    Entity<Components...> & getEntity(int id);

    template<typename Component> void hasComponent(Entity<Components...> & entity);

    template<typename Component> void addComponent(Entity<Components...> & entity);

    template<typename Component> void removeComponent(Entity<Components...> & entity);

private:
    Vectors<Components...> components;
    Lists<Components*...> freeLists;
    std::map<int, Entity<Components...> > entities;
};

template<typename... Components>
template<typename Component>
std::vector<Component> & EntitySystem<Components...>::getComponents() {
    return components.template getContainer<Component>();
}

template<typename... Components>
Entity<Components...> & EntitySystem<Components...>::createEntity() {
    int id = (int) new int;
    entities[id].id = id;
    entities[id].es = this;
    return entities[id];
}

template<typename... Components>
Entity<Components...> & EntitySystem<Components...>::getEntity(int id) {
    return entities[id];
}

template<typename... Components>
template<typename Component>
void EntitySystem<Components...>::hasComponent(Entity<Components...> & entity) {
    return entity.template has<Component>();
}

template<typename... Components>
template<typename Component>
void EntitySystem<Components...>::addComponent(Entity<Components...> & entity) {
    // If another Component is required, add this first, then proceed
    bool fullFillRequirements = true;

    if(std::tuple_size<typename Component::REQUIRED_COMPONENTS>::value > 0)
    {
        fullFillRequirements = entity.template hasComponents2<typename Component::REQUIRED_COMPONENTS>();
    }
    std::cerr << "Component prerequisites fullfilled: "+(fullFillRequirements?std::string("yes"):std::string("no"));

    if(!freeLists.template getContainer<Component*>().empty()) {
        Component * c = freeLists.template getContainer<Component*>().back();
        entity.template assign<Component>((int)c);
        freeLists.template getContainer<Component*>().pop_back();
    } else {
        getComponents<Component>().push_back(Component());
        Component * c = (Component*) (getComponents<Component>().size()-1);
        entity.template assign<Component>((int)c);
    }
    //getComponents<Component>().reserve(100);    // Should probably reserve tons of components somewhere...
}

template<typename... Components>
template<typename Component>
void EntitySystem<Components...>::removeComponent(Entity<Components...> & entity) {
    freeLists.template getContainer<Component*>().push_back((Component*)entity.template getIndex<Component>());
    entity.template assign<Component>(-1);
}

#endif // ENTITYSYSTEM_HPP
