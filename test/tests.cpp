#include "gtest/gtest.h"

TEST(DeepThoughtTest, EmptyInput) {}
TEST(DeepThoughtTest, QuestionTooLong) {} // > 255 chars until next unquoted question mark
TEST(DeepThoughtTest, AnswerTooLong) {}
TEST(DeepThoughtTest, MultipleQuestionMarks) {}
TEST(DeepThoughtTest, UnclosedQuotes) {}
TEST(DeepThoughtTest, AnswerWithoutQuotes) {}
TEST(DeepThoughtTest, NonExistingQuestion) {}
