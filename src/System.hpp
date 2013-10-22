#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "EntitySystem.hpp"

template<typename PrimaryComponent, typename... Components>
class System
{
public:
    System(EntitySystem<Components...> & entitySystem) : es(entitySystem) {}

    virtual void processStep(PrimaryComponent & c) = 0;
    void batch();

private:
    EntitySystem<Components...> & es;

};

/*!
 * \brief   Calls processStep for every component of PrimaryComponent type.
 * TODO: Parallize!
 */
template<typename PrimaryComponent, typename... Components>
void System<PrimaryComponent, Components...>::batch() {
    std::vector<PrimaryComponent> & components = es.template getComponents<PrimaryComponent>();
    for(int n = 0; n < components.size(); n++) {
        processStep(components[n]);
    }
}


#endif // SYSTEM_HPP
