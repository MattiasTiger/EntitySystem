#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <map>

#include "Component.hpp"
#include "Vectors.hpp"

template<typename... Components>
class EntitySystem;

template<typename... Components>
class Entity
{
    friend class EntitySystem<Components...>;
private:
    std::tuple<Components*...> componentPointers;
    int id;
public:
    Entity() { id = -1; }
    Entity(int id) : id(id) {}
    const int getID() {
        return id;
    }
    template<typename Component>
    Component * get() {
        return std::get<get_index<Component,Components...>::INDEX >(componentPointers);
    }
private:
    template<typename Component>
    void assign(Component * pointer) {
        std::get<get_index<Component,Components...>::INDEX>(componentPointers) = pointer;
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
        int id = (int) new int;
        entities[id].id = id;
        return entities[id];
    }

    template<typename Component>
    void addComponent(Entity<Components...> & entity) {
        // TODO: some magic, not the things below
        getComponents<Component>().reserve(100);    // To get around the segfault due to vector expansion and reallocation.. Should probably use index-list instead of pointer list in Entity (and a reference to the entity system...? :/)
        getComponents<Component>().push_back(Component());
        Component * c = &getComponents<Component>().back();
        entity.assign(c);
    }

    template<typename Component>
    void removeComponent(Entity<Components...> & entity) {
        // TODO: some magic, not the things below
        delete std::get<get_index<Component,Components...> >(entity.componentPointers);
        entity.assign(0);
    }



};

#endif // ENTITYSYSTEM_HPP
