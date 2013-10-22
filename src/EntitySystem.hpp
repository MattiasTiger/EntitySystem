#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <map>

#include "Component.hpp"
#include "Vectors.hpp"

template<typename... Components>
class Entity
{
private:
    std::tuple<Components*...> componentPointers;
    int id;
public:
    Entity(int id) : id(id) {}
    const int getID() {
        return id;
    }
    template<typename Component>
    Component * get() {
        std::get<get_index<Component,Components...>::INDEX>(componentPointers)>(componentPointers);
    }
};

template<typename... Components>
class EntitySystem
{
private:
    Vectors<Components...> components;
    std::map<int, Entity<Components...> > entities;

public:
    /*
    template<typename Component>
    void add(Component component) {
        components.template getVector<Component>().push_back(component);
    }
    */

    template<typename Component>
    std::vector<Component> & getComponents() {
        return components.template getVector<Component>();
    }

    Entity<Components...> & createEntity() {

    }
/*
    template<typename Component>
    void addComponent(Entity & entity) {

    }
*/
};

#endif // ENTITYSYSTEM_HPP
