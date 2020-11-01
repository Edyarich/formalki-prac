#include "solver.h"
#include <gtest/gtest.h>

TEST(FROM_DOC, A_LETTER_4) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'a');
    bool answer = solver.AnswerToRequest(4);
    EXPECT_EQ(answer, false);
}

TEST(FROM_DOC, B_LETTER_2) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'b');
    bool answer = solver.AnswerToRequest(2);
    EXPECT_EQ(answer, true);
}

TEST(FROM_DOC, B_LETTER_3) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'b');
    bool answer = solver.AnswerToRequest(3);
    EXPECT_EQ(answer, false);
}

TEST(FIRST_FROM_DOC, A_LETTER_2) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'b');
    bool answer = solver.AnswerToRequest(2);
    EXPECT_EQ(answer, true);
}

TEST(FIRST_FROM_DOC, C_LETTER_2) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'c');
    size_t answer = solver.AnswerToRequest(2);
    EXPECT_EQ(answer, false);
}

TEST(FIRST_FROM_DOC, C_LETTER_1) {
    std::string reg_exp = "ab+c.aba.*.bac.+.+*";
    Solver solver(reg_exp, 'c');
    size_t answer = solver.AnswerToRequest(1);
    EXPECT_EQ(answer, true);
}



TEST(SECOND_FROM_DOC, B_LETTER_2) {
    std::string reg_exp = "acb..bab.c.*.ab.ba.+.+*a.";
    Solver solver(reg_exp, 'b');
    size_t answer = solver.AnswerToRequest(2);
    EXPECT_EQ(answer, true);
}

TEST(SECOND_FROM_DOC, B_LETTER_3) {
    std::string reg_exp = "acb..bab.c.*.ab.ba.+.+*a.";
    Solver solver(reg_exp, 'b');
    size_t answer = solver.AnswerToRequest(3);
    EXPECT_EQ(answer, false);
}

TEST(SECOND_FROM_DOC, A_LETTER_3) {
    std::string reg_exp = "acb..bab.c.*.ab.ba.+.+*a.a.";
    Solver solver(reg_exp, 'a');
    size_t answer = solver.AnswerToRequest(3);
    EXPECT_EQ(answer, true);
}

TEST(SECOND_FROM_DOC, A_LETTER_4) {
    std::string reg_exp = "acb..bab.c.*.ab.ba.+.+*a.a.";
    Solver solver(reg_exp, 'a');
    size_t answer = solver.AnswerToRequest(4);
    EXPECT_EQ(answer, false);
}

TEST(SECOND_FROM_DOC, C_LETTER_2) {
    std::string reg_exp = "acb..bcb.c.*.cb.ba.+.+*a.";
    Solver solver(reg_exp, 'c');
    size_t answer = solver.AnswerToRequest(2);
    EXPECT_EQ(answer, true);
}

TEST(SECOND_FROM_DOC, C_LETTER_4) {
    std::string reg_exp = "acb..bcb.c.*.cb.ba.+.+*a.";
    Solver solver(reg_exp, 'c');
    size_t answer = solver.AnswerToRequest(4);
    EXPECT_EQ(answer, false);
}


TEST(EXCEPTIONS, INCORRECT_CONCATENATION_NO_OPERAND) {
    std::string reg_exp = "acb...";
    Solver solver(reg_exp, 'a');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, INCORRECT_CONCATENATION_EMPTY_STACK) {
    std::string reg_exp = ".acb..";
    Solver solver(reg_exp, 'c');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, INCORRECT_ADDITION_NO_OPERAND) {
    std::string reg_exp = "acb+++";
    Solver solver(reg_exp, 'b');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, INCORRECT_ADDITION_EMPTY_STACK) {
    std::string reg_exp = "+cb+";
    Solver solver(reg_exp, 'a');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, INCORRECT_CLOSURE_NO_OPERAND) {
    std::string reg_exp = "*";
    Solver solver(reg_exp, 'c');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, LESS_OPERANDS_THAN_NECESSARY) {
    std::string reg_exp = "aaaaaa...";
    Solver solver(reg_exp, 'a');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

TEST(EXCEPTIONS, NO_OPERANDS) {
    std::string reg_exp = "aaaaaa";
    Solver solver(reg_exp, 'a');
    ASSERT_ANY_THROW(solver.AnswerToRequest(1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

