#include <optional>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class DeepThoughtError {

  public:
    enum class Type {
        QUESTION_IN_QUOTES,
        QUESTION_TOO_LONG,
        LAST,
    };

    explicit DeepThoughtError(Type errorType) : _errorType(errorType) {
    }

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
            {Type::QUESTION_IN_QUOTES, "question should not be in quotes"             },
            {Type::QUESTION_TOO_LONG,  "no question found in the first 255 characters"},
        });
    }
};
