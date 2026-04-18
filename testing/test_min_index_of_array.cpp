#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */

    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int min_index;

    min_index = min_index_of_array(p_arr, length);

    EXPECT_EQ(min_index, 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */

    int arr[] = {2, 3, 4, 5, 1};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int min_index;

    min_index = min_index_of_array(p_arr, length);

    EXPECT_EQ(min_index, 4);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */

    int arr[] = {2, 3, 1, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int min_index;

    min_index = min_index_of_array(p_arr, length);

    EXPECT_EQ(min_index, 2);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */

    int arr[] = {2, 1, 1, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int min_index;

    min_index = min_index_of_array(p_arr, length);

    EXPECT_EQ(min_index, 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */

    int arr[] = {1, 2, 3, 4, 5};
    int* p_arr = &arr[0];
    int length = sizeof(arr) / sizeof(arr[0]);
    int min_index;

    min_index = min_index_of_array(p_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(arr[i], (i+1));
    }
    EXPECT_EQ(min_index, 0);
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              (const std::vector<int>&values)) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    int length = values.size();
    int* arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_ar = &arr[0];
    int min_index;

    min_index = min_index_of_array(p_ar, length);

    for (int j = 0; j < length; j++) {
        if (j == min_index) {

            continue;
        }
        EXPECT_LE(arr[min_index], arr[j]);
    }
    free(arr);
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              (const std::vector<int>&values)) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int length = values.size();
    int* arr = (int*) malloc (length
        * sizeof(int));

    for (int i = 0; i < length; i++) {
        arr[i] = values[i];
    }

    int* p_ar = &arr[0];
    int min_index;

    min_index = min_index_of_array(p_ar, length);

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(arr[j], values[j]);
    }
    free(arr);
}
