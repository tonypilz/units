#pragma once

namespace unit {

template <typename Unit, typename MagnitudeRepresentation = double>
class Quantity {
    template <typename, typename>
    friend class Quantity;

   public:
    using unit = Unit;
    using magnitude_type = MagnitudeRepresentation;
    using classtype = Quantity<unit, magnitude_type>;

    constexpr explicit Quantity() : m_magnitude(0) {}
    constexpr explicit Quantity(magnitude_type const& v) : m_magnitude(v) {}

    constexpr Quantity(classtype const& v) = default;

    template <typename U, typename R>
    constexpr Quantity(Quantity<U, R> const& v) : m_magnitude(v.m_magnitude) {}

    classtype& operator=(classtype const& v) = default;

    constexpr magnitude_type const& magnitude() const { return m_magnitude; }
    void setMagnitude(classtype const& v) { m_magnitude = v.m_magnitude; }

   private:
    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator+=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator-=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator*=(Quantity<U, L>&, Quantity<U, R> const&);

    template <typename U, typename L, typename R>
    friend constexpr Quantity<U, L>& operator/=(Quantity<U, L>&, Quantity<U, R> const&);

    magnitude_type m_magnitude;
};
}
