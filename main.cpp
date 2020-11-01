#include <iostream>
#include "solver.h"

int main() {
    std::string reg_exp;
    char letter = 0;
    size_t multiplicity = 0;
    std::cin >> reg_exp >> letter >> multiplicity;

    Solver solver(reg_exp, letter);
    bool result = solver.AnswerToRequest(multiplicity);
    result ? std::cout << "YES\n" : std::cout << "NO\n";
    return 0;
}
