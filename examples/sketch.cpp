#include <ranges>
#include <algorithm>

#include <cstdlib>
#include <string_view>
#include <string>
#include <iostream>

#include "pi/containers/lookup_table.hpp"

enum class stoplight {
    green, yellow, red
};
namespace utility {
static constexpr pi::lookup_table<stoplight, std::string_view, 3>
stoplight_names {
    { stoplight::green,     "green" },
    { stoplight::yellow,    "yellow" },
    { stoplight::red,       "red" }
};
}
std::string to_string(stoplight val)
{
    return std::string{ utility::stoplight_names.find(val)->second };
}
std::optional<stoplight> from_string(std::string_view name)
{
    namespace ranges = std::ranges;
    auto matches_value = [&name](const auto& v) { return name == v.second; };
    if (const auto result = ranges::find_if(utility::stoplight_names,
                                            matches_value)) {
        return result->first;
    }
    return std::nullopt;
}

int main()
{
    std::cout << to_string(stoplight::green) << " light\n";
    if (const auto light = from_string("yellow")) {
        std::cout << "yellow is a stoplight color!\n";
    }
    else {
        std::cout << "couldn't read yellow as a stoplight color\n";
    }
    return EXIT_SUCCESS;
}
