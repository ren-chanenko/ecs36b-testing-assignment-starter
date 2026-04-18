#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    int len = *rc::gen::inRange<int>(0, 100);
    char* word = (char*) malloc ((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) {
        word[i] = *rc::gen::inRange<char>('a', 'z');;
    }

    word[len] = '\0';

    return word;

}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<char*> result;
    char buffer[20];
    for (int i = 0; i < numbers.size(); i++) {
        sprintf(buffer, "%d", numbers[i]);
        result.push_back(strdup(buffer));
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    char* arguments[] = {"cd", "10", "725", "-5"};
    char** p_argv = arguments;

    int argc = sizeof(arguments) / sizeof(char*);

    int* ar_out = NULL;
    int** p_ar_out = &ar_out;

    int len_out;
    int* p_len_out = &len_out;

    parse_args(argc, p_argv, p_ar_out, p_len_out);

    EXPECT_EQ(len_out, 3);
    EXPECT_EQ(ar_out[0], 10);
    EXPECT_EQ(ar_out[1], 725);
    EXPECT_EQ(ar_out[2], -5);

    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    char* arguments[] = {"hello"};
    char** p_argv = arguments;

    int argc = sizeof(arguments) / sizeof(char*);

    int* ar_out = NULL;
    int** p_ar_out = &ar_out;

    int len_out = 0;
    int* p_len_out = &len_out;

    parse_args(argc, p_argv, p_ar_out, p_len_out);

    EXPECT_EQ(len_out, 0);
    EXPECT_TRUE(ar_out == NULL);

    free(ar_out);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              (const std::vector<int>&values)
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    std::vector<char*> arguments =  vector_of_ints_to_vector_of_strings(values);
    arguments.insert(arguments.begin(), word_generator());
    char** p_argv = arguments.data();

    int argc = arguments.size();

    int* ar_out = NULL;
    int** p_ar_out = &ar_out;

    int len_out;
    int* p_len_out = &len_out;

    parse_args(argc, p_argv, p_ar_out, p_len_out);

    EXPECT_EQ(len_out, values.size());
    for (int i = 0; i < values.size(); i++) {
        EXPECT_EQ(ar_out[i], values[i]);
    }

    for (int j = 0; j < arguments.size(); j++ ) {
        free(arguments[j]);
    }
    free(ar_out);

}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    char* arguments[1] = { word_generator()};
    char** p_argv = arguments;

    int argc = sizeof(arguments) / sizeof(char*);

    int* ar_out = NULL;
    int** p_ar_out = &ar_out;

    int len_out = 0;
    int* p_len_out = &len_out;

    parse_args(argc, p_argv, p_ar_out, p_len_out);

    EXPECT_EQ(len_out, 0);
    EXPECT_TRUE(ar_out == NULL);

    free(ar_out);
    free(arguments[0]);
}
