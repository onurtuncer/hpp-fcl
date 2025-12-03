#pragma once 

#include <cmath>      // std::isnan, std::isfinite, std::isinf
#include <type_traits>

namespace boost {
    namespace math {

        template <typename T>
        constexpr bool isnan(T x) noexcept
        {
            // Boost allowed integral inputs; std::isnan does not.
            if constexpr (std::is_integral_v<T>)
                return false;
            else
                return std::isnan(x);
        }

        template <typename T>
        constexpr bool isfinite(T x) noexcept
        {
            if constexpr (std::is_integral_v<T>)
                return true;
            else
                return std::isfinite(x);
        }

        template <typename T>
        constexpr bool isinf(T x) noexcept
        {
            if constexpr (std::is_integral_v<T>)
                return false;
            else
                return std::isinf(x);
        }

    } // namespace math
} // namespace boost