#ifndef META_LIBRARY
#define META_LIBRARY

/*!
 * \brief   Provides meta functionality in a clear and neat way.
 */

#include "MetaLibrary/VariadicIndexing.hpp"
#include "MetaLibrary/VariadicTypedef.hpp"

template <typename DataType, class... Args>
std::tuple<Args...> tupleAssign(DataType value)
{
    return std::make_tuple(Args(value)...);
};

#endif
