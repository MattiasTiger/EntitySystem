#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include "Component.hpp"
#include "System.hpp"

#include "Vectors.hpp"

#include <iostream>

template<typename... Components>
class EntitySystem
{
private:
    Vectors<Components...> components;
public:
    template<typename Component>
    void add(Component component) {
        components.template getVector<Component>().push_back(component);
    }

    template<typename Component>
    std::vector<Component> & get() {
        return components.template getVector<Component>();
    }

};

#endif // ENTITYSYSTEM_HPP
