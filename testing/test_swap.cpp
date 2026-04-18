#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */

    int a = 5;
    int b = 7;
    int* x = &a;
    int* y = &b;

    swap(x, y);

    EXPECT_EQ(a, 7);
    EXPECT_EQ(b, 5);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int array[] = {1, 2, 3, 4};

    int *x = &array[0];
    int *y = &array[2];

    swap(x, y);

    EXPECT_EQ(array[0], 3);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 1);
    EXPECT_EQ(array[3], 4);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start;
    int b = b_start;

    int* x = &a;
    int* y = &b;

    swap(x, y);

    EXPECT_EQ(a, b_start);
    EXPECT_EQ(b, a_start );

}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    RC_PRE(values.size() >= 3);


    size_t length = values.size();
    int *array = (int*) malloc(length * sizeof(int));

    for (size_t i = 0; i < length; i++) {
        array[i] = values[i];
    }

    int *x = &array[0];
    int *y = &array[2];

    swap(x, y);

    for (size_t j = 0; j < length; j++) {
        if (j == 0) {
            EXPECT_EQ(array[j], values[2]) << "j:" << j;
            continue;
        }
        if (j == 2) {
            EXPECT_EQ(array[j], values[0]) << "j:" << j;
            continue;
        }
        EXPECT_EQ(array[j], values[j]) << "j:" << j;
    }

    free(array);
}
