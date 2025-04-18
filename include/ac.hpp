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

    struct ImageSize {
        ImageSize(auto value): value_{value} {}
        ImageSize& operator=(std::string_view &src) {
            value_ = src;
            return *this;
        }
        bool operator==(ImageSize const &other) const = default;
        operator std::string const&() const { return value_; }
    private:
        std::string value_;
    };

    struct Image: public Element {
        static constexpr auto type_name = "Image";
        uri_t url;
        std::optional<std::string> altText;
        std::optional<std::string> backgroundColor;
        std::optional<ImageSize> size;
        void read_size(std::string_view value) {
            size = value;
        }
    };


    struct AdaptiveCard {
        std::string type;
        std::string version;
        // Keep using json_t for body for simpler parsing
        void read_body(const glz::json_t& source);
        std::vector<std::shared_ptr<Element>> body;
    };

} // namespace ac