#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <utility>

#include <glaze/glaze.hpp>
#include <glaze/json.hpp>
#include <glaze/json/read.hpp>
#include <glaze/json/json_t.hpp>

#include "ac.hpp"

namespace glz {

    template <>
    struct meta<ac::TextBlock> {
        using T = ac::TextBlock;
        static constexpr auto value = object(
            "type", &T::type,
            "text", &T::text,
            "size", &T::size,
            "weight", &T::weight
        );
        static constexpr std::string_view name = "TextBlock";
    };

    template <>
    struct meta<ac::Image> {
        using T = ac::Image;
        static constexpr auto value = object(
            "type", &T::type,
            "url", &T::url,
            "size", custom<&T::read_size, nullptr>
        );
        static constexpr std::string_view name = "Image";
    };

    template <>
    struct meta<ac::AdaptiveCard> {
        using T = ac::AdaptiveCard;
        static constexpr auto value = object(
            "type", &T::type,
            "version", &T::version,
            "body", custom<&T::read_body, nullptr>
        );
        static constexpr std::string_view name = "AdaptiveCard";
    };

} // namespace glz