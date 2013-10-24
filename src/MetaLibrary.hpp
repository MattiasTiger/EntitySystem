#ifndef META_LIBRARY
#define META_LIBRARY

/*!
 * \brief   Provides meta functionality in a clear and neat way.
 */

#include "MetaLibrary/VariadicUtilities.hpp"
#include "MetaLibrary/VariadicIndexing.hpp"
#include "MetaLibrary/VariadicTypedef.hpp"
#include "MetaLibrary/MultiContainer.hpp"

/*!
 *  \brief  Check if a std::tuple<> have zero parameters.
 */
template<int size>
struct isTupleEmpty_ {
    static const bool value = false;
};
template<>
struct isTupleEmpty_<0> {
    static const bool value = true;
};
template<typename tuple>
struct isTupleEmpty {
    static const bool value = isTupleEmpty_<std::tuple_size<tuple>::value>::value;
};

/*!
 *  \brief      If control structures.
 *  \details    * IF<condition, Then>
 *              * IF<condition, Then, Else>
 */

template <bool condition, typename Then, typename Else>
struct IF {
    typedef Then RETURN;
};
template <typename Then, typename Else>
struct IF<false, Then, Else> {
    typedef Else RETURN;
};
template <bool condition, typename Then>
struct IF<condition, Then, void> {
    typedef Then RETURN;
};
template <typename Then>
struct IF<false, Then, void>{
    typedef void RETURN;
};

struct NOPE {};

#endif
