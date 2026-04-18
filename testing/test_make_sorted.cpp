#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);

    make_sorted(p_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(arr[i], (i+1));
    }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {5, 4, 3, 2, 1};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);

    make_sorted(p_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(arr[i], (i + 1));
    }
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {7, 3, 9, 4, 1};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);

    make_sorted(p_arr, length);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 7);
    EXPECT_EQ(arr[4], 9);
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {7, 1, 7, 4, 1};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);

    make_sorted(p_arr, length);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 7);
    EXPECT_EQ(arr[4], 7);
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int length = values.size();
    int* arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_arr = &arr[0];

    make_sorted(p_arr, length);

    for (int j = 0; j < length - 1 ; j++) {
        EXPECT_LE(arr[j], arr[j + 1]);
    }

    free(arr);
}
