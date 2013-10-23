#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <map>

#include "Component.hpp"
#include "Vectors.hpp"

template<typename... Components>
class EntitySystem;

template<typename... Components>
class Entity
{
    friend class EntitySystem<Components...>;
public:
    Entity()                { id = -1; es = 0; }
    Entity(int id) : id(id) {}
    const int getID()       { return id; }
    template<typename Component> bool has();
    template<typename Component> void add();
    template<typename Component> Component & get();
    template<typename Component> void remove();

private:
    int id;
    EntitySystem<Components...> * es;
    std::tuple<Components*...> componentIndexes;

    template<typename Component>
    void assign(int index);

    template<typename Component>
    int getIndex();
};

template<typename... Components>
template<typename Component> bool Entity<Components...>::has() {
    Component * index = std::get<get_index<Component,Components...>::INDEX >(componentIndexes);
    return ((int)index) > 0;
}

template<typename... Components>
template<typename Component> Component & Entity<Components...>::get() {
    Component * index = std::get<get_index<Component,Components...>::INDEX >(componentIndexes);
    return es->template getComponents<Component>()[((int)index)-1];
}

template<typename... Components>
template<typename Component> void Entity<Components...>::add() {
    Component * index = std::get<get_index<Component,Components...>::INDEX >(componentIndexes);
    if(((int)index) > 0)   // Already have the component
        return;
    es->template addComponent<Component>(*this);
}

template<typename... Components>
template<typename Component> void Entity<Components...>::remove() {
    Component * index = std::get<get_index<Component,Components...>::INDEX >(componentIndexes);
    if(((int)index) <= 0)   // Does not have the component
        return;
    es->template removeComponent<Component>(*this);
}

template<typename... Components>
template<typename Component> void Entity<Components...>::assign(int index) {
    std::get<get_index<Component,Components...>::INDEX>(componentIndexes) = (Component*)(index+1);
}

template<typename... Components>
template<typename Component> int Entity<Components...>::getIndex() {
    return ((int)std::get<get_index<Component,Components...>::INDEX>(componentIndexes))-1;
}

#endif // ENTITY_HPP
