#include <iostream>
#include <optional>
#include <ostream>
#include <unordered_map>
#include <vector>

class DeepThought {

  private:
    std::unordered_map<std::string, std::vector<std::string>> _questions;

    std::optional<std::vector<std::string>>
    lookup(const std::string &question) const {
        std::unordered_map<std::string, std::vector<std::string>>::const_iterator it = _questions.find(question);

        if (it == _questions.end()) {
            return std::nullopt;
        } else {
            return std::make_optional(it->second);
        }
    }

  public:
    DeepThought() = default;
    ~DeepThought() = default;

    DeepThought(const DeepThought &) = delete;
    DeepThought &operator=(const DeepThought &) = delete;
    DeepThought(DeepThought &&) = delete;
    DeepThought &operator=(DeepThought &&) = delete;

    const void
    processInput(const std::string &input) {
        struct QuotesPos {
            int left = -1, right = -1;
        };

        for (int idx = 0; idx < input.size(); ++idx) {

        }
    }
};

int
main() {

    while (true) {
        std::string input;
        input.reserve(512);
        std::cout << "deepthought> ";
        std::getline(std::cin, input);
    }
}

