#pragma once

#include <optional>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <glaze/json/json_t.hpp> // Include for json_t used below

namespace ac {
    using uri_t = std::string;

    struct Element {
        virtual ~Element() = default;
        std::string type;
    };

    using CardElementOriginal = std::variant<
        std::shared_ptr<struct TextBlock>,
        std::shared_ptr<struct Image>
    >;

    struct AdaptiveCard {
        std::string type;
        std::string version;
        // Keep using json_t for body for simpler parsing
        std::vector<glz::json_t> body;
    };

    struct TextBlock: public Element {
        static constexpr auto type_name = "TextBlock";
        std::string text;
        // USE OPTIONAL STRING
        std::optional<std::string> size;
        std::optional<std::string> weight;
    };

    struct Image: public Element {
        static constexpr auto type_name = "Image";
        uri_t url;
        // USE OPTIONAL STRING
        std::optional<std::string> size;
    };
} // namespace ac