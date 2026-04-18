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
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
    char* arguments[] = {"cd", "3", "4", "5"};
    char** p_argv = arguments;

    int argc = sizeof(arguments) / sizeof(char*);

    int* ar_out = NULL;
    int** p_ar_out = &ar_out;

    //int* len_out = (int*) malloc ((argc - 1) * sizeof(int));
    int len_out;
    int* p_len_out = &len_out;

    parse_args(argc, p_argv, p_ar_out, p_len_out);

    EXPECT_EQ(len_out, 3);
    EXPECT_EQ(ar_out[0], 3);
    EXPECT_EQ(ar_out[1], 4);
    EXPECT_EQ(ar_out[2], 5);

    free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
}
