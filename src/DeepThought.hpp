#pragma once

#include "DeepThoughtError.hpp"
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

    optional<vector<string>>
    lookupQuestion(const string &question) const {
        unordered_map<string, vector<string>>::const_iterator it = _questions.find(question);

        if (it == _questions.end()) {
            return nullopt;
        } else {
            return make_optional(it->second);
        }
    }

    const variant<string, DeepThoughtError>
    getQuestion(const string &input) {
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
                return variant<string, DeepThoughtError>(input.substr(0, idx + 1));
            }
        }

        return variant<string, DeepThoughtError>(in_place_type<DeepThoughtError>, DeepThoughtError::Type::EMPTY_INPUT);
    }

    const variant<vector<string>, DeepThoughtError>
    getAnswers(const string &input) {
        size_t left = 0;
        bool inQuotes;
        vector<string> answers;

        string trimmedInput = input.substr(
            input.find_first_not_of("\t\n "),
            input.find_last_not_of("\t\n ") - input.find_first_not_of("\t\n ") + 1
        );
        if (trimmedInput[0] != '"') {
            return variant<vector<string>, DeepThoughtError>(
                in_place_type<DeepThoughtError>,
                DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES
            );
        }

        inQuotes = true;

        for (size_t idx = 1; idx < trimmedInput.size(); ++idx) {
            if (trimmedInput[idx] == '"') {
                if (inQuotes) {
                    if ((idx - left - 1) > 255) {
                        return variant<vector<string>, DeepThoughtError>(
                            in_place_type<DeepThoughtError>,
                            DeepThoughtError::Type::ANSWER_TOO_LONG
                        );
                    }
                    answers.push_back(trimmedInput.substr(left + 1, idx - left - 1));
                    inQuotes = false;
                } else {
                    left = idx;
                    inQuotes = true;
                }
            } else if (!inQuotes && string("\t\n ").find_first_of(trimmedInput[idx]) == string::npos) {
                return variant<vector<string>, DeepThoughtError>(
                    in_place_type<DeepThoughtError>,
                    DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES
                );
            }
        }

        if (inQuotes) {
            return variant<vector<string>, DeepThoughtError>(
                in_place_type<DeepThoughtError>,
                DeepThoughtError::Type::UNCLOSED_QUOTES
            );
        }

        return variant<vector<string>, DeepThoughtError>(in_place_type<vector<string>>, answers);
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
        variant<string, DeepThoughtError> questionVariant = getQuestion(input);

        if (holds_alternative<DeepThoughtError>(questionVariant)) {
            DeepThoughtError &err = get<DeepThoughtError>(questionVariant).addToStackTrace("could not parse question");
            return variant<string, DeepThoughtError>(std::move(err));
        }

        const string &question = get<string>(questionVariant);
        if (input.find_first_not_of("\t\n ", question.size()) == string::npos) {
            optional<vector<string>> answers = lookupQuestion(question);
            if (answers.has_value()) {
                stringstream stream;
                for (string &answer : answers.value()) {
                    stream << answer << '\n';
                }
                return variant<string, DeepThoughtError>(stream.str());
            } else {
                return variant<string, DeepThoughtError>("The answer to life, universe and everything is 42.\n");
            }

        } else {
            variant<vector<string>, DeepThoughtError> result = getAnswers(input.substr(question.size()));

            if (holds_alternative<DeepThoughtError>(result)) {
                DeepThoughtError &err = get<DeepThoughtError>(result).addToStackTrace("could not parse answers");
                return variant<string, DeepThoughtError>(std::move(err));
            }

            _questions[question] = get<vector<string>>(result);
        }
        return variant<string, DeepThoughtError>("");
    }
};
