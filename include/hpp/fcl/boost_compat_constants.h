#pragma once

#include <numbers>

namespace boost {
    namespace math {
        namespace constants {

            template<typename T>
            constexpr T pi() noexcept {
                return std::numbers::pi_v<T>;
            }

            // Add more if the code uses them:
            // template<typename T>
            // constexpr T two_pi() noexcept { return std::numbers::pi_v<T> * T(2); }

        } // namespace constants
    } // namespace math
} // namespace boost
