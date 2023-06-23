#pragma once
#include <concepts>
#include <algorithm>

#include <cstdint>
#include <array>
#include <utility>
#include <initializer_list>

namespace pi {
template<std::equality_comparable Key, typename Value, std::size_t N>
struct lookup_table {
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<Key, Value>;

    constexpr lookup_table(std::initializer_list<value_type> args)
    {
        std::ranges::copy(args, mappings.begin());
    }

    constexpr auto begin() noexcept { return mappings.begin(); }
    constexpr auto begin() const noexcept { return mappings.begin(); }
    constexpr auto end() noexcept { return mappings.end(); }
    constexpr auto end() const noexcept { return mappings.end(); }

    template<std::equality_comparable_with<Key> AltKey>
    constexpr auto find(const AltKey& key)
    {
        auto matches_key = [&key](const auto& v) { return v.first == key; };
        return std::ranges::find_if(mappings, matches_key);
    }
    template<std::equality_comparable_with<Key> AltKey>
    constexpr auto find(const AltKey& key) const
    {
        auto matches_key = [&key](const auto& v) { return v.first == key; };
        return std::ranges::find_if(mappings, matches_key);
    }
    std::array<std::pair<Key, Value>, N> mappings;
};
}
