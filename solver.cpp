#include "solver.h"

size_t State::GetMaxPrefixLen() const noexcept {
    return max_prefix_len_;
}
size_t State::GetMaxSuffixLen() const noexcept {
    return max_suffix_len_;
}
size_t State::GetMaxSubstrLen() const noexcept {
    return max_substr_len_;
}
bool State::GetStatus() const noexcept {
    return hasnt_diff_letters_;
}
bool State::IsEmpty() const noexcept {
    return is_empty_;
}

Solver::Solver(const std::string_view& reg_exp, char sign): reg_exp_(reg_exp) {
    if (IsCorrectLetter(sign)) {
        letter_to_find_ = sign;
    } else {
        std::cerr << "Wrong letter in the Solver's constructor\n";
    }
}

bool Solver::IsCorrectLetter(char sign) const noexcept {
    return std::any_of(alphabet_.begin(), alphabet_.end(), [sign](char letter){
        return sign == letter;
    }) || sign == Solver::EpsilonToken;
}

State Solver::AddLetter(char sign) const noexcept {
    if (sign == letter_to_find_) {
        return State{1, 1, 1, true, false};
    } else if (sign == EpsilonToken) {
        return State{0, 0, 0, false, true};
    }
    return State{0, 0, 0, false, false};
}

State Solver::Sum(const State& summand1, const State& summand2) {
    bool sum_hasnt_diff_letters = summand1.GetStatus() + summand2.GetStatus();
    auto sum_max_prefix_len = std::max(summand1.GetMaxPrefixLen(), summand2.GetMaxPrefixLen());
    auto sum_max_suffix_len = std::max(summand1.GetMaxSuffixLen(), summand2.GetMaxSuffixLen());
    auto sum_max_substr_len = std::max(summand1.GetMaxSubstrLen(), summand2.GetMaxSubstrLen());
    auto sum_is_empty = std::max(summand1.IsEmpty(), summand2.IsEmpty());

    return {sum_max_prefix_len, sum_max_suffix_len, sum_max_substr_len, sum_hasnt_diff_letters,
                                                                                    sum_is_empty};
}
State Solver::Concatenate(const State& obj1, const State& obj2) {
    bool mult_hasnt_diff_letters = obj1.GetStatus() * obj2.GetStatus();

    auto candidate2_mult_max_len = obj1.GetMaxSuffixLen() + obj2.GetMaxPrefixLen();
    auto mult_max_substr_len = std::max(obj1.GetMaxSubstrLen(), obj2.GetMaxSubstrLen());
    mult_max_substr_len = std::max(mult_max_substr_len, candidate2_mult_max_len);

    auto mult_max_prefix_len = obj1.GetMaxPrefixLen();
    auto mult_max_suffix_len = obj2.GetMaxSuffixLen();
    auto mult_is_empty = obj1.IsEmpty() && obj2.IsEmpty();

    if (obj1.GetStatus()) {
        mult_max_prefix_len = obj1.GetMaxPrefixLen() + obj2.GetMaxPrefixLen();
    }
    if (obj2.GetStatus()) {
        mult_max_suffix_len = obj1.GetMaxSuffixLen() + obj2.GetMaxSuffixLen();
    }

    if (obj1.IsEmpty()) {
        mult_max_prefix_len = std::max(mult_max_prefix_len, obj2.GetMaxPrefixLen());
        mult_hasnt_diff_letters = obj2.GetStatus();
    }
    if (obj2.IsEmpty()) {
        mult_max_suffix_len = std::max(mult_max_suffix_len, obj1.GetMaxSuffixLen());
        mult_hasnt_diff_letters = obj1.GetStatus();
    }

    return {mult_max_prefix_len, mult_max_suffix_len, mult_max_substr_len,
                                                            mult_hasnt_diff_letters, mult_is_empty};
}
State Solver::Closure(const State& obj) {
    bool cl_hasnt_diff_letters = obj.GetStatus();
    auto cl_max_prefix_len = obj.GetMaxPrefixLen();
    auto cl_max_suffix_len = obj.GetMaxSuffixLen();

    auto cl_max_substr_len = obj.GetMaxSubstrLen();
    cl_max_substr_len = std::max(cl_max_substr_len, obj.GetMaxPrefixLen() + obj.GetMaxSuffixLen());
    if (obj.GetStatus()) {
        cl_max_substr_len = cl_max_prefix_len = cl_max_suffix_len = State::INF;
    }

    return {cl_max_prefix_len, cl_max_suffix_len, cl_max_substr_len, cl_hasnt_diff_letters, true};
}

void Solver::Sum(std::stack<State>& states) {
    if (states.size() < 2) {
        throw std::invalid_argument("ERROR. Wrong regular expression");
    }

    auto summand1 = states.top();
    states.pop();
    auto summand2 = states.top();
    states.pop();
    auto sum = Sum(summand1, summand2);

    states.push(sum);
}
void Solver::Concatenate(std::stack<State>& states) {
    if (states.size() < 2) {
        throw std::invalid_argument("ERROR. Wrong regular expression\n");
    }

    auto word1 = states.top();
    states.pop();
    auto word2 = states.top();
    states.pop();
    auto concat = Concatenate(word1, word2);

    states.push(concat);
}
void Solver::Closure(std::stack<State>& states) {
    if (states.empty()) {
        throw std::invalid_argument("ERROR. Wrong regular expression\n");
    }

    auto word = states.top();
    states.pop();
    auto closure = Closure(word);

    states.push(closure);
}

size_t Solver::FindTheLongestSubstrLen() const {
    size_t result = 0;
    std::stack<State> states;

    for (const auto& sign: reg_exp_) {
        if (IsCorrectLetter(sign)) {
            states.push(AddLetter(sign));
            continue;
        }
        switch (sign) {
            case SumToken:
                try {
                    Sum(states);
                    break;
                } catch (std::invalid_argument()) {
                    throw;
                }
            case ConcatenateToken:
                try {
                    Concatenate(states);
                    break;
                } catch (std::invalid_argument()) {
                    throw;
                }
            case KliniStarToken:
                try {
                    Closure(states);
                    break;
                } catch (std::invalid_argument()) {
                    throw;
                }
            default:
                throw std::invalid_argument("ERROR. Wrong symbol in the regular expression");
        }
    }

    if (states.size() != 1) {
        throw std::invalid_argument("ERROR. Wrong regular expression");
    }

    return states.top().GetMaxSubstrLen();
}
bool Solver::AnswerToRequest(size_t length) const {
    size_t max_length = 0;
    try {
        max_length = FindTheLongestSubstrLen();
    } catch (std::invalid_argument()) {
        throw;
    }
    return max_length >= length;
}
