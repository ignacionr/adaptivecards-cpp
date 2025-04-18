#include <cassert>
#include <memory>
#include <print>
#include <string>
#include <variant>
#include <vector>
#include <string_view> // For string_view
#include <stdexcept>   // For potential exceptions

#include <ac.hpp>      // Uses vector<json_t>
#include <ac_glz.hpp>  // Only contains meta definitions now
#include <glaze/glaze.hpp>
#include <glaze/json/json_t.hpp> // Include for json_t usage

constexpr auto sample_adaptivecard_0 {
    R"({
        "type": "AdaptiveCard",
        "version": "1.3",
        "body": []
    })"
};

constexpr auto sample_adaptivecard {
    R"({
        "type": "AdaptiveCard",
        "version": "1.3",
        "body": [
            {
                "type": "TextBlock",
                "text": "Hello, Adaptive Cards!",
                "size": "Large",
                "weight": "Bolder"
            },
            {
                "type": "Image",
                "url": "https://adaptivecards.io/content/cats/1.png",
                "size": "Medium"
            }
        ]
    })"
};

void check_0(const ac::AdaptiveCard& card) {
    assert(card.type == "AdaptiveCard");
    assert(card.version == "1.3");
    assert(card.body.empty());
}

void check_card(const ac::AdaptiveCard& card) {
    assert(card.type == "AdaptiveCard");
    assert(card.version == "1.3");
    assert(card.body.size() == 2);

    // Check TextBlock
    auto textBlock = std::dynamic_pointer_cast<ac::TextBlock>(card.body[0]);
    assert(textBlock != nullptr);
    assert(textBlock->type == "TextBlock");
    assert(textBlock->text == "Hello, Adaptive Cards!");
    assert(textBlock->size == "Large");
    assert(textBlock->weight == "Bolder");
    // Check Image
    auto image = std::dynamic_pointer_cast<ac::Image>(card.body[1]);
    assert(image != nullptr);
    assert(image->type == "Image");
    assert(image->url == "https://adaptivecards.io/content/cats/1.png");
    assert(image->size == "Medium");
}


int main() {
    std::println("--- Testing Card 0 ---");
    std::println("Input JSON:\n{}", sample_adaptivecard_0);
    auto card0_result = glz::read_json<ac::AdaptiveCard>(sample_adaptivecard_0);
    if (card0_result) {
        check_0(*card0_result);
        std::println("AdaptiveCard 0 check passed ✅");
    }
    else {
        std::println("Unable to parse Card 0: {}", glz::format_error(card0_result.error(), sample_adaptivecard_0));
        return 1;
    }

    std::println("\n--- Testing Card 1 ---");
    std::println("Input JSON:\n{}", sample_adaptivecard);
    auto card1_result = glz::read_json<ac::AdaptiveCard>(sample_adaptivecard);
     if (card1_result) {
        try { // Add try-catch around check_card if .as<T> might throw
             check_card(*card1_result);
             std::println("AdaptiveCard 1 check passed ✅");
        } catch (const std::exception& e) {
            std::println("Runtime error during check_card: {}", e.what());
             return 1;
        } catch (...) {
            std::println("Unknown runtime error during check_card.");
            return 1;
        }
    }
    else {
        std::println("Unable to parse Card 1: {}", glz::format_error(card1_result.error(), sample_adaptivecard));
        return 1;
    }

    std::println("\nAll checks passed!");
    return 0;
}