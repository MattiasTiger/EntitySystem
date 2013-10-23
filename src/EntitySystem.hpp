#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <map>

#include "Component.hpp"
#include "Vectors.hpp"

#include "Entity.hpp"

template<typename... Components>
class EntitySystem
{
private:
    Vectors<Components...> components;
    std::map<int, Entity<Components...> > entities;

public:

    template<typename Component> std::vector<Component> & getComponents();

    Entity<Components...> & createEntity();

    template<typename Component> void hasComponent(Entity<Components...> & entity);

    template<typename Component> void addComponent(Entity<Components...> & entity);

    template<typename Component> void removeComponent(Entity<Components...> & entity);

};

template<typename... Components>
template<typename Component>
std::vector<Component> & EntitySystem<Components...>::getComponents() {
    return components.template getVector<Component>();
}

template<typename... Components>
Entity<Components...> & EntitySystem<Components...>::createEntity() {
    int id = (int) new int;
    entities[id].id = id;
    entities[id].es = this;
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
    // TODO: some magic, not the things below

    // Do: Check free-list for that Component type
    //      Use component index from free-list if possible, otherwise push back new Component.

    //getComponents<Component>().reserve(100);    // To get around the segfault due to vector expansion and reallocation.. Should probably use index-list instead of pointer list in Entity (and a reference to the entity system...? :/)
    getComponents<Component>().push_back(Component());
    Component * c = (Component*) (getComponents<Component>().size());
    entity.assign(c);
}

template<typename... Components>
template<typename Component>
void EntitySystem<Components...>::removeComponent(Entity<Components...> & entity) {
    // TODO: some magic, not the things below

    // Do: Add component index to free-list for that Component type.
    //delete std::get<get_index<Component,Components...> >(entity.componentPointers);
    entity.assign(0);
}

#endif // ENTITYSYSTEM_HPP
