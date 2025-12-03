// boost/noncopyable.hpp
#pragma once

namespace boost {

    class noncopyable {
    protected:
        // C++20/23-friendly: trivial, constexpr, noexcept
        constexpr noncopyable() noexcept = default;
        ~noncopyable() = default;

        // Non-copyable
        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;

        // Also make it non-movable explicitly (copy-delete already implies this,
        // but being explicit is clearer)
        noncopyable(noncopyable&&) = delete;
        noncopyable& operator=(noncopyable&&) = delete;
    };

} // namespace boost

