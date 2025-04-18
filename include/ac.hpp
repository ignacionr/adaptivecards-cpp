#pragma once

#include <optional>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <glaze/glaze.hpp>
#include <glaze/json.hpp>
#include <glaze/json/read.hpp>
#include <glaze/json/json_t.hpp>

using namespace std::string_literals;

namespace ac {
    using uri_t = std::string;

    struct Element {
        virtual ~Element() = default;
        std::string type;
    };

    struct TextBlock: public Element {
        static constexpr auto type_name = "TextBlock";
        std::string text;
        std::optional<std::string> size;
        std::optional<std::string> weight;
    };

    struct Image: public Element {
        static constexpr auto type_name = "Image";
        uri_t url;
        std::optional<std::string> size;
    };


    struct AdaptiveCard {
        std::string type;
        std::string version;
        // Keep using json_t for body for simpler parsing
        void read_body(const glz::json_t& source);
        auto write_body() const {
            throw std::runtime_error("write_body not implemented");
        }
        std::vector<std::shared_ptr<Element>> body;
    };

} // namespace ac