#include "gtest/gtest.h"

TEST(DeepThoughtAdd, EmptyInput) {}
TEST(DeepThoughtAdd, QuestionTooLong) {} // > 255 chars until next unquoted question mark
TEST(DeepThoughtAdd, AnswerTooLong) {}
TEST(DeepThoughtAdd, MultipleQuestionMarks) {}
TEST(DeepThoughtAdd, UnclosedQuotes) {}
TEST(DeepThoughtAdd, AnswerWithoutQuotes) {}

TEST(DeepThoughtAsk, EmptyInput) {}
TEST(DeepThoughtAsk, InputTooLong) {}
