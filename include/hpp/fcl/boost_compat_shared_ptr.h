#pragma once

#include <memory>

namespace boost
{
    template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    template<typename T, typename... Args>
    inline shared_ptr<T> make_shared(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
