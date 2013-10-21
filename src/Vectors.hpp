#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <vector>
#include <tuple>
#include <algorithm>
#include <type_traits>

// META-FUNCTIONS
// =======================================================

// indices are a classic
template< std::size_t... Ns >
struct indices
{
    using next = indices< Ns..., sizeof...( Ns ) >;
};

template< std::size_t N >
struct make_indices
{
    using type = typename make_indices< N - 1 >::type::next;
};

template<>
struct make_indices< 0 >
{
    using type = indices<>;
};

// we need something to find a type's index within a list of types
template<typename T, typename U, std::size_t=0>
struct index {};

template<typename T, typename... Us, std::size_t N>
struct index<T,std::tuple<T,Us...>,N>
: std::integral_constant<std::size_t, N> {};

template<typename T, typename U, typename... Us, std::size_t N>
struct index<T,std::tuple<U,Us...>,N>
: index<T,std::tuple<Us...>,N+1> {};

// we need a way to remove duplicate types from a list of types
template<typename T,typename I=void> struct unique;

// step 1: generate indices
template<typename... Ts>
struct unique< std::tuple<Ts...>, void >
: unique< std::tuple<Ts...>, typename make_indices<sizeof...(Ts)>::type >
{
};

// step 2: remove duplicates. Note: No recursion here!
template<typename... Ts, std::size_t... Is>
struct unique< std::tuple<Ts...>, indices<Is...> >
{
    using type = decltype( std::tuple_cat( std::declval<
        typename std::conditional<index<Ts,std::tuple<Ts...>>::value==Is,std::tuple<Ts>,std::tuple<>>::type
>()... ) );
};

// a helper to turn Ts... into std::vector<Ts>...
template<typename> struct vectorize;

template<typename... Ts>
struct vectorize<std::tuple<Ts...>>
{
    using type = std::tuple< std::vector<Ts>... >;
};

//===========================================================================

template<typename... Types>
class Vectors
{
public:
    template<typename Type>
    std::vector<Type>& get() {
        return getVector<Type>();
    }
private:
    using VectorMap = typename vectorize<typename unique<std::tuple<Types...>>::type>::type;
    VectorMap vectors;

    // Getter to simplify extraction from ComponentMap
    template<typename T>
    decltype(std::get<index<T,typename unique<std::tuple<Types...> >::type>::value>(vectors))
    getVector()
    {
        return std::get<index<T,typename unique<std::tuple<Types...> >::type>::value>(vectors);
    }
};


#endif
