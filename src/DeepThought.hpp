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

#undef DEEPTHOUGHT_USAGE
#define DEEPTHOUGHT_USAGE                                                                                              \
    "\n\
Usage:\n\
    <question?> \"<answer_0>\" \"<answer_1>\" ... \"<answer_n>\"\n\
        - Stores <question?> along with all answers\n\
    <question?>\n\
        - Looks up <question?>\n\
\n\
Constraints:\n\
    - A question must not contain double quotes.\n\
    - A question must be followed by a single question mark.\n\
    - A question must not exceed 255 characters.\n\
    - An answer must be within double quotes.\n\
    - An answer must not exceed 255 characters.\n\
    - Double quoted sequences must be closed (duh).\n\n\
"

// Question-and-answer system. `DeepThought` allows storing questions along with answers to retrieve them later.
// .
// The `processInput` public method may be used to parse user input and separate simple lookups from new questions.
// .
// User input must adhere to the following constraints:
// .
// Formatting:
//     - New question: `<question?> \"<answer_0>\" \"<answer_1>\" ... \"<answer_n>\"`
//     - Lookup: `<question?>`
//
// .
// Constraints:
//    - A question must not contain double quotes.
//    - A question must be followed by a single question mark.
//    - A question must not exceed 255 characters.
//    - An answer must be within double quotes.
//    - An answer must not exceed 255 characters.
//    - Double quoted sequences must be closed.
class DeepThought {

  private:
    unordered_map<string, vector<string>> _questions;

    // Looks up `question` in `_questions`, returning either the retrieved value or a default answer.
    const string lookupQuestion(const string &question) const {
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

    // Parses `input` for a correctly formatted question according to DeepThought's usage constraints.
    const variant<string, DeepThoughtError> parseQuestion(const string &input) {
        if (input.size() == 0) {
            return DeepThoughtError(DeepThoughtError::Type::EMPTY_INPUT);
        }

        for (size_t idx = 0; idx < input.size(); ++idx) {

            if (input[idx] == '"') {
                return DeepThoughtError(DeepThoughtError::Type::QUESTION_IN_QUOTES);
            } else if (idx > 255) {
                return DeepThoughtError(DeepThoughtError::Type::QUESTION_TOO_LONG);
            } else if (input[idx] == '?') {
                return input.substr(0, idx + 1);
            }
        }

        return DeepThoughtError(DeepThoughtError::Type::NO_QUESTION);
    }

    // Parses `input` for correctly formatted answers according to DeepThought's usage constraints.
    const variant<vector<string>, DeepThoughtError> parseAnswers(const string &input) {
        size_t left = 0;
        bool inQuotes = false;
        vector<string> answers;

        for (size_t idx = 0; idx < input.size(); ++idx) {
            char c = input[idx];

            if (inQuotes) {
                if ((idx - left - 1) > 255) {
                    return DeepThoughtError(DeepThoughtError::Type::ANSWER_TOO_LONG);
                }

                if (c == '"') {
                    answers.push_back(input.substr(left + 1, idx - left - 1));
                    inQuotes = false;
                }
            } else {
                if (c == '"') {
                    left = idx;
                    inQuotes = true;
                } else if (!isspace(c)) {
                    return DeepThoughtError(DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES);
                }
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

    // Processes `input`, deciding whether the user is trying to store a new question, look up the answers to a
    // question, or just smashed their head on the keyboard.
    // .
    // On lookup success, returns a string containing all answers to the question asked.
    // On question storing success, returns a string confirming success.
    // .
    // On failure, returns a `DeepThoughtError` appropriately set type.
    const variant<string, DeepThoughtError> processInput(const string &input) {
        variant<string, DeepThoughtError> questionVariant = parseQuestion(input);

        if (holds_alternative<DeepThoughtError>(questionVariant)) {
            DeepThoughtError &err = get<DeepThoughtError>(questionVariant).addToStackTrace("Could not parse question");
            return std::move(err);
        }

        const string &question = get<string>(questionVariant);
        if (input.find_first_not_of("\t\n ", question.size()) == string::npos) {
            return lookupQuestion(question);
        } else {
            variant<vector<string>, DeepThoughtError> result = parseAnswers(input.substr(question.size()));
            if (holds_alternative<DeepThoughtError>(result)) {
                DeepThoughtError &err = get<DeepThoughtError>(result).addToStackTrace("Could not parse answers");
                return std::move(err);
            }

            _questions[question] = get<vector<string>>(result);
        }
        return "Successfully stored new question '" + question + "'\n";
    }

    // Returns the usage instructions and constraints for DeepThought.
    const string usage() const { return DEEPTHOUGHT_USAGE; }
};
