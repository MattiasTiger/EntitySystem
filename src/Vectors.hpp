#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <vector>
#include <algorithm>
#include <type_traits>

#include "MetaLibrary.hpp"


/* Get the length of a variadic list
 */
template<typename ...Types>
struct get_size {
    enum {SIZE = sizeof...(Types)};
};

//===========================================================================

template<typename... Types>
class Vectors
{
private:
    std::tuple<std::vector<Types>...> vectors;

public:
    /*!
     * \Brief   Get vector by type (getVector<Type>()).
     */
    template<typename T>
    std::vector<T> & getVector()
    {
        return std::get<get_index<T,Types...>::INDEX>(vectors);
    }

    /*!
     * \Brief   Get vector index by type (getIndex<Type>).
     */
    template<typename T>
    constexpr const int getIndex()
    {
        return get_index<T, Types...>::INDEX;
    }

    /*!
     * \Brief   Get the number of vectors.
     */
    constexpr int size()
    {
        return get_size<Types...>::SIZE;
    }

};


#endif
