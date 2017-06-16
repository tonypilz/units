#pragma once

#include <ratio>

namespace unit {
namespace helper {

using Index = unsigned int;

template<Index n, int Arg, int... Args>
struct NthElement{
    static constexpr int value() { return NthElement<n-1,Args...>::value(); }
};



template<int Arg, int... Args>
struct NthElement<0u, Arg, Args...>{
    static constexpr int value(){ return Arg;}
};





template<typename ratioIn, typename ratioOut, typename T >
constexpr T rescale(T const& v)
{
    using r = std::ratio_divide<ratioIn,ratioOut>;
    return v*T{r::num}/T{r::den};
}

template<typename ratioIn, typename T >
constexpr T rescaleTo1(T const& v)
{
    return rescale<ratioIn,std::ratio<1>,T>(v);
}
}




template<typename T> constexpr T femto(T const& v) { return helper::rescaleTo1<std::femto>(v); }
template<typename T> constexpr T pico(T const& v) { return helper::rescaleTo1<std::pico>(v); }
template<typename T> constexpr T nano(T const& v) { return helper::rescaleTo1<std::nano>(v); }
template<typename T> constexpr T micro(T const& v) { return helper::rescaleTo1<std::micro>(v); }
template<typename T> constexpr T milli(T const& v) { return helper::rescaleTo1<std::milli>(v); }
template<typename T> constexpr T centi(T const& v) { return helper::rescaleTo1<std::centi>(v); }
template<typename T> constexpr T deci(T const& v) { return helper::rescaleTo1<std::deci>(v); }
template<typename T> constexpr T deca(T const& v) { return helper::rescaleTo1<std::deca>(v); }
template<typename T> constexpr T hecto(T const& v) { return helper::rescaleTo1<std::hecto>(v); }
template<typename T> constexpr T kilo(T const& v) { return helper::rescaleTo1<std::kilo>(v); }
template<typename T> constexpr T mega(T const& v) { return helper::rescaleTo1<std::mega>(v); }
template<typename T> constexpr T giga(T const& v) { return helper::rescaleTo1<std::giga>(v); }
template<typename T> constexpr T tera(T const& v) { return helper::rescaleTo1<std::tera>(v); }
template<typename T> constexpr T peta(T const& v) { return helper::rescaleTo1<std::peta>(v); }




} //helper



