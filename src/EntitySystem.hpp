#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include "Component.hpp"
#include "System.hpp"

#include "Vectors.hpp"

template<typename... Components>
class EntitySystem
{
public:
    template<typename Component>
    void add(Component component) {
        vectors.get<Component>().push_back(component);
    }

    template<typename Component>
    std::vector<Component>& get() {
        return vectors.get<Component>();
    }

private:
    //std::tuple<std::vector<Components>...> components;
    Vectors<Components...> vectors;
};

#endif // ENTITYSYSTEM_HPP
