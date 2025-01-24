#include "DeepThoughtError.hpp"
#include <iostream>
#include <ostream>

using namespace std;

int
main() {

    DeepThoughtError err(DeepThoughtError::Type::QUESTION_IN_QUOTES);

    cout << err.getMessage() << endl;

    DeepThoughtError err2(DeepThoughtError::Type::QUESTION_TOO_LONG);

    cout << err2.getMessage() << endl;
}
