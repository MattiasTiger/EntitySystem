#ifndef COMPONENT_HPP
#define COMPONENT_HPP

template<typename... RequiredComponents>
class Component
{
public:
    typedef std::tuple<RequiredComponents...> REQUIRED_COMPONENTS;
    int entityOwnerID;
};

#endif // COMPONENT_HPP
