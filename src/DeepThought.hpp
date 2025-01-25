#pragma once

#include "DeepThoughtError.hpp"
#include <cctype>
#include <cstddef>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

using namespace std;

class DeepThought {

  private:
    unordered_map<string, vector<string>> _questions;

    const string
    lookupQuestion(const string &question) const {
        unordered_map<string, vector<string>>::const_iterator it = _questions.find(question);

        if (it == _questions.end()) {
            return "The answer to life, universe and everything is 42.\n";
        }

        stringstream stream;
        for (const string &answer : it->second) {
            stream << answer << '\n';
        }

        return stream.str();
    }

    const variant<string, DeepThoughtError>
    parseQuestion(const string &input) {
        for (size_t idx = 0; idx < input.size(); ++idx) {

            if (input[idx] == '"') {
                return DeepThoughtError(DeepThoughtError::Type::QUESTION_IN_QUOTES);
            } else if (idx > 255) {
                return DeepThoughtError(DeepThoughtError::Type::QUESTION_TOO_LONG);
            } else if (input[idx] == '?') {
                return input.substr(0, idx + 1);
            }
        }

        return DeepThoughtError(DeepThoughtError::Type::EMPTY_INPUT);
    }

    const variant<vector<string>, DeepThoughtError>
    parseAnswers(const string &input) {
        size_t left = 0;
        bool inQuotes = false;
        vector<string> answers;

        for (size_t idx = 0; idx < input.size(); ++idx) {
            if (input[idx] == '"') {
                if (inQuotes) {
                    if ((idx - left - 1) > 255) {
                        return DeepThoughtError(DeepThoughtError::Type::ANSWER_TOO_LONG);
                    }
                    answers.push_back(input.substr(left + 1, idx - left - 1));
                } else {
                    left = idx;
                }
                inQuotes = !inQuotes;
            } else if (!inQuotes && !isspace(input[idx])) {
                return DeepThoughtError(DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES);
            }
        }

        if (inQuotes) {
            return DeepThoughtError(DeepThoughtError::Type::UNCLOSED_QUOTES);
        }

        return answers;
    }

  public:
    DeepThought() = default;
    ~DeepThought() = default;

    DeepThought(const DeepThought &) = delete;
    DeepThought &operator=(const DeepThought &) = delete;
    DeepThought(DeepThought &&) = delete;
    DeepThought &operator=(DeepThought &&) = delete;

    const variant<string, DeepThoughtError>
    processInput(const string &input) {
        variant<string, DeepThoughtError> questionVariant = parseQuestion(input);

        if (holds_alternative<DeepThoughtError>(questionVariant)) {
            DeepThoughtError &err = get<DeepThoughtError>(questionVariant).addToStackTrace("could not parse question");
            return std::move(err);
        }

        const string &question = get<string>(questionVariant);
        if (input.find_first_not_of("\t\n ", question.size()) == string::npos) {
            return lookupQuestion(question);
        } else {
            variant<vector<string>, DeepThoughtError> result = parseAnswers(input.substr(question.size()));

            if (holds_alternative<DeepThoughtError>(result)) {
                DeepThoughtError &err = get<DeepThoughtError>(result).addToStackTrace("could not parse answers");
                return std::move(err);
            }

            _questions[question] = get<vector<string>>(result);
        }
        return "";
    }
};
