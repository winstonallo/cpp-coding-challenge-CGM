#include "DeepThought.hpp"
#include <variant>

using namespace std;

int
main() {
    DeepThought deepThought;

    variant<bool, DeepThoughtError> result = deepThought.processInput("asaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasaasa?");

    if (holds_alternative<DeepThoughtError>(result)) {
        DeepThoughtError &err = get<DeepThoughtError>(result);
        cerr << "error: " << err.getMessage() << endl;
    }
}
