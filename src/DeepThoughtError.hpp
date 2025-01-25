#include <optional>
#include <string>
#include <unordered_map>

using namespace std;

class DeepThoughtError {

  public:
    // `enum class` prevents implicit conversions to integer types.
    enum class Type {
        QUESTION_IN_QUOTES,
        QUESTION_TOO_LONG,
        EMPTY_INPUT,
        UNCLOSED_QUOTES,
        ANSWER_TOO_LONG,
        ANSWER_WITHOUT_QUOTES,
    };

    // `explicit` keyword prevents implicit conversions, ensuring it can only be
    // used for direct initialization.
    explicit DeepThoughtError(DeepThoughtError::Type errorType) : _errorType(errorType) {}

    ~DeepThoughtError() = default;

    DeepThoughtError(DeepThoughtError &&rhs) noexcept = default;
    DeepThoughtError &operator=(DeepThoughtError &&rhs) noexcept = default;

    // Delete all other constructors to ensure each `DeepThoughtError` is unique
    // and immutable.
    DeepThoughtError() = delete;
    DeepThoughtError(const DeepThoughtError &rhs) = delete;
    DeepThoughtError &operator=(const DeepThoughtError &rhs) = delete;

    const string &
    getMessage() const {
        if (!_errorMessages) {
            initializeErrorMessages();
        }

        if (_stackTrace.empty()) {
            return _errorMessages->at(_errorType);
        } else {
            return _stackTrace;
        }
    }

    Type
    getType() const {
        return _errorType;
    }

    DeepThoughtError &
    addToStackTrace(const std::string &message) {
        if (_stackTrace.empty()) {
            _stackTrace = message + ": " + getMessage();
            return *this;
        }

        _stackTrace = _stackTrace + ": " + message;
        return *this;
    }

  private:
    Type _errorType;
    static optional<unordered_map<Type, string>> _errorMessages;
    string _stackTrace;

    void
    initializeErrorMessages() const {
        _errorMessages.emplace(unordered_map<Type, string>{
            {Type::QUESTION_IN_QUOTES,      "question can not be in quotes"                },
            {Type::QUESTION_TOO_LONG,       "no question found in the first 255 characters"},
            {Type::EMPTY_INPUT,             "input can not be empty"                       },
            {Type::UNCLOSED_QUOTES,         "quotes sequences must be closed"              },
            {Type::ANSWER_TOO_LONG,         "answers can not exceed 255 characters"        },
            {Type::ANSWER_WITHOUT_QUOTES,   "answers must be enclosed in quotes"           },
        });
    }
};
