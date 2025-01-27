#include <optional>
#include <string>
#include <unordered_map>

using std::string, std::unordered_map, std::optional;

// Error class for `DeepThought`, containing all possible error cases and their corresponding base error messages.
// Additionally, the `addToStackTrace` public method may be used to prepend more information to `DeepThoughtError`'s
// error message.
//
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
        NO_QUESTION,
    };

    explicit DeepThoughtError(DeepThoughtError::Type errorType) : _errorType(errorType) {}

    ~DeepThoughtError() = default;

    DeepThoughtError(DeepThoughtError &&rhs) noexcept = default;
    DeepThoughtError &operator=(DeepThoughtError &&rhs) noexcept = default;

    DeepThoughtError() = delete;
    DeepThoughtError(const DeepThoughtError &rhs) = delete;
    DeepThoughtError &operator=(const DeepThoughtError &rhs) = delete;

    // Returns the `DeepThoughtError` instance's message, initializing the static `_errorMessages` variable if necessary.
    const string &getMessage() const {
        if (!_errorMessages) {
            initializeErrorMessages();
        }

        if (_stackTrace.empty()) {
            return _errorMessages->at(_errorType);
        } else {
            return _stackTrace;
        }
    }

    // Returns the `DeepThoughtError`'s error's type.
    Type getType() const { return _errorType; }

    // Prepends an additional message to the `DeepThoughtError`'s stack trace.
    // .
    // Example:
    // `DeepThoughtError err = DeepThoughtError(DeepThoughtError::Type::EMPTY_INPUT)`
    // `cout << err.getMessage()`
    // `Input can not be empty`
    // `err.addToStackTrace("Could not parse question")`
    // `cout << err.getMessage()`
    // `Could not parse question: Input can not be empty`
    DeepThoughtError &addToStackTrace(const std::string &message) {
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

    void initializeErrorMessages() const {
        _errorMessages.emplace(unordered_map<Type, string>{
            {Type::QUESTION_IN_QUOTES,    "Question can not be in quotes"                },
            {Type::QUESTION_TOO_LONG,     "No question found in the first 255 characters"},
            {Type::EMPTY_INPUT,           "Input can not be empty"                       },
            {Type::UNCLOSED_QUOTES,       "Quoted sequences must be closed"              },
            {Type::ANSWER_TOO_LONG,       "Answers can not exceed 255 characters"        },
            {Type::ANSWER_WITHOUT_QUOTES, "Answers must be enclosed in quotes"           },
            {Type::NO_QUESTION,           "No question found in input"                   },
        });
    }
};
