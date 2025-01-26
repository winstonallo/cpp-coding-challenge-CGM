#include "DeepThought.hpp"
#include "gtest/gtest.h"
#include <variant>

variant<string, DeepThoughtError> test(const string &input) {
    DeepThought deepthought;

    return deepthought.processInput(input);
}

TEST(DeepThoughtTest, EmptyInput) {
    variant<string, DeepThoughtError> res = test("");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::EMPTY_INPUT);
}

TEST(DeepThoughtTest, QuestionTooLong) {
    stringstream stream;

    for (int i = 0; i <= 256; ++i) {
        stream << ' ';
    }

    variant<string, DeepThoughtError> res = test(stream.str());

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::QUESTION_TOO_LONG);
}

TEST(DeepThoughtTest, AnswerTooLong) {
    stringstream stream;

    stream << '"';
    for (int i = 0; i <= 256; ++i) {
        stream << ' ';
    }
    stream << '"';

    variant<string, DeepThoughtError> res = test("Question?" + stream.str());

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::ANSWER_TOO_LONG);
}

TEST(DeepThoughtTest, MultipleQuestionMarks) {
    variant<string, DeepThoughtError> res = test("?? \"Hello\"");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES);
}

// Covers branch inside of for loop in DeepThought::getAnswers()
TEST(DeepThoughtTest, AnswerWithoutQuotes1) {
    variant<string, DeepThoughtError> res = test("What is the answer to? \"The life\" \"The universe\" everything");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::ANSWER_WITHOUT_QUOTES);
}

TEST(DeepThoughtTest, UnclosedQuotes) {
    variant<string, DeepThoughtError> res = test("Question? \"Answer");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::UNCLOSED_QUOTES);
}

TEST(DeepThoughtTest, QuestionInQuotes) {
    variant<string, DeepThoughtError> res = test("\"Hello?\"");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::QUESTION_IN_QUOTES);
}

TEST(DeepThoughtTest, NonExistingQuestion) {
    variant<string, DeepThoughtError> res = test("Non-existing Question?");

    ASSERT_EQ(get<string>(res), "The answer to life, universe and everything is 42.\n");
}

TEST(DeepThoughtTest, AddQuestion) {
    DeepThought deepthought;

    variant<string, DeepThoughtError> res = deepthought.processInput("Question? \"Answer1\" \"Answer2\" \"Answer3\"");

    ASSERT_EQ(
        get<string>(res),
        "Successfully stored new question 'Question?'\n"
    ); // processInput should return an empty string when adding a question

    variant<string, DeepThoughtError> res1 = deepthought.processInput("Question?");

    ASSERT_EQ(get<string>(res1), "Answer1\nAnswer2\nAnswer3\n");
}

TEST(DeepThoughtTest, NoQuestion) {
    DeepThought deepthought;

    variant<string, DeepThoughtError> res = deepthought.processInput("Question");

    ASSERT_EQ(get<DeepThoughtError>(res).getType(), DeepThoughtError::Type::NO_QUESTION);
}
