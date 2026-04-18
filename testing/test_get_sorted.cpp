#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(p_sorted_arr[i], (i+1));
    }

    free(p_sorted_arr);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {5, 4, 3, 2, 1};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(p_sorted_arr[i], (i + 1));
    }

    free(p_sorted_arr);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {7, 3, 9, 2, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    EXPECT_EQ(p_sorted_arr[0], 2);
    EXPECT_EQ(p_sorted_arr[1], 3);
    EXPECT_EQ(p_sorted_arr[2], 5);
    EXPECT_EQ(p_sorted_arr[3], 7);
    EXPECT_EQ(p_sorted_arr[4], 9);

    free(p_sorted_arr);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {7, 2, 7, 2, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    EXPECT_EQ(p_sorted_arr[0], 2);
    EXPECT_EQ(p_sorted_arr[1], 2);
    EXPECT_EQ(p_sorted_arr[2], 5);
    EXPECT_EQ(p_sorted_arr[3], 7);
    EXPECT_EQ(p_sorted_arr[4], 7);

    free(p_sorted_arr);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    for (int i = 0; i < length; i++) {
        arr[i] = 9;
    }

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(arr[i], 9);
    }

    free(p_sorted_arr);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int* p_sorted_arr;

    p_sorted_arr = get_sorted(p_arr, length);

    EXPECT_NE(p_arr, p_sorted_arr);

    free(p_sorted_arr);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int length = values.size();
    int* arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_arr = &arr[0];
    int* cp_p_arr;

    cp_p_arr = get_sorted(p_arr, length);

    for (int j = 0; j < length - 1; j++) {
        EXPECT_LE(cp_p_arr[j], cp_p_arr[j+1]);
    }

    free(arr);
    free(cp_p_arr);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    ;
    int length = values.size();
    int* arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_arr = &arr[0];
    int* cp_p_arr;

    cp_p_arr = get_sorted(p_arr, length);

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(arr[j], values[j]);
    }

    free(arr);
    free(cp_p_arr);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int length = values.size();
    int* arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_arr = &arr[0];
    int* cp_p_arr;

    cp_p_arr = get_sorted(p_arr, length);

    for (int j = 0; j < length - 1; j++) {
        EXPECT_LE(cp_p_arr[j], cp_p_arr[j+1]);
    }
    EXPECT_NE(p_arr, cp_p_arr);

    free(arr);
    free(cp_p_arr);
}











