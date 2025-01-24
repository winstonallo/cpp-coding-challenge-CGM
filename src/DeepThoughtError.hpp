#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

using namespace std;

class DeepThoughtError {

  public:
    enum class Type {
        QUESTION_IN_QUOTES,
        QUESTION_TOO_LONG,
        EMPTY_INPUT,
        MULTIPLE_QUESTION_MARKS,
        UNCLOSED_QUOTES,
        ANSWER_TOO_LONG,
        ANSWER_WITHOUT_QUOTES,
    };

    explicit DeepThoughtError(Type errorType) : _errorType(errorType) {}

    const string &
    getMessage() const {
        if (!_errorMessages) {
            initializeErrorMessages();
        }

        return _errorMessages->at(_errorType);
    }

  private:
    Type _errorType;
    static optional<unordered_map<Type, string>> _errorMessages;

    void
    initializeErrorMessages() const {
        cout << "initializing error messages" << endl;
        _errorMessages.emplace(unordered_map<Type, string>{
            {Type::QUESTION_IN_QUOTES,      "question can not be in quotes"                },
            {Type::QUESTION_TOO_LONG,       "no question found in the first 255 characters"},
            {Type::EMPTY_INPUT,             "input can not be empty"                       },
            {Type::MULTIPLE_QUESTION_MARKS, "input can not have more than one question"    },
            {Type::UNCLOSED_QUOTES,         "quotes sequences must be closed"              },
            {Type::ANSWER_TOO_LONG,         "answers can not exceed 255 characters"        },
            {Type::ANSWER_WITHOUT_QUOTES,   "answers must be enclosed in quotes"           },
        });
    }
};
