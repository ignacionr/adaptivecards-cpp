#include <ac.hpp>
#include <ac_glz.hpp>

void ac::AdaptiveCard::read_body(const glz::json_t& source)
{
    // Check if the source is an array
    if (!source.is_array()) {
        throw std::runtime_error("Expected an array for body");
    }
    // Clear the existing body
    body.clear();
    // Parse the array elements
    for (const auto& element : source.get_array()) {
        if (element.is_object()) {
            // Check the type of the element
            if (!element.contains("type")) {
                throw std::runtime_error("Missing 'type' field in element");
            }
            auto const &type = element["type"].get_string();
            if (type == TextBlock::type_name) {
                body.push_back(std::make_shared<TextBlock>(glz::read_json<TextBlock>(element).value()));
            } else if (type == Image::type_name) {
                body.push_back(std::make_shared<Image>(glz::read_json<Image>(element).value()));
            } else {
                throw std::runtime_error(std::format("Unknown element type: {}", type));
            }
        }
    }
}

