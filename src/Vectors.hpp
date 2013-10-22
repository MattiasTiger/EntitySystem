#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <vector>
#include <tuple>
#include <algorithm>
#include <type_traits>

// META-FUNCTIONS
// =======================================================


/* Get the intex to a specific type in a variadic list (first found)
 */

// 2) Recursion, traverse Types
template<typename Wanted, int N, typename First, typename... Types>
struct get_index_helper {
    enum {INDEX = get_index_helper<Wanted, N+1, Types...>::INDEX};
};

// 3) Break when Wanted found in Types and "return" N.
template<typename Wanted, int N, typename... Types>
struct get_index_helper<Wanted, N, Wanted, Types...> {
    enum {INDEX = N};
};

// 1) Interface. Wanted = Type which index we want. Types = all types in order.
template<typename Wanted, typename... Types>
struct get_index {
    enum {INDEX = get_index_helper<Wanted, 0, Types...>::INDEX};
};

//--------------------------------------------------------------------------


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
