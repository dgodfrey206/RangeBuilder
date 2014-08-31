#include <iostream>
#include <array>

template<int... Indices>
struct indices {
    typedef indices<Indices..., sizeof...(Indices)> next;
};

template<int Start>
struct build_indices {
    typedef typename build_indices<Start - 1>::type::next type;
};

template<>
struct build_indices<0> {
    typedef indices<> type;
};

template<int n>
using build_indices_t = typename build_indices<n>::type;

template<int first, int last, typename T>
struct index_from_range_impl;

template<int first, int last, int... Is>
struct index_from_range_impl<first, last, indices<Is...>>
{
    using type = indices<(Is + first)...>;
};

template<int first, int last>
struct index_from_range
{
    using type = typename index_from_range_impl<first, last, build_indices_t<(last + 1) - first>>::type;
};

template<int first, int last>
using index_from_range_t = typename index_from_range<first, last>::type;

static_assert(std::is_same<index_from_range_t<10, 15>,
              indices<10, 11, 12, 13, 14, 15>>::value, "");

int main()
{
}
