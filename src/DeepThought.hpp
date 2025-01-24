#pragma once

#include "DeepThoughtError.hpp"
#include <string>
#include <utility>
#include <variant>
#include <vector>

using namespace std;

class DeepThought {

  private:
    unordered_map<string, vector<string>> _questions;

    optional<vector<string>>
    _lookupQuestion(const string &question) const {
        unordered_map<string, vector<string>>::const_iterator it = _questions.find(question);

        if (it == _questions.end()) {
            return nullopt;
        } else {
            return make_optional(it->second);
        }
    }

    const variant<string, DeepThoughtError>
    _getQuestion(const string &input) {
        for (size_t idx = 0; idx < input.size(); ++idx) {

            if (input[idx] == '"') {
                return variant<string, DeepThoughtError>(
                    in_place_type<DeepThoughtError>,
                    DeepThoughtError::Type::QUESTION_IN_QUOTES
                );
            } else if (idx > 255) {
                return variant<string, DeepThoughtError>(
                    in_place_type<DeepThoughtError>,
                    DeepThoughtError::Type::QUESTION_TOO_LONG
                );
            } else if (input[idx] == '?') {
                return variant<string, DeepThoughtError>(input.substr(0, idx));
            }
        }

        return variant<string, DeepThoughtError>(
            in_place_type<DeepThoughtError>,
            DeepThoughtError::Type::QUESTION_IN_QUOTES
        );
    }

  public:
    DeepThought() = default;
    ~DeepThought() = default;

    DeepThought(const DeepThought &) = delete;
    DeepThought &operator=(const DeepThought &) = delete;
    DeepThought(DeepThought &&) = delete;
    DeepThought &operator=(DeepThought &&) = delete;

    const variant<bool, DeepThoughtError>
    processInput(const string &input) {
        variant<string, DeepThoughtError> questionVariant = _getQuestion(input);

        if (holds_alternative<DeepThoughtError>(questionVariant)) {
            DeepThoughtError &err = get<DeepThoughtError>(questionVariant).addToStackTrace("could not parse question");
            return variant<bool, DeepThoughtError>(std::move(err));
        }

        const string &question = get<string>(questionVariant);

        optional<vector<string>> answers = _lookupQuestion(question);
        if (answers.has_value()) {
            for (string &answer : answers.value()) {
                cout << answer << '\n';
            }
        } else {
            cout << "The answer to life, universe and everything is 42." << '\n';
        }

        return variant<bool, DeepThoughtError>(true);
    }
};
