#ifndef INCLUDE_GUARD_SCHIFFEVERSENKEN_GLOBALCONF_HPP
#define INCLUDE_GUARD_SCHIFFEVERSENKEN_GLOBALCONF_HPP

#include <string_view>

constexpr struct {
    const std::string_view version = "v1.0.0";
    const bool debugMode = false;
} GlobalConf;

#endif  // INCLUDE_GUARD_SCHIFFEVERSENKEN_GLOBALCONF_HPP
