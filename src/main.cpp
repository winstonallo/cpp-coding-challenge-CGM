#include "DeepThought.hpp"
#include <iostream>
#include <variant>

using namespace std;

int
main() {
    DeepThought deepThought;

    variant<string, DeepThoughtError> res1 = deepThought.processInput("");

    if (holds_alternative<DeepThoughtError>(res1)) {
        DeepThoughtError &err = get<DeepThoughtError>(res1);
        cerr << "error: " << err.getMessage() << endl;
    } else {
        cout << get<string>(res1);
    }

    variant<string, DeepThoughtError> res2 =
        deepThought.processInput("Hello, World?       \"Hello, Sir!\"        \"How are you today?\"");

    if (holds_alternative<DeepThoughtError>(res2)) {
        DeepThoughtError &err = get<DeepThoughtError>(res2);
        cerr << "error: " << err.getMessage() << endl;
    } else {
        cout << get<string>(res2);
    }

    variant<string, DeepThoughtError> res3 = deepThought.processInput("Hello, World?");

    if (holds_alternative<DeepThoughtError>(res3)) {
        DeepThoughtError &err = get<DeepThoughtError>(res3);
        cerr << "error: " << err.getMessage() << endl;
    } else {
        cout << get<string>(res3);
    }
}
