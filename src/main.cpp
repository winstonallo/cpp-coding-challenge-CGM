#include "DeepThought.hpp"
#include <iostream>
#include <variant>

using namespace std;

int
main() {
    DeepThought deepthought;
    string input;

    for (;;) {
        cout << "deepthought> ";

        if (!getline(cin, input)) {
            break;
        }

        variant <string, DeepThoughtError> res = deepthought.processInput(input);

        if (holds_alternative<DeepThoughtError>(res)) {
            cerr << get<DeepThoughtError>(res).getMessage() << '\n';
        } else {
            cout << get<string>(res);
        }
    }
}
