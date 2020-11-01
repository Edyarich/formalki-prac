#ifndef FORMALKI1_SOLVER_H
#define FORMALKI1_SOLVER_H

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <stack>
#include <exception>
#include <algorithm>

class State {
public:
    static const size_t INF = SIZE_MAX;
private:
    size_t max_prefix_len_ = 0;
    size_t max_suffix_len_ = 0;
    size_t max_substr_len_ = 0;
    bool has_diff_letters_ = true;

public:
    State(size_t num1, size_t num2, size_t num3, bool num4): max_prefix_len_(num1),
                                                             max_suffix_len_(num2),
                                                             max_substr_len_(num3),
                                                             has_diff_letters_(num4) {}

    size_t GetMaxPrefixLen() const noexcept;
    size_t GetMaxSuffixLen() const noexcept;
    size_t GetMaxSubstrLen() const noexcept;
    bool GetStatus() const noexcept;
};

class Solver {
public:
    static const char ConcatenateToken = '.';
    static const char SumToken = '+';
    static const char KliniStarToken = '*';
    static const char EpsilonToken = '1';
private:
    std::array<char, 3> alphabet_ = {{'a', 'b', 'c'}};
    std::string reg_exp_;
    char letter_to_find_ = alphabet_[0];

    State AddLetter(char) const noexcept;
    static State Concatenate(const State&, const State&);
    static State Sum(const State&, const State&);
    static State Closure(const State&);
    static void Concatenate(std::stack<State>&);
    static void Sum(std::stack<State>&);
    static void Closure(std::stack<State>&);

public:
    Solver() = default;
    Solver(const Solver&) = delete;
    Solver(const Solver&&) = delete;
    Solver operator=(const Solver&) = delete;
    Solver operator=(const Solver&&) = delete;
    explicit Solver(const std::string&, char);

    bool IsCorrectLetter(char) const noexcept;

    size_t FindTheLongestSubstrLen() const;
    bool AnswerToRequest(size_t) const;
};

#endif //FORMALKI1_SOLVER_H
